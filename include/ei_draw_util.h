/**
* @file ei_draw_util.h
* @brief definit les fonctions utilitaires pour le dessin
* \author
* L.Bertrand, T.Benjelloun, E.Quenton
*/

#ifndef EI_DRAW_UTIL_H
#define EI_DRAW_UTIL_H

#include "hw_interface.h"
#include "ei_types.h"


struct ei_widget_frame_t;
struct ei_widget_t;


/**
 * \brief      calcule la distance entre deux points
 *
 * @param     t1      premier point
 *
 * @param     t2      deuxieme point
 *
 * @return            la distance entre t1 et t2
 */
int distPoint(ei_point_t t1, ei_point_t t2);



/**
 * \brief  calcule le minimum de deux entiers
 *
 * @param   a      premier entier
 *
 * @param   b      deuxieme entier
 *
 * @return         le minimum entre a et b
 */
int min(int a, int b);



/**
 * \brief       calcule le maximum de deux entiers
 *
 * @param   a      premier entier
 *
 * @param   b      deuxieme entier
 *
 * @return         le maximum entre a et b
 */
int max(int a, int b);

// Fonctions points chainées


/**
 * \brief         libere une liste chainee de points
 *
 * @param   l     le premier point de la liste
 */
void freeLinkedPoint(ei_linked_point_t* l);



/**
 * \brief         ajoute un point en fin de liste chainee
 *
 * @param   l     le premier point de la liste; pointeur vers une liste
 *
 * @param   p     le point a ajouter; de type point
 *
 * @return        le premier point de la liste
 */
ei_linked_point_t* addLinkedPoint(ei_linked_point_t* l, ei_point_t p);




/**
 * \brief        retourne le dernier point d'une liste chainee. Parcourt la liste
 *
 * @param   l     le premier point de la liste; pointeur vers une liste
 *
 * @return       le dernier point de la liste
 */
ei_linked_point_t* lastPoint(ei_linked_point_t* l);



/**
 * \brief        parcourt une liste chainee et affiche tous les points de celle-ci
 *
 * @param   l     le premier point de la liste; pointeur vers une liste
 */
void printLinkedPoint(ei_linked_point_t* l);




// Texte et image


/**
 * \brief         dessine le texte d'un widget et le place en fonction de son ancrage
 *
 * @param   surface     la surface sur laquelle on dessinera le texte
 *
 * @param   widget      le widget dont on veut dessiner le texte
 *
 * @param   wf          un frame, dont le champ widget est "widget" 
 *
 * @param   clipper     le rectangle qui limite la surface où on peut dessiner
 */
void drawTextWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf,ei_rect_t* clipper);






/**
 * \brief         dessine l'image  d'un widget et le place en fonction de son ancrage
 *
 * @param   surface     la surface sur laquelle se place l'image
 *
 * @param   widget      le widget dont on veut dessiner l'image
 *
 * @param   wf          un frame, dont le champ widget est "widget" 
 */
void drawImgWidget(ei_surface_t surface,struct ei_widget_t* widget, ei_rect_t* clipper);

// Frame



/**
 * \brief         dessine un widget si c'est un bouton ou un cadre
 *
 * @param   widget           le widget que l'on veut dessiner 
 *
 * @param   surface          la surface ou on dessine
 *
 * @param   clipper          le rectangle qui limite la surface ou on peut dessiner
 *
 * @param   enfoncer         si le widget est un bouton, booleen qui decide s'il doit etre enfonce ou non
 *
 * @param   isFrame          booleen qui indique si le widget est un frame ou un bouton (si false, bouton; si true, frame)
 *
 * @param   pick_surface     surface de picking
 */
void draw_frameButton(struct ei_widget_t* widget, ei_surface_t surface, ei_rect_t* clipper, ei_bool_t enfoncer, ei_bool_t isFrame, ei_surface_t pick_surface);

// Toplevel


/**
 * \brief         dessine un widget si c'est un toplevel
 *
 * @param   widget           le widget que l'on veut dessiner 
 *
 * @param   surface          la surface ou on dessine
 *
 * @param   clipper          le rectangle qui limite la surface ou on peut dessiner
 */

void draw_toplevel(struct ei_widget_t* widget,ei_surface_t surface, ei_rect_t* clipper, ei_surface_t pick_surface);


ei_rect_t realIntersection(ei_rect_t* r1, ei_rect_t* r2);


#endif
