
#include "ei_widget_fame.h"

void* frameAllocfunc()
{
    // calloc initialise automatiquement les données à 0
    return calloc(1, sizeof(ei_widget_frame_t));
}

void frameReleasefunc(struct ei_widget_t* widget)
{

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
