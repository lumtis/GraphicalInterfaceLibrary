/**
*  Definie toute les variables globales necessaires au programme
**/

#ifndef EI_GLOBAL_H
#define Ei_GLOBAL_H
#include "ei_event.h"
#include "ei_widget.h"

extern ei_surface_t windowpick;
extern ei_widget_t* tab_widget[256];



typedef struct traitant {
	ei_widget_t*                widget ;
	ei_tag_t                    tag;
	ei_callback_t               callback;
	void *                      user_param;
	struct traitant*            next;
} traitant;

extern traitant* tab_event[ei_ev_last];

#endif

