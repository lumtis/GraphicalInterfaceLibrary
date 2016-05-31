/**
* Definie les fonctions utilitaires pour le dessin de point
**/

#ifndef EI_DRAW_UTIL_H
#define EI_DRAW_UTIL_H

int min(int a, int b);

// Fonctions points chainées
ei_linked_point_t* getCadre(ei_widget_t* widget);
ei_linked_point_t* getBordure(ei_widget_t* widget, int bord);
void freeLinkedPoint(ei_linked_point_t* l);
ei_linked_point_t* addLinkedPoint(ei_linked_point_t* l, ei_point_t p);
ei_linked_point_t* lastPoint(ei_linked_point_t* l);

// Fonctions dessin
void drawTextWidget(ei_surface_t surface, ei_widget_t* widget, ei_widget_frame_t* wf, ei_rect_t* clipper);
void drawImgWidget(ei_surface_t surface, ei_widget_t* widget, ei_widget_frame_t* wf);
void arc(ei_point_t centre, int rayon, int angleDebut, int angleFin,int nbPoints);

#endif
