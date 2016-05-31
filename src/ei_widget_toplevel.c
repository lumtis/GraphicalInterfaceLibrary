
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

    if(wtl->title != NULL)
        free(wtl->title);
    if(wtl->min_size != NULL)
        free(wtl->min_size);
}


void toplevelDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{

}


void toplevelSetdefaultsfunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

    wtl->border_width = 4;
    wtl->color = ei_default_background_color;
    wtl->title = malloc(strlen("Toplevel") + 1);
    strcpy(wtl->title, "Toplevel");
    wtl->closable = EI_TRUE;
    wtl->resizable = ei_axis_both;
    wtl->min_size = malloc(sizeof(ei_size_t));
    wtl->min_size->width = 160;
    wtl->min_size->height = 120;
}


void toplevelGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}
