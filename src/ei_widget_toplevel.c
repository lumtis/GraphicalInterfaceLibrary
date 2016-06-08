
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ei_widget_toplevel.h"
#include "ei_draw_util.h"
#include "ei_interncallback.h"
#include "ei_types.h"
#include "ei_utils.h"
#include "ei_event.h"
#include "ei_application.h"
#include "ei_geometrymanager.h"

#define POS_BOUTON 10
#define TAILLE_BOUTON 8
#define TAILLE_ENTETE 20
#define TAILLE_RECADR 10


void* toplevelAllocfunc()
{
    return calloc(1, sizeof(ei_widget_toplevel_t));
}


void toplevelReleasefunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

    if(wtl->title != NULL)
        free(wtl->title);
    if(wtl->min_size != NULL)
        free(wtl->min_size);
} 


void toplevelDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{
  ei_widget_toplevel_t* tpl = (ei_widget_toplevel_t*)widget;
  ei_color_t  pickColor = (*widget->pick_color);
   
  draw_toplevel(widget,surface,clipper, pick_surface);
}


void toplevelSetdefaultsfunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

    wtl->border_width = 4;
    wtl->color = ei_default_background_color;
    wtl->title = malloc(strlen("Toplevel") + 1);
    strcpy(wtl->title, "Toplevel");
    wtl->closable = EI_TRUE;
    wtl->resizable = ei_axis_both;
    wtl->min_size = malloc(sizeof(ei_size_t));
    wtl->min_size->width = 160;
    wtl->min_size->height = 120;
}


void toplevelGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{
    ei_widget_toplevel_t* tpl = (ei_widget_toplevel_t*)widget;
    int b = tpl->border_width;
    int x = rect.top_left.x;
    int y = rect.top_left.y;
    int w = rect.size.width;
    int h = rect.size.height;
    
    widget->content_rect->top_left.x = x + 1 + b;
    widget->content_rect->top_left.y = y + TAILLE_ENTETE + 1 + b;
    widget->content_rect->size.width = w - 2 - 2*b;
    widget->content_rect->size.height = h - 2 - 2*b - TAILLE_ENTETE;
}


/**********************************************************************
***************** Events **********************************************
**********************************************************************/


ei_bool_t pushToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;
    ei_point_t cur = getCurrent();
    ei_point_t bPos = ei_point(widget->screen_location.top_left.x + POS_BOUTON, widget->screen_location.top_left.y + POS_BOUTON); // Position du bouton
    ei_rect_t recadr = ei_rect(ei_point(widget->screen_location.top_left.x + widget->screen_location.size.width - TAILLE_RECADR, widget->screen_location.top_left.y + widget->screen_location.size.height - TAILLE_RECADR), ei_size(TAILLE_RECADR,TAILLE_RECADR));
    
    // On regarde si nous sommes sur le boutton
    if(distPoint(cur, bPos) < 8 && wtl->closable == EI_TRUE)
	ei_bind(ei_ev_mouse_buttonup, NULL, "all", releaseCloseToplevel, widget);
    // On regarde si nous sommes sur l'en-tête    
    else if(cur.y < widget->screen_location.top_left.y + TAILLE_ENTETE)// On regarde si nous sommes sur l'en-tête
    {
	ei_bind(ei_ev_mouse_move, NULL, "all", moveToplevel, widget);
	ei_bind(ei_ev_mouse_buttonup, NULL, "all", releaseMoveToplevel, widget);
    }
    // On regarde si nous sommes sur le carré de recadrement
    else if(isIn(cur, recadr) == EI_TRUE && wtl->resizable != ei_axis_none)
    {
	ei_bind(ei_ev_mouse_move, NULL, "all", moveResizeToplevel, widget);
	ei_bind(ei_ev_mouse_buttonup, NULL, "all", releaseResizeToplevel, widget);
    }
    
    return EI_FALSE;
}


