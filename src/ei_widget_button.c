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
