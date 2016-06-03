/**
* @file Definie toute  les fonctions de callbacks internes
**/


#ifndef EI_INTERNCALLBACK
#define EI_INTERNCALLBACK

struct ei_widget_t* widget;
struct ei_event_t* event;


// Button
ei_bool_t pushButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


// Top level
ei_bool_t moveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t pushMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

ei_bool_t pushCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

ei_bool_t pushResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t releaseResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);
ei_bool_t resizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);

#endif