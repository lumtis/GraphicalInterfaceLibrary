#ifndef EI_WIDGET_FRAME_H
#define EI_WIDGET_FRAME_H

#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_types.h"
#include "ei_draw_util.h"

typedef struct ei_widget_frame_t
{
    struct ei_widget_t w;

    // Specifique à frame
    int border_width;
    ei_color_t	color;
    ei_relief_t relief;
    char* text;
    ei_font_t text_font;
    ei_color_t text_color;
    ei_anchor_t text_anchor;
    ei_surface_t	img;
    ei_rect_t*	img_rect;
    ei_anchor_t img_anchor;
} ei_widget_frame_t;


void* frameAllocfunc();
void frameReleasefunc(ei_widget_t* widget);
void frameDrawfunc(ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);
void frameSetdefaultsfunc(ei_widget_t* widget);
void frameGeomnotifyfunc(ei_widget_t* widget, ei_rect_t rect);

#endif
