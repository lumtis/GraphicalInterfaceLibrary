/**
 * @file	ei_widget_button.h
 *
 * @brief 	definit toutes les fonctions associees au bouton
 */

#ifndef EI_WIDGET_BUTTON_H
#define EI_WIDGET_BUTTON_H

#include "ei_widget.h"
#include "ei_draw_util.h"



/**
 * \brief  definition de la structure d'un bouton, avec tous ses champs
 */

typedef struct ei_widget_button_t
{
		struct ei_widget_t w;

		// Specifique à button
		int border_width;
		ei_color_t color;
		ei_relief_t relief;
		char* text;
		ei_font_t text_font;
		ei_color_t text_color;
		ei_anchor_t text_anchor;
		ei_surface_t img;
		ei_rect_t* img_rect;
		ei_anchor_t img_anchor;
		int corner_radius;
		ei_callback_t callback;
		void* user_param;
} ei_widget_button_t;


/**
 * \brief	alloue la memoire necessaire pour creer un bouton
 */
void* buttonAllocfunc();

/**
 * \brief	libere la memoire occupee par un bouton
 *
 * @param  widget     le bouton qu'on veut liberer
 */
void buttonReleasefunc(struct ei_widget_t* widget);


/**
 * \brief	dessine le bouton
 *
 * @param  widget     le bouton qu'on veut dessiner
 * 
 * @param  surface    la surface ou on dessine le bouton
 *
 * @param pick_surface   la surface de picking
 *
 * @param clipper      le rectangle qui limite l'endroit ou on peut dessiner
 */
void buttonDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);



/**
 * \brief	mets a jour les parametres du bouton en lui affectant des valeurs par defaut
 *
 * @param  widget     le bouton qu'on veut mettre a jour
 */
void buttonSetdefaultsfunc(struct ei_widget_t* widget);



void buttonGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect);

#endif
