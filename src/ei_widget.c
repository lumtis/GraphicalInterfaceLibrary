/**
 * @file	ei_widget.c
 *
 * @brief 	API for widgets management: creation, configuration, hierarchy, redisplay.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ei_application.h"
#include "ei_widget.h"
#include "debug.h"
#include "ei_widget_frame.h"
#include "ei_widget_button.h"
#include "ei_widget_toplevel.h"
#include "ei_geometrymanager.h"
#include "ei_global.h"
#include "ei_interncallback.h"
#include "ei_event.h"



uint32_t vgpick_id = 1;


// Libere un widget
void freeWidget(ei_widget_t * widget)
{   
    // libère les pointeurs spécifiques à la classe
    widget->wclass->releasefunc(widget);
    // libère les autres pointeurs s'ils sont non nuls
    if(widget->pick_color != NULL)
	free(widget->pick_color);
    if(widget->content_rect != NULL)
	free(widget->content_rect);
    if(widget->geom_params != NULL)
    {
	if(widget->geom_params->manager != NULL)
	    free(widget->geom_params->manager);
	free(widget->geom_params);
    }
    free(widget);
}


/**
 * \brief  libère tous les widgets frères et fils du widget en paramètre ainsi que le widget lui même 
 */
void ei_widget_destroy_rec(ei_widget_t * widget)
{
    if (widget == NULL )
        return;
    else
    {
        if (widget->children_head != NULL )
	  // libère les fils
            ei_widget_destroy_rec(widget->children_head);
        if (widget->next_sibling != NULL )
	  // libère les frères 
            ei_widget_destroy_rec(widget->next_sibling);
	
        freeWidget(widget);
    }
}


ei_widget_t* ei_widget_create(ei_widgetclass_name_t class_name,
			      ei_widget_t* parent)
{
  
  ei_widget_t* new_widget ;
  // obtenion de class à partir de son nom
  ei_widgetclass_t * classe_new_widget = ei_widgetclass_from_name(class_name);
  // si on ne connait pas la classe souhaitée , on retoune NULL 
  if ( classe_new_widget == NULL)
    return NULL;
  else
    {
      // allocation de l'espace necessaire pour cette classe de widget précisemment 
      new_widget = (ei_widget_t*)classe_new_widget->allocfunc();
      new_widget->wclass = classe_new_widget;
      // initialisation de valeur spécifiques à la classe
      classe_new_widget->setdefaultsfunc(new_widget);
      
      // initialisaion des autres valeurs 
      new_widget->pick_id = vgpick_id ;
      new_widget->pick_color = calloc(1, sizeof(ei_color_t));
      // fonction bijective entre [0,2^(64)-1] et [0,255]*[0,255]*[0,255] 
      new_widget->pick_color->red = vgpick_id % 256;
      new_widget->pick_color->alpha = 255 ;
      new_widget->pick_color->blue = (vgpick_id / 256 ) % 256;	
      new_widget->pick_color->green=(vgpick_id / (256*256)) % 256 ;
      // maximum de widget possible est 256*256*256
      if (vgpick_id > 256*256*256 -1)
	fprintf( stderr , "trop de widget tue le widget" );
	
      // Arborescence
      new_widget->parent = parent;
      if (parent->children_head == NULL )
	{
	  parent->children_head=new_widget;
	  parent->children_tail=new_widget;
	}
      else
	{
	  parent->children_tail->next_sibling = new_widget;
	  parent->children_tail = new_widget;
	}
    }
    
    // Localistation, geometrie
    new_widget->screen_location.top_left = parent->screen_location.top_left;
    new_widget->geom_params = calloc(1, sizeof(ei_geometry_param_t));
    new_widget->content_rect = calloc(1, sizeof(ei_rect_t));
    
    // mise à jour du tableau de widget
    tab_widget[vgpick_id]=new_widget;
    vgpick_id++; 
    // création des mind des button et top level 
    if ( strcmp ( class_name ,"button" ) == 0 )
      ei_bind(ei_ev_mouse_buttondown,new_widget,NULL,pushButton, NULL);
    if ( strcmp( class_name, "toplevel" ) == 0 )
      ei_bind(ei_ev_mouse_buttondown,new_widget,NULL,pushToplevel, NULL);
    return new_widget;
}


void ei_widget_destroy(ei_widget_t* widget)
{
    ei_widget_t* p;
    if (widget == NULL )
        return;
    else
      
    {
	// avant de détruire les widget , on enlève les bind correspondants
	if ( strcmp ( widget->wclass->name , "button" ))
	  ei_unbind(ei_ev_mouse_buttondown,widget,NULL,pushButton, NULL);
	if ( strcmp ( widget->wclass->name , "toplevel" ))
	  ei_unbind(ei_ev_mouse_buttondown,widget,NULL,pushToplevel, NULL);
        if (widget->parent== NULL)
        {   
	    //libère tout l'arbre 
            ei_widget_destroy_rec(widget->children_head);
            freeWidget(widget);
        }
        else
        {
	    // recherche du 1èr frère précédent le widget à liberer 
            p= widget->parent->children_head;
            if ( p == widget)
            {
	        // cas où le widget est un fils unique 
              	if (p==widget->parent->children_tail)
              	{
                  	  widget->parent->children_head = NULL;
                  	  widget->parent->children_tail= NULL;
                  	  ei_widget_destroy_rec(widget->children_head);
                  	  freeWidget(widget);
              	}
              	 else
              	 {
		   //cas où c'est le plus grand des fils 
                  	  widget->parent->children_head= p->next_sibling;
                  	  ei_widget_destroy_rec(widget->children_head);
                  	  
			  freeWidget(widget);
              	  }
      	    }
      	    else
      	    {
		// les autres cas
          	    while ( p->next_sibling != widget )
          	        p=p->next_sibling;
          	    p->next_sibling=widget->next_sibling;
          	    ei_widget_destroy_rec(widget->children_head);
		    
		    freeWidget(widget);
      	    }
        }
    }
}


