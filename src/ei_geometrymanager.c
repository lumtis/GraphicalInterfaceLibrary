/**
 *  @file	ei_geometrymanager.h
 *  @brief	Manages the positionning and sizing of widgets on the screen.
 *
 *  \author
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ei_geometrymanager.h"
#include "debug.h"
#include "ei_geometry_placer.h"
#include "ei_types.h"
#include "ei_application.h"


/**
 *  @var	gm
 *  @brief	Variable globale contenant un chainage de tous les gm
 */
ei_geometrymanager_t* gm = NULL;


void ei_geometrymanager_register(ei_geometrymanager_t* geometrymanager)
{
    ei_geometrymanager_t* tmp;

    // s'il n'y a pas de classe on la definit comme la premiere
    if(gm == NULL)
	     gm = geometrymanager;
    else
    {
      	tmp = gm;
      	for(tmp = gm; tmp->next != NULL; tmp = tmp->next);
	  tmp->next = geometrymanager;
    }
}

ei_geometrymanager_t* ei_geometrymanager_from_name(ei_geometrymanager_name_t name)
{
    ei_geometrymanager_t* tmp;

    for(tmp=gm; tmp != NULL; tmp = tmp->next)
    {
	if(!strcmp(tmp->name, name))
	    return tmp;
    }

    PRINT_DEBUG("ei_geometrymanager_from_name : classe non trouvee");

    return NULL;
}



void ei_geometrymanager_unmap(ei_widget_t* widget)
{
    ei_app_invalidate_rect(&(widget->screen_location));
    widget->screen_location.top_left.x = 0; //place le widget a la position (0,0)
    widget->screen_location.top_left.y = 0;
    widget->screen_location.size.height = 0; // la taille du widget est reduite a 0
    widget->screen_location.size.width = 0;
    widget->geom_params->manager->releasefunc(widget); //on appelle la fonction release du gestionnaire de geometrie qui gere le widget
    free(widget->geom_params); //on libere les parametres geometriques du widget
    widget->geom_params = NULL;
}



void ei_register_placer_manager()
{
    ei_geometrymanager_t* placer = calloc(1, sizeof(ei_geometrymanager_t));
    strcpy(placer->name, "placer");
    placer->runfunc = placerRunfunc;
    placer->releasefunc = placerReleasefunc;
    placer->next = NULL;

    ei_geometrymanager_register(placer);
}


void	ei_place	(ei_widget_t*		widget,
			 ei_anchor_t*		anchor,
			 int*			x,
			 int*			y,
			 int*			width,
			 int*			height,
			 float*			rel_x,
			 float*			rel_y,
			 float*			rel_width,
			 float*			rel_height)
{
    ei_geometrymanager_t* placeur = ei_geometrymanager_from_name("placer");
    ei_geometry_placer_t* manager;
    ei_bool_t redef = EI_FALSE;
    
    if(widget->geom_params == NULL)
	widget->geom_params = calloc(1, sizeof(ei_geometry_param_t));
    
    // widget n'a pas forcement de manager placeur
    if(widget->geom_params->manager == NULL)
	redef = EI_TRUE;
    else if(strcmp(widget->geom_params->manager->name, "placer") != 0)
    {
	widget->geom_params->manager->releasefunc(widget);
	redef = EI_TRUE;
    }
    
    // Le manager de geometrie est à redefinir
    if(redef == EI_TRUE)
    {
	widget->geom_params->manager = calloc(1, sizeof(ei_geometry_placer_t));
	*(widget->geom_params->manager) = *placeur;
	
	manager = (ei_geometry_placer_t*)widget->geom_params->manager;
	manager->x = widget->screen_location.top_left.x;
	manager->y = widget->screen_location.top_left.y;
	manager->width = widget->screen_location.size.width;
	manager->height = widget->screen_location.size.height;
    }
    else
	manager = (ei_geometry_placer_t*)widget->geom_params->manager;
    
    //Mis à jour des membres du placeur
    if (anchor != NULL)
        manager->anchor = *anchor;
    if (x != NULL)
        manager->x = *x;
    if (y != NULL)
        manager->y = *y;
    if (width != NULL)
        manager->width = *width;
    if (height != NULL)
    {
	if(strcmp(widget->wclass->name, "toplevel") == 0)
	    *height += 10;
        manager->height = *height;
    }
    if (rel_x != NULL)
        manager->rel_x = *rel_x;
    if (rel_y != NULL)
        manager->rel_y = *rel_y;
    if (rel_width != NULL)
        manager->rel_width = *rel_width;
    if (rel_height != NULL)
        manager->rel_height = *rel_height;
    
    // Met à jour les modifs
    widget->geom_params->manager->runfunc(widget);
}