ei_bool_t releaseCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)user_param;
    ei_point_t cur = getCurrent();
    ei_widget_t* w = (ei_widget_t*)user_param;
    ei_point_t bPos = ei_point(w->screen_location.top_left.x + POS_BOUTON, w->screen_location.top_left.y + POS_BOUTON);
    ei_rect_t update = w->screen_location;
    
    update.size.width++;
    update.size.height++;
    
    // On retire l'evenement
    ei_unbind(ei_ev_mouse_buttonup, NULL, "all", releaseCloseToplevel, w);
    
    // Si le curseur est actuellement dans le button on change coupe la fenetre
    if(distPoint(cur, bPos) < 8 && wtl->closable == EI_TRUE)
    {
	// On retire l'evenement
	ei_unbind(ei_ev_mouse_buttonup, NULL, "all", releaseCloseToplevel, w);
	ei_app_invalidate_rect(&update);
	ei_widget_destroy(w);
	
 	return EI_TRUE;
    }
    
    return EI_FALSE;
}


ei_bool_t moveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_t* w = (ei_widget_t*)user_param;
    ei_point_t mov = ei_point_sub(getCurrent(), getLast()); // Mouvement entre la derniere et actuelle position
    ei_rect_t update;
    int newX = w->screen_location.top_left.x + mov.x;
    int newY = w->screen_location.top_left.y + mov.y;
    
    // Rectangle à mettre a jour
    update.top_left.x = min(w->screen_location.top_left.x, newX);
    update.top_left.y = min(w->screen_location.top_left.y, newY);
    if(mov.x > 0)
	update.size.width = w->screen_location.size.width + mov.x + 1;
    else
	update.size.width = w->screen_location.size.width - mov.x + 1;
    if(mov.y >0)
	update.size.height = w->screen_location.size.height + mov.y + 1;
    else
	update.size.height = w->screen_location.size.height - mov.y + 1;
    
    // Met à jour sa position
    ei_place(w, NULL, &newX, &newY, NULL, NULL, NULL, NULL, NULL, NULL);
    ei_app_invalidate_rect(&update);
    
    return EI_FALSE;
}

ei_bool_t releaseMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_t* w = (ei_widget_t*)user_param;
    
    // On retire les evenements
    ei_unbind(ei_ev_mouse_move, NULL, "all", moveToplevel, w);
    ei_unbind(ei_ev_mouse_buttonup, NULL, "all", releaseMoveToplevel, w);
    
    return EI_FALSE;
}


ei_bool_t moveResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)user_param;
    ei_widget_t* w = (ei_widget_t*)user_param;
    ei_point_t mov = ei_point_sub(getCurrent(), getLast());
    ei_rect_t update;
    int newWidth = w->screen_location.size.width + mov.x;
    int newHeight = w->screen_location.size.height + mov.y;
    
    if(w->screen_location.size.width + mov.x > wtl->min_size->width)
	 newWidth = w->screen_location.size.width + mov.x;
    else
	newWidth =wtl->min_size->width;
    if(w->screen_location.size.height + mov.y > wtl->min_size->height)
	 newHeight = w->screen_location.size.height + mov.y;
    else
	newHeight = wtl->min_size->height;
    
    // Rectangle à mettre a jour
    update.top_left.x = w->screen_location.top_left.x;
    update.top_left.y = w->screen_location.top_left.y;
    update.size.width = max(w->screen_location.size.width, w->screen_location.size.width + mov.x) + 1;
    update.size.height = max(w->screen_location.size.height, w->screen_location.size.height + mov.y) + 1;
    
    // Met à jour sa position
    switch(wtl->resizable)
    {
      
      case ei_axis_both :
	ei_place(w, NULL, NULL, NULL, &newWidth, &newHeight, NULL, NULL, NULL, NULL);
	break;
      case ei_axis_x :
	ei_place(w, NULL, NULL, NULL, &newWidth, NULL, NULL, NULL, NULL, NULL);
	break;
      case ei_axis_y :
	ei_place(w, NULL, NULL, NULL, NULL, &newHeight, NULL, NULL, NULL, NULL);
	break;
      default:
	break;
    }
    
    ei_app_invalidate_rect(&update);
    
    return EI_FALSE;
}

ei_bool_t releaseResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_t* w = (ei_widget_t*)user_param;
    
    // On retire les evenements
    ei_unbind(ei_ev_mouse_move, NULL, "all", moveResizeToplevel, w);
    ei_unbind(ei_ev_mouse_buttonup, NULL, "all", releaseResizeToplevel, w);
    
    return EI_FALSE;
}

