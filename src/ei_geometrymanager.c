/**
 *  @file	ei_geometrymanager.h
 *  @brief	Manages the positionning and sizing of widgets on the screen.
 *
 *  \author
 *
 */

#include "ei_geometrymanager.h"
#include "debug.h"
#include "ei_geometry_placer.h"
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



ei_geometrymanager_t* ei_geometrymanager_from_name(ei_geometrymanager_name_t name)
{
   ei_geometrymanager_t* tmp;
  
    for(tmp = gm; tmp != NULL; tmp = tmp->next)
    {
	if(!strcmp(tmp->name, name))
	    return tmp;
    }
    
    PRINT_DEBUG("ei_geometrymanager_from_name : classe non trouvee");
    
    return NULL;
}



void ei_geometrymanager_unmap(ei_widget_t* widget)
{  
  widget->screen_location.top_left.x = 0; //place le widget a la position (0,0)
  widget->screen_location.top_left.y = 0;
  widget->screen_location.size = 0; // la taille du widget est reduite a 0
  widget->geom_params->releasefunc(); //on appelle la fonction release du gestionnaire de geometrie qui gere le widget
  free(widget->geom_params); //on libere les parametres geometriques du widget
}



void ei_register_placer_manager()
{
  ei_geometrymanager_t* placer = malloc(sizeof(struct(ei_geometrymanager_t));
  strcpy(placer->name, "placer");
  	placer->runfunc=placerRunfunc;
	placer->releasefunc=placerReleasefunc;
	placer->next=NULL;
	
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
  
}

