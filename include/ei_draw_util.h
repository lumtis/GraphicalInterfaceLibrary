/**
* Definie les fonctions utilitaires pour le dessin de point
**/

#ifndef EI_DRAW_UTIL_H
#define EI_DRAW_UTIL_H

#include "hw_interface.h"
#include "ei_types.h"


struct ei_widget_frame_t;
struct ei_widget_t;


// Fonctions points chainées
ei_linked_point_t* getCadre(struct ei_widget_t* widget);
ei_linked_point_t* getBordure(struct ei_widget_t* widget, int bord);
void freeLinkedPoint(ei_linked_point_t* l);
ei_linked_point_t* addLinkedPoint(ei_linked_point_t* l, ei_point_t p);
ei_linked_point_t* lastPoint(ei_linked_point_t* l);

void printLinkedPoint(ei_linked_point_t* l);

// Fonctions dessin
void drawTextWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf,ei_rect_t* clipper);
void drawImgWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf);
ei_linked_point_t* arc(ei_point_t centre, int rayon, int angleDebut, int angleFin,int nbPoints);
ei_linked_point_t* rounded_frame(ei_rect_t rect, int rayon, ei_bool_t partieHaute, ei_bool_t partieBasse);
ei_linked_point_t* lastPoint(ei_linked_point_t* l);

int min(int a, int b);



#endif
