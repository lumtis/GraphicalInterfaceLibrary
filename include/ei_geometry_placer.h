#ifndef EI_GEOMETRY_PLACER
#define EI_GEOMETRY_PLACER

#include "ei_geometrymanager.h"
#include "debug.h"
#include "ei_widget.h"

typedef struct ei_geometry_placer_t
{
	ei_geometrymanager_t manager;
	
	//specifique a placer
	
	ei_widget_t* widget;
	ei_anchor_t anchor;
	int x;
	int y;
	int width;
	int height;
	float rel_x;
	float rel_y;
	float rel_width;
	float rel_height;
	
} ei_geometry_placer_t;

void placerRunfunc(struct ei_widget_t*	widget);
void placerReleasefunc(struct ei_widget_t* widget);


#endif