ei_widget_t* ei_widget_pick(ei_point_t*	where)
{
  // le buffer pointe vers le pixel en haut à gauche
  uint8_t * buffer;
  // on récupère l'odre du RGB 
  int rouge;
  int vert;
  int bleu;
  int alpha;
  uint32_t id ;
  // width est la largeur de l'écrant ( mémoire organisé en tableau unidimentionnelle 
  int width=(hw_surface_get_size(ei_app_root_surface())).width;
  buffer= hw_surface_get_buffer(windowpick);
  hw_surface_get_channel_indices(windowpick, &rouge, &vert, &bleu, &alpha);
  // on récupère l'identité à partir de la couleur de la surface de picking et la fonction bijective
  id= buffer [ 4 * ((where->y)*width + (where->x)) + rouge] + 256 * buffer [ 4 * ((where->y)*width + (where->x)) + bleu ] + 256*256* buffer [ 4 * ((where->y)*width + (where->x)) + vert ]; 
  // on retourne le widget correspondant
  return tab_widget[id];
}




void			ei_frame_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor)
{
    ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;
    
    int text_width = 0;
    int text_height = 0;

    if(color != NULL)
        wf->color = *color;
    if(border_width != NULL)
        wf->border_width = *border_width;
    if(relief != NULL)
        wf->relief = *relief;
    if(text != NULL)
    {
        if(wf->text != NULL)
            free(wf->text);
	wf->text = malloc(strlen(*text)+1);
        strcpy(wf->text, *text);
    }
    if(text_font != NULL)
        wf->text_font = *text_font;
    if(text_color != NULL)
        wf->text_color = *text_color;
    if(text_anchor != NULL)
        wf->text_anchor = *text_anchor;
    if(img != NULL)
    {
        if(wf->img != NULL)
            hw_surface_free(wf->img);
        wf->img = *img;
    }
    if(img_rect != NULL)
        wf->img_rect = *img_rect;
    if(img_anchor != NULL)
        wf->img_anchor = *img_anchor;
    
    if(requested_size != NULL)
        widget->requested_size = *requested_size;
    if(wf->text != NULL && wf->text_font != NULL)
    {
	hw_text_compute_size(wf->text,wf->text_font,&text_width,&text_height);
	if(widget->requested_size.width < text_width+2*wf->border_width)
	    widget->requested_size.width = text_width+2*wf->border_width;
	if(widget->requested_size.height < text_height+2*wf->border_width)
	    widget->requested_size.height = text_height+2*wf->border_width;
    }
    if(widget->requested_size.width > widget->screen_location.size.width)
	widget->screen_location.size.width = widget->requested_size.width;
    if(widget->requested_size.height > widget->screen_location.size.height)
	widget->screen_location.size.height = widget->requested_size.height;
    
    // On modifie son content_rect en fonction de sa classe
    widget->wclass->geomnotifyfunc(widget, widget->screen_location);
}


// TODO : Changer taille
void			ei_button_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 int*			corner_radius,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor,
							 ei_callback_t*		callback,
							 void**			user_param)
{
    ei_widget_button_t* wb = (ei_widget_button_t*)widget;

    if(corner_radius != NULL)
        wb->corner_radius = *corner_radius;
    if(callback != NULL)
        wb->callback = *callback;
    if(user_param != NULL)
        wb->user_param = *user_param;

    ei_frame_configure(widget, requested_size, color, border_width, relief, text, text_font, text_color, text_anchor, img, img_rect, img_anchor);
}



// TODO : Changer taille
void			ei_toplevel_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 ei_color_t*		color,
							 int*			border_width,
							 char**			title,
							 ei_bool_t*		closable,
							 ei_axis_set_t*		resizable,
						 	 ei_size_t**		min_size)
{
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

    if(requested_size != NULL)
    {
        widget->requested_size = *requested_size;
	if(widget->requested_size.width > widget->screen_location.size.width)
	    widget->screen_location.size.width = widget->requested_size.width;
	if(widget->requested_size.height > widget->screen_location.size.height)
	    widget->screen_location.size.height = widget->requested_size.height;
    }

    if(color != NULL)
        wtl->color = *color;
    if(border_width != NULL)
        wtl->border_width = *border_width;
    if(title != NULL)
    {
        if(wtl->title != NULL)
            free(wtl->title);
	wtl->title = malloc(strlen(*title)+1);
        strcpy(wtl->title, *title);
    }
    if(closable != NULL)
        wtl->closable = *closable;
    if(resizable != NULL)
        wtl->resizable = *resizable;
    if(min_size != NULL)
        wtl->min_size = *min_size;
    
    // On modifie son content_rect en fonction de sa classe
    widget->wclass->geomnotifyfunc(widget, widget->screen_location);
}
