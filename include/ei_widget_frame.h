/**
 *  @file	ei_widget_frame.h
 *  @brief	definit toutes les fonctions associees au frame
 */


#ifndef EI_WIDGET_FRAME_H
#define EI_WIDGET_FRAME_H

#include "ei_widget.h"
#include "ei_types.h"
#include "ei_draw_util.h"


/**
 * \brief  definition de la structure d'un frame, avec tous ses champs
 */


typedef struct ei_widget_frame_t
{
    struct ei_widget_t w;

    // Specifique à frame
    int border_width;
    ei_color_t	color;
    ei_relief_t relief;
    char* text;
    ei_font_t text_font;
    ei_color_t text_color;
    ei_anchor_t text_anchor;
    ei_surface_t	img;
    ei_rect_t*	img_rect;
    ei_anchor_t img_anchor;
} ei_widget_frame_t;




/**
 * \brief	alloue la memoire necessaire pour creer un frame
 */
void* frameAllocfunc();




/**
 * \brief	libere la memoire occupee par un frame
 *
 * @param  widget     le frame qu'on veut liberer
 */
void frameReleasefunc(struct ei_widget_t* widget);


/**
 * \brief	dessine le frame
 *
 * @param  widget     le frame qu'on veut dessiner
 * 
 * @param  surface    la surface ou on dessine le frame
 *
 * @param pick_surface   la surface de picking
 *
 * @param clipper      le rectangle qui limite l'endroit ou on peut dessiner
 */
void frameDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);



/**
 * \brief	mets a jour les parametres du frame en lui affectant des valeurs par defaut
 *
 * @param  widget     le frame qu'on veut mettre a jour
 */
void frameSetdefaultsfunc(struct ei_widget_t* widget);
void frameGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect);

#endif
