/**
* @file Definie toute  les fonctions de callbacks internes
**/


#ifndef EI_INTERNCALLBACK
#define EI_INTERNCALLBACK

struct ei_widget_t* widget;
struct ei_event_t* event;


// general
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
inline ei_bool_t isIn(ei_point_t p, ei_rect_t r)
{
    if(p.x >= r.top_left.x && p.x <= r.top_left.x + r.size.width && p.y >= r.top_left.y && p.y <= r.top_left.y + r.size.height)
	return EI_TRUE;
    else
	return EI_FALSE;
}

ei_point_t getCurrent();
ei_point_t getLast();

#endif