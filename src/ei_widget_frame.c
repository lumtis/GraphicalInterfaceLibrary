
#include "ei_widget_fame.h"

void* frameAllocfunc()
{
    // calloc initialise automatiquement les données à 0
    return calloc(1, sizeof(ei_widget_frame_t));
}

void frameReleasefunc(struct ei_widget_t* widget)
{
  // On convertie le widget pour effectuer les opérations
  ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;

  int* border_width,
  const ei_color_t*	color,
	ei_relief_t* relief,
	char** text,
	ei_font_t* text_font,
	ei_color_t* text_color,
	ei_anchor_t* text_anchor,
	ei_surface_t*	img,
	ei_rect_t**	img_rect,
	ei_anchor_t* img_anchor
}

void frameDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{

}

void frameSetdefaultsfunc(struct ei_widget_t* widget)
{

}

void frameGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}
