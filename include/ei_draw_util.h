/**
* Definie les fonctions utilitaires pour le dessinage de point
**/

#ifndef EI_DRAW_UTIL_H
#define EI_DRAW_UTIL_H

#include "hw_interface.h"
#include "ei_types.h"


struct ei_widget_frame_t;
struct ei_widget_t;
struct ei_rect_t;
struct ei_linked_point_t;



// Fonctions points chainées
struct ei_linked_point_t* getCadre(struct ei_widget_t* widget);
struct ei_linked_point_t* getBordure(struct ei_widget_t* widget, int bord);
void freeLinkedPoint(struct ei_linked_point_t* l);
struct ei_linked_point_t* addLinkedPoint(struct ei_linked_point_t* l, ei_point_t p);

// Fonctions dessin
void drawTextWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf,struct ei_rect_t* clipper);
void drawImgWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf);

#endif
