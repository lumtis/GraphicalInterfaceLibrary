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

  int* border_width,
  const ei_color_t*	color,
  int* corner_radius,
  ei_relief_t* relief,
  char** text,
  ei_font_t* text_font,
  ei_color_t*	text_color,
  ei_anchor_t* text_anchor,
  ei_surface_t*	img,
  ei_rect_t**	img_rect,
  ei_anchor_t* img_anchor,
  ei_callback_t* callback,
  void** user_param
}


void buttonDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{

}


void buttonSetdefaultsfunc(struct ei_widget_t* widget)
{

}


void buttonGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}
