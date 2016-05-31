#ifndef EI_WIDGET_TOPLEVEL_H
#define EI_WIDGET_TOPLEVEL_H

#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_draw_util.h"

typedef struct ei_widget_toplevel_t
{
		struct ei_widget_t w;

		// Specifique à toplevel
		int border_width;
		ei_color_t color;
		char* title;
		ei_bool_t closable;
		ei_axis_set_t resizable;
		ei_size_t *min_size;
} ei_widget_toplevel_t;


void* toplevelAllocfunc();
void toplevelReleasefunc(struct ei_widget_t* widget);
void toplevelDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);
void toplevelSetdefaultsfunc(struct ei_widget_t* widget);
void toplevelGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect);

#endif
