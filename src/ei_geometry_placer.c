/**
 *  @file	ei_geometry_placer.h
 *  @brief	Manages the positionning and sizing of widgets on the screen.
 *
 *  \author
 *
 */

#include "ei_geometry_placer.h"

void placerRunfunc(struct ei_widget_t*	widget) //recalcule la position du widget dans son parent
{
     struct ei_widget_t* parent = widget->parent;      
     struct ei_anchor_t* anc = parent->geom_params->anchor;
     int* x = parent->geom_params->x;
     int* y = parent->geom_params->y;
     int* w = parent->geom_params->width;
     int* h = parent->geom_params->height;
     float* rx = parent->geom_params->rel_x;
     float* ry = parent->geom_params->rel_y;
     float*	rw = parent->geom_params->rel_width;
     float*	rh = parent->geom_params->rel_height;

     ei_place(widget,anc,&x,&y,&w,&h,&rx,&ry,&rw,&rh);

}



void placerReleasefunc(struct ei_widget_t* widget)
{

}
