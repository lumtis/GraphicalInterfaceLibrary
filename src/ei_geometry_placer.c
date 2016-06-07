/**
 *  @file	ei_geometry_placer.h
 *  @brief	Manages the positionning and sizing of widgets on the screen.
 *
 *  \author
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ei_geometry_placer.h"
#include "ei_application.h"
#include "ei_utils.h"


void placerRunfunc(struct ei_widget_t*	widget)
{
    ei_geometry_placer_t* pl;
    ei_rect_t parentRect;
    ei_widget_t* child;
    
    // Il faut que le widget possède un manager de geometrie de type placer
    if(widget->geom_params == NULL)
	return;
    if(widget->geom_params->manager == NULL)
	return;
    if(strcmp(widget->geom_params->manager->name, "placer") != 0)
	return;
    
    pl = (ei_geometry_placer_t*)widget->geom_params->manager;
    
    // Si c'est la fenetre racine ses coordonnées reste toujours à (0,0)
    if(widget == ei_app_root_widget())
	return;
    else
	parentRect = *(widget->parent->content_rect);
	
    // On modifie la taille du widget
    widget->screen_location.size.width = pl->rel_width * parentRect.size.width + pl->width;
    widget->screen_location.size.height = pl->rel_height * parentRect.size.height + pl->height;
    
    // On modifie sa position en fonction de son anchor
    switch(pl->anchor)
    {
	case ei_anc_none:	// Pas d'ancrage -> nord ouest
	case ei_anc_northwest:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y;
	    break;
	case ei_anc_north:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x - (widget->screen_location.size.width)/2;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y;
	    break;
	case ei_anc_northeast:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x - widget->screen_location.size.width;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y;
	    break;
	case ei_anc_east:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x - widget->screen_location.size.width;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y - (widget->screen_location.size.height)/2;
	    break;
	case ei_anc_southeast:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x - widget->screen_location.size.width;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y - widget->screen_location.size.height;
	    break;
	case ei_anc_south:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x - (widget->screen_location.size.width)/2;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y - widget->screen_location.size.height;
	    break;
	case ei_anc_southwest:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y - widget->screen_location.size.height;
	    break;
	case ei_anc_west:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y - (widget->screen_location.size.height)/2;
	    break;
	case ei_anc_center:
	    widget->screen_location.top_left.x = parentRect.top_left.x + pl->rel_x * parentRect.size.width + pl->x - (widget->screen_location.size.width)/2;
	    widget->screen_location.top_left.y = parentRect.top_left.y + pl->rel_y * parentRect.size.height + pl->y - (widget->screen_location.size.height)/2;
	    break;
    }
    
    // On modifie son content_rect en fonction de sa classe
    widget->wclass->geomnotifyfunc(widget, widget->screen_location);
    
    // On deplace les widget enfant
    child = widget->children_head;
    while(child != NULL)
    {
	placerRunfunc(child);
	child = child->next_sibling;
    }
}



void placerReleasefunc(struct ei_widget_t* widget)
{
    if(widget != NULL)
    {
	if(widget->geom_params != NULL)
	{
	    if(widget->geom_params->manager != NULL)
	    {
		free(widget->geom_params->manager);
		widget->geom_params->manager = NULL;
	    }
	}
    }
}
