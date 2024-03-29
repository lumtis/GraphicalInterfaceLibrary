/**
 *  @file	ei_application.c
 *  @brief	Manages the main steps of a graphical application: initialization, main window,
 *		main loop, quitting, resource freeing.
 *
 *  \author
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ei_application.h"
#include "debug.h"
#include "ei_widgetclass.h"
#include "ei_widget_frame.h"
#include "ei_global.h"
#include "ei_geometrymanager.h"
#include "ei_types.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "ei_draw_util.h"

// Est ce qu'on rafraichit tout, ou est ce qu'on fait tout les rectangles
//#define RAFRAICHISSEMENT_TOTAL


ei_widget_t * racine;
ei_surface_t window;
ei_surface_t windowpick;
ei_widget_t* tab_widget[256*256*256] = {NULL};
traitant* tab_event[ei_ev_last];
ei_linked_rect_t*  liste_rect = NULL;
ei_widget_t * focus ;




ei_bool_t quitEchap(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t memorizePosition(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


// Definit quand il faut  quitter l'application
ei_bool_t quit = EI_FALSE;
// Curseur position
ei_point_t currentP;
ei_point_t lastP;



void traitement(ei_event_t event ,  ei_widget_t* widget)
{
  // definit quand il faut stoper l'appel au callback
  ei_bool_t stopcallback = EI_FALSE;
  
  traitant* tmp = tab_event[event.type];
  while ( tmp != NULL && stopcallback== EI_FALSE)
  {
    if(tmp->widget == NULL)
    { 
      if(strcmp(tmp->tag ,"all") == 0)
	stopcallback=tmp->callback( widget , &(event) , tmp->user_param);
      if(strcmp( tmp->tag , widget->wclass->name ) == 0)
	stopcallback=tmp->callback(widget, &(event),tmp->user_param);
    }
    else 
    {
      if(tmp->widget == widget)
	stopcallback=tmp->callback(widget , &(event),tmp->user_param);
    }
    tmp=tmp->next;
  }
}




/*Libere une liste de rect*/
ei_linked_rect_t* freeLinkedRect(ei_linked_rect_t* l)
{
    ei_linked_rect_t* tmp1 = l;
    ei_linked_rect_t* tmp2;

    if(tmp1 == NULL)
        return NULL;
    if(tmp1->next == NULL)
	free(tmp1);

    while(tmp1->next != NULL)
    {
	tmp2 = tmp1->next;
        free(tmp1);
        tmp1 = tmp2;
    }
    
    return NULL;
}


void ei_app_run_rec(ei_widget_t* widget, ei_surface_t window, ei_surface_t windowpick, ei_rect_t* clipper)
{
    ei_rect_t tmp;
  
    if(widget == NULL)
        return;
    
    if(widget->parent == NULL)
    {
	widget->wclass->drawfunc(widget ,window, windowpick, clipper);
    
	ei_app_run_rec(widget->children_head, window, windowpick, clipper);
	ei_app_run_rec(widget->next_sibling, window, windowpick, clipper);
    }
    else
    {
	tmp = realIntersection(widget->parent->content_rect, clipper);
	
	if(tmp.size.width > 0)
	{
	    widget->wclass->drawfunc(widget ,window, windowpick, &tmp);
	    ei_app_run_rec(widget->children_head, window, windowpick, &tmp);
	}
	
	ei_app_run_rec(widget->next_sibling, window, windowpick, clipper);
    }
}



void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{ 
    ei_color_t * coloracine;
    
    hw_init();
    for ( ei_eventtype_t i = ei_ev_none ; i < ei_ev_last ; i++)
      tab_event[i]=NULL;
    ei_frame_register_class();
    ei_button_register_class();
    ei_toplevel_register_class();
    ei_register_placer_manager();
    
    racine = frameAllocfunc();
    frameSetdefaultsfunc(racine);
    focus= ei_app_root_widget();
    coloracine=malloc(sizeof(ei_color_t));
    coloracine->red = 0;
    coloracine->green = 0;
    coloracine->blue = 0;
    coloracine->alpha = 255;
    
    // Identifiant
    racine->pick_color = coloracine;
    racine->wclass = ei_widgetclass_from_name("frame");
    racine->pick_id = 0;
    
    // Taille
    racine->requested_size = *main_window_size;
    racine->screen_location.top_left.x = 0;
    racine->screen_location.top_left.y = 0;
    racine->screen_location.size = *main_window_size;
    racine->content_rect = malloc(sizeof(ei_rect_t));
    *(racine->content_rect) = racine->screen_location;
    
    // Initialisation du tableau de widget 
     tab_widget[0]=racine;
//     for ( int i =1 ; i <256 ; i++)
//       tab_widget[i]=NULL;

    racine->geom_params = calloc(1, sizeof(ei_geometry_param_t));
    
    window = hw_create_window(main_window_size,fullscreen);
    windowpick = hw_surface_create(window,main_window_size, EI_TRUE);
    
    
    // Quitter lorsqu'on appuie sur echap
    ei_bind(ei_ev_keydown, NULL, "all", quitEchap, NULL);
    
    // Position souris
    currentP = ei_point(0,0);
    lastP = ei_point(0,0);
    ei_bind(ei_ev_mouse_move, NULL, "all", memorizePosition, NULL);
}


