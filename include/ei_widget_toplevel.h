/**
 * @file	ei_widget_toplevel.h
 *
 * @brief 	definit toutes les fonctions associees au toplevel
 */


#ifndef EI_WIDGET_TOPLEVEL_H
#define EI_WIDGET_TOPLEVEL_H

#include "ei_widget.h"
#include "ei_draw_util.h"


/**
 * \brief  definition de la structure d'un toplevel, avec tous ses champs
 */

typedef struct ei_widget_toplevel_t
{
		struct ei_widget_t w;

		// Specifique à toplevel
		int border_width;
		ei_color_t color;
		char* title;
		ei_bool_t closable;
		ei_axis_set_t resizable;
		ei_size_t *min_size;
} ei_widget_toplevel_t;

/**
 * \brief	alloue la memoire necessaire pour creer un toplevel
 */
void* toplevelAllocfunc();



/**
 * \brief	libere la memoire occupee par un toplevel
 *
 * @param  widget     le toplevel qu'on veut liberer
 */
void toplevelReleasefunc(struct ei_widget_t* widget);




/**
 * \brief	dessine le toplevel
 *
 * @param  widget     le toplevel qu'on veut dessiner
 * 
 * @param  surface    la surface ou on dessine le toplevel
 *
 * @param pick_surface   la surface de picking
 *
 * @param clipper      le rectangle qui limite l'endroit ou on peut dessiner
 */
void toplevelDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);





/**
 * \brief	mets a jour les parametres du toplevel en lui affectant des valeurs par defaut
 *
 * @param  widget     le toplevel qu'on veut mettre a jour
 */
void toplevelSetdefaultsfunc(struct ei_widget_t* widget);




void toplevelGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect);

#endif
