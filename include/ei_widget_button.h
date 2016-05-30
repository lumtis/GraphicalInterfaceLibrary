#ifndef EI_WIDGET_BUTTON_H
#define EI_WIDGET_BUTTON_H

#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_widget_frame.h"

typedef struct ei_widget_button_t
{
	struct ei_widget_t w;

	// Specifique à button
	int border_width;
	ei_color_t color;
	ei_relief_t relief;
	char* text;
	ei_font_t text_font;
	ei_color_t text_color;
	ei_anchor_t text_anchor;
	ei_surface_t img;
	ei_rect_t* img_rect;
	ei_anchor_t img_anchor;
	int corner_radius;
	ei_callback_t callback;
	void* user_param;
} ei_widget_button_t;


void* buttonAllocfunc();
void buttonReleasefunc(struct ei_widget_t* widget);
void buttonDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);
void buttonSetdefaultsfunc(struct ei_widget_t* widget);
void buttonGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect);

#endif