void ei_app_free()
{
    ei_widget_destroy(racine);
    hw_surface_free(window);
    
    ei_unbind(ei_ev_keydown, NULL, "all", quitEchap, NULL);
    ei_unbind(ei_ev_mouse_move, NULL, "all", memorizePosition, NULL);
    
    // On termine le widget principal
    hw_quit();
  
    return;
}

void ei_app_run()
{
    ei_linked_rect_t * courant;
    ei_event_t event;
    
    // Premier dessin de la fenere entiere
    hw_surface_lock(window);
    //frameDrawfunc(racine, window, windowpick, racine->content_rect);
    ei_app_run_rec(racine, window, windowpick, racine->content_rect);
    hw_surface_unlock(window);
    hw_surface_update_rects(window, NULL);
    
   while ( quit == EI_FALSE)
   {
    hw_event_wait_next(&event);
    switch ( event.type )
    {
      case ei_ev_none:
      case ei_ev_last : break;
      case ei_ev_app:
      case ei_ev_keydown :
      case ei_ev_keyup :traitement(event, focus);break;
      case ei_ev_mouse_buttondown : focus = ei_widget_pick(&(event.param.mouse.where)); traitement(event, focus) ;break;
      case ei_ev_mouse_buttonup : 
      case ei_ev_mouse_move : traitement(event, ei_widget_pick(&(event.param.mouse.where)));break;
      
    }
    
    courant = liste_rect;
    hw_surface_lock(window);
    #ifdef RAFRAICHISSEMENT_TOTAL
    if( courant != NULL)
	ei_app_run_rec(racine, window, windowpick, racine->content_rect);
    #else
    while ( courant != NULL)
    {
      ei_app_run_rec(racine, window, windowpick,&(courant->rect));
      courant=courant->next;
    }
    #endif
    liste_rect = freeLinkedRect(liste_rect);
    hw_surface_unlock(window);
    hw_surface_update_rects(window, NULL);
  }  
}


printListRect(ei_linked_rect_t *l)
{
    int i = 0;
    ei_rect_t rect;
    while(l != NULL)
    {
	rect = l->rect;
	printf("rect%d : %d %d %d %d\n", i, rect.top_left.x, rect.top_left.y, rect.size.width, rect.size.height);
	i++;
	l = l->next;
    }
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{
    
    ei_linked_rect_t * new_rect = calloc(1, sizeof(ei_linked_rect_t));
    new_rect->rect = *rect;
    ei_linked_rect_t * tmp;
    
    // On rajoute le rectangles à la fin de la liste
    if (liste_rect == NULL)
      liste_rect = new_rect;
    else
    {
      tmp=liste_rect;
      for(tmp=liste_rect;tmp->next != NULL; tmp =tmp->next);
      tmp->next= new_rect;
    }
}


ei_bool_t quitEchap(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    if(event->param.key.key_sym == SDLK_RETURN)
    {
	ei_app_quit_request();
	
	return EI_TRUE;
    }
    return EI_FALSE;
}



void ei_app_quit_request()
{
    quit = EI_TRUE;
    return;
}

ei_widget_t* ei_app_root_widget()
{
    return racine;
}

ei_surface_t ei_app_root_surface()
{
    return window;
}


ei_bool_t memorizePosition(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    // On met à jour la position courante et precedante
    lastP = ei_point(currentP.x, currentP.y);
    currentP = event->param.mouse.where;
    
    return EI_FALSE;
}

ei_point_t getCurrent()
{
    return currentP;
}

ei_point_t getLast()
{
    return lastP;
}
