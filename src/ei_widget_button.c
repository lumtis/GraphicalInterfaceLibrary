
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ei_widget_button.h"


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
	    draw_frameButton(widget, surface, clipper, EI_FALSE, EI_FALSE);
	    break;
	case (ei_relief_sunken): // Bordure plus foncée
	    draw_frameButton(widget, surface, clipper, EI_TRUE, EI_FALSE);
	    break;
    }
    
    //ei_draw_polyline(surface, cadre, gris, clipper);
    // Offsreen
    pickColor = *(widget->pick_color);
    //ei_draw_polygon(pick_surface, cadre, pickColor, clipper);

    // Texte
    if(wb->text != NULL)
        drawTextWidget(surface, widget, wb, clipper);

    // Image
    if(wb->img != NULL)
        //drawImgWidget(surface, widget, wb);
    
    hw_surface_unlock(surface);
    //hw_surface_unlock(pick_surface);
    hw_surface_update_rects(surface, NULL);
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
