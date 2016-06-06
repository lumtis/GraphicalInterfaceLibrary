
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ei_widget_button.h"
#include "ei_widget_frame.h"
#include "ei_application.h"
#include "ei_event.h"
#include "ei_interncallback.h"


void* buttonAllocfunc()
{
  // calloc initialise automatiquement les données à 0
  return calloc(1, sizeof(ei_widget_button_t));
}


void buttonReleasefunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_button_t* wb = (ei_widget_button_t*)widget;

    frameReleasefunc(widget);
    if(wb->user_param != NULL)
        free(wb->user_param);
}


void buttonDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{
    ei_widget_button_t* wb = (ei_widget_button_t*)widget;
      
    ei_color_t pickColor;
    
    hw_surface_lock(surface);
    //hw_surface_lock(pick_surface);
    
    switch (wb->relief)
    {
	case (ei_relief_none): // Pas de bordure
	case (ei_relief_raised): // Bordure plus claire
	    draw_frameButton(widget, surface, clipper, EI_FALSE, EI_FALSE, pick_surface);
	    break;
	case (ei_relief_sunken): // Bordure plus foncée
	    draw_frameButton(widget, surface, clipper, EI_TRUE, EI_FALSE, pick_surface);
	    break;
    }

    // Texte
    if(wb->text != NULL)
        drawTextWidget(surface, widget, (ei_widget_frame_t*)wb, clipper);

    // Image
    if(wb->img != NULL)
        drawImgWidget(surface, widget, wb);
    
    hw_surface_unlock(surface);
    //hw_surface_unlock(pick_surface);
}


void buttonSetdefaultsfunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_button_t* wb = (ei_widget_button_t*)widget;

    frameSetdefaultsfunc(widget);
    wb->corner_radius = k_default_button_corner_radius;
    wb->callback = NULL;
    wb->user_param = NULL;
}


void buttonGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}


// Obtient le relief inverse du boutton lorsqu'il est pressé
ei_relief_t reliefInvese(ei_relief_t r)
{
    switch(r)
    {
      case ei_relief_none :
	    return ei_relief_none;
      case ei_relief_raised :
	    return ei_relief_sunken;
      case ei_relief_sunken :
	    return ei_relief_raised;
    }
    
    return ei_relief_none;
}


// Defini si un point est dans un rectangle
ei_bool_t isIn(ei_point_t p, ei_rect_t r)
{
    if(p.x >= r.top_left.x && p.x <= r.top_left.x + r.size.width && p.y >= r.top_left.y && p.y <= r.top_left.y + r.size.height)
	return EI_TRUE;
    else
	return EI_FALSE;
}


/**********************************************************************
***************** Events **********************************************
**********************************************************************/


ei_bool_t pushButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_button_t* wb = (ei_widget_button_t*)widget;
    
    // On change le relief lorsqu'il est pressé
    wb->relief = reliefInvese(wb->relief);
    
    printf("test\n");
    
    // On creer des evenements pour detecer quand est ce qu'on change le relief
    ei_bind(ei_ev_mouse_move , NULL, "all", isOutButton, widget);
    ei_bind(ei_ev_mouse_buttonup , NULL, "all", releaseButton, widget);
    
    // on devra redessiner la partie
    ei_app_invalidate_rect(&(widget->screen_location));
    
    return EI_TRUE;
}


ei_bool_t releaseButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_button_t* wb = (ei_widget_button_t*)user_param;
    ei_widget_t* w = (ei_widget_t*)user_param;
  
    // Si le curseur est actuellement dans le button on change son relief
    if(isIn(getCurrent(), w->screen_location) == EI_TRUE)
    {
	wb->relief = reliefInvese(wb->relief);
	
	// on devra redessiner la partie
	ei_app_invalidate_rect(&(widget->screen_location));
    }
    
    // On retire mes evenements precedents
    ei_unbind(ei_ev_mouse_move , NULL, "all", isOutButton, w);
    ei_unbind(ei_ev_mouse_buttonup , NULL, "all", releaseButton, w);
    
    return EI_TRUE;
}


ei_bool_t isOutButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    ei_widget_button_t* wb = (ei_widget_button_t*)user_param;
    ei_widget_t* w = (ei_widget_t*)user_param;
    
    // Si on sort du bouton on inverse le relief et inversement
    if(isIn(getCurrent(), w->screen_location) == EI_TRUE && isIn(getLast(), w->screen_location) == EI_FALSE)
    {
	wb->relief = reliefInvese(wb->relief);
	
	// on devra redessiner la partie
	ei_app_invalidate_rect(&(w->screen_location));
    }
    else if(isIn(getCurrent(), w->screen_location) == EI_FALSE && isIn(getLast(), w->screen_location) == EI_TRUE)
    {
	wb->relief = reliefInvese(wb->relief);
	
	// on devra redessiner la partie
	ei_app_invalidate_rect(&(w->screen_location));
    }
    
    return EI_TRUE;
}