#include "ei_widget_toplevel.h"


void* toplevelAllocfunc()
{
  // calloc initialise automatiquement les données à 0
  return calloc(1, sizeof(ei_widget_toplevel_t));
}


void toplevelReleasefunc(struct ei_widget_t* widget)
{
  // On convertie le widget pour effectuer les opérations
  ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

  int* border_width,
  const ei_color_t*	color,
  char** title,
  ei_bool_t* closable,
  ei_axis_set_t* resizable,
  ei_size_t**	min_size
}


void toplevelDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{

}


void toplevelSetdefaultsfunc(struct ei_widget_t* widget)
{

}


void toplevelGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}
