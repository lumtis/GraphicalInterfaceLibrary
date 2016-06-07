/**
* @file Definit toutes  les fonctions de callbacks internes
**/


#ifndef EI_INTERNCALLBACK
#define EI_INTERNCALLBACK

struct ei_widget_t* widget;
struct ei_event_t* event;


// general


/** \brief obtient la position actuelle de la souris
 *
 * @param widget
 * 
 * @param  event
 *
 * @param  user_param
 *
 * @return 
 */

ei_bool_t memorizePosition(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t quitEchap(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

// Button
ei_bool_t pushButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t isOutButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


// Top level
ei_bool_t pushToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

ei_bool_t releaseCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

ei_bool_t moveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

ei_bool_t moveResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


// Utilitaire
ei_bool_t isIn(ei_point_t p, ei_rect_t r);

ei_point_t getCurrent();
ei_point_t getLast();

#endif
