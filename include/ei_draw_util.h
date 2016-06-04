/**
* Definie les fonctions utilitaires pour le dessin de point
**/

#ifndef EI_DRAW_UTIL_H
#define EI_DRAW_UTIL_H

#include "hw_interface.h"
#include "ei_types.h"


struct ei_widget_frame_t;
struct ei_widget_t;


int distPoint(ei_point_t t1, ei_point_t t2);
int min(int a, int b);
int max(int a, int b);

// Fonctions points chainées
void freeLinkedPoint(ei_linked_point_t* l);
ei_linked_point_t* addLinkedPoint(ei_linked_point_t* l, ei_point_t p);
ei_linked_point_t* lastPoint(ei_linked_point_t* l);

void printLinkedPoint(ei_linked_point_t* l);

// Texte et image
void drawTextWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf,ei_rect_t* clipper);
void drawImgWidget(ei_surface_t surface,struct ei_widget_t* widget,struct ei_widget_frame_t* wf);

// Frame
void draw_frameButton(struct ei_widget_t* widget, ei_surface_t surface, ei_rect_t* clipper, ei_bool_t enfoncer, ei_bool_t isFrame, ei_surface_t pick_surface);

// Toplevel
void draw_toplevel(struct ei_widget_t* widget,ei_surface_t surface, ei_rect_t* clipper);



#endif
