/**
 *  @file	ei_geometry_placer.h
 *  @brief	definit toutes les fonctions associees au placeur
 *
 *  \author
 * Bertrand, Benjelloun, Quenton
 */

#ifndef EI_GEOMETRY_PLACER
#define EI_GEOMETRY_PLACER

#include "ei_geometrymanager.h"
#include "debug.h"
#include "ei_widget.h"



/**
 * \brief    la structure qui regroupe les informations d'un placeur (type de geometrymanager)  
 */

typedef struct ei_geometry_placer_t
{
	ei_geometrymanager_t manager;
	
	//specifique a placer
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


/**
 * \brief     recalcule la position d'un widget dans son parent, en fonction de 
 *            sa position relative et sa position absolue
 *
 * @param widget      le widget dont on veut recalculer la position 
 */
void placerRunfunc(struct ei_widget_t*	widget);


/**
 * \brief      "relache" le widget, c est a dire que le widget  ne sera plus gere
 *             par le placeur. sa taille est remise a 0, sa position a (0,0) et ses parametres
 *             geometriques a NULL
 *
 * @param widget      le widget que l'on veut "liberer" 
 */
void placerReleasefunc(struct ei_widget_t* widget);


#endif
