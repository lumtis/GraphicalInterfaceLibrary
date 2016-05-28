#include "ei_widget_button.h"


void* buttonAllocfunc()
{
  // calloc initialise automatiquement les données à 0
  return calloc(1, sizeof(ei_widget_button_t));
}


void buttonReleasefunc(struct ei_widget_t* widget)
{

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
