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
if (widget == NULL)
  {
    return;
  }

if (widget->geomnotify) //si il n'y a pas eu modification on renvoie le widget tel quel
  {

  } 
else 
  {
      widget->requested_size =
      widget->screen_location = 
      widget->content_rec = parent->content_rec;
      ei_place(widget,,x,y,width,height,rel_x,rel_y,rel_width,rel_height);
  }

// TODO : implementer le reste de la fonction et voir quels parametres modifier
}





void placerReleasefunc(struct ei_widget_t* widget)
{
  ei_geometrymanager_unmap(widget); //Retire le widget de l'ecran
  
}