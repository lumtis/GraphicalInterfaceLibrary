
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "ei_widget_frame.h"

void* frameAllocfunc()
{
    // calloc initialise automatiquement les données à 0
    return calloc(1, sizeof(ei_widget_frame_t));
}

void frameReleasefunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;

    // on libere tout les membres qui ont ete alloués
    if(wf->text != NULL)
        free(wf->text);
    if(wf->img_rect != NULL)
        free(wf->img_rect);
    //if(wf->img != NULL)
        //free(wf->img);
}

void frameDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{
    ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;
    ei_linked_point_t* cadre = getCadre(widget);
    ei_linked_point_t* bordure;
      
    // Couleurs  de relief avec alpha au milieu
    ei_color_t white = {0xF0, 0xF0, 0xF0, 0x70};
    ei_color_t black  = {0x10, 0x10, 0x10, 0x70};
    ei_color_t pickColor;
    //ei_color_t grey  = {0x70, 0x70, 0x70, 0xFF};
    
    /*
    // On dessine un relief si le bord est supérieur à 0
    if (wf->border_width > 0)
    {
    bordure = getBordure(widget, wf->border_width);

        // Différents cas de bordure
        switch (wf->relief)
        {
  	        case (ei_relief_none): // Pas de bordure
      	        break;
  	        case (ei_relief_raised): // Bordure plus claire
            	  ei_draw_polygon(surface, bordure, white, clipper);
            	  ei_draw_polygon(surface, bordure, wf->color, clipper);
            	  //ei_draw_polyline(surface, cadre_bg, grey, clipper);
            	  break;
        	  case (ei_relief_sunken): // Bordure plus foncée
            	  ei_draw_polygon(surface, bordure, black, clipper);
            	  ei_draw_polygon(surface, bordure, wf->color, clipper);
            	  //ei_draw_polyline(surface, cadre_bg, grey, clipper);
            	  break;
        }
        // Libération liste
        freeLinkedPoint(bordure);
    }
    */

    // Dessin du cadre
    hw_surface_lock(surface);    
    ei_draw_polygon(surface, cadre, wf->color, clipper);
    hw_surface_unlock(surface);
    hw_surface_update_rects(surface, NULL);
    
    //ei_draw_polyline(surface, cadre, gris, clipper);
    // Offsreen
    //pickColor = *(widget->pick_color);
    //ei_draw_polygon(pick_surface, cadre, pickColor, clipper);

    freeLinkedPoint(cadre);

    // Texte
    if(wf->text != NULL)
        drawTextWidget(surface, widget, wf, clipper);

    // Image
    if(wf->img != NULL)
        drawImgWidget(surface, widget, wf);
}


void frameSetdefaultsfunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;

    wf->border_width = 0;
    wf->color = ei_default_background_color;
    wf->relief = ei_relief_none;
    wf->text = NULL;
    wf->text_font = ei_default_font;
    wf->text_color = ei_font_default_color;
    wf->text_anchor = ei_anc_center;
    wf->img = NULL;
    wf->img_rect = NULL;
    wf->img_anchor = ei_anc_center;
    
    // Pour un frame le content_rect est egal au screen_location
    widget->content_rect = &(widget->screen_location);
}


void frameGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}
