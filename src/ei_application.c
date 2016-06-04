/**
 *  @file	ei_application.c
 *  @brief	Manages the main steps of a graphical application: initialization, main window,
 *		main loop, quitting, resource freeing.
 *
 *  \author
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ei_application.h"
#include "debug.h"
#include "ei_widgetclass.h"
#include "ei_widget_frame.h"
#include "ei_global.h"
#include "ei_geometrymanager.h"
#include "ei_types.h"
#include "ei_event.h"
#include "ei_utils.h"


ei_widget_t * racine;
ei_surface_t window;
ei_surface_t windowpick;
ei_widget_t* tab_widget[256];
traitant* tab_event[ei_ev_last];
ei_linked_rect_t*  liste_rect = NULL;
ei_widget_t * focus ;





void traitement(ei_event_t event ,  ei_widget_t* widget )
{
  traitant* tmp = tab_event[event.type];
  while ( tmp != NULL )
  {
    if (tmp->widget== NULL)
    { 
      if( strcmp(tmp->tag ,"all" )==0)
	tmp->callback( widget , &(event) , tmp->user_param);
      if ( strcmp( tmp->tag , widget->wclass->name ) == 0 )
	tmp->callback(widget, &(event),tmp->user_param);
    }
    else 
    {
      if ( tmp->widget ==widget )
	tmp->callback(widget , &(event),tmp->user_param);
    }
    tmp=tmp->next;
  }
}


// Definie quand faut il quitter l'application
ei_bool_t quit = EI_FALSE;

// Curseur position
ei_point_t currentP;
ei_point_t lastP;


/*Libere une liste de rect*/
void freeLinkedRect(ei_linked_rect_t* l)
{
    ei_linked_rect_t* tmp1 = l;
    ei_linked_rect_t* tmp2;

    if(tmp1 == NULL)
        return;

    tmp2 = tmp1->next;

    while(tmp2 != NULL)
    {
        free(tmp1);
        tmp1 = tmp2;
        tmp2 = tmp1->next;
    }
}



void ei_app_run_rec(ei_widget_t* widget, ei_surface_t window, ei_surface_t windowpick, ei_rect_t* clipper)
{
    if(widget == NULL)
        return;
    
    if (clipper == NULL)
      widget->wclass->drawfunc(widget ,window, windowpick, widget->parent->content_rect);
    else 
      widget->wclass->drawfunc(widget ,window, windowpick, clipper);
    
    ei_app_run_rec(widget->next_sibling, window, windowpick,clipper);
    ei_app_run_rec(widget->children_head, window, windowpick,clipper);
}


// TODO : Implémenter fullscreen
void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{ 
    ei_color_t * coloracine;
  
    hw_init();
    for ( ei_eventtype_t i = ei_ev_none ; i < ei_ev_last ; i++)
      tab_event[i]=NULL;
    ei_frame_register_class();
    ei_button_register_class();
    ei_toplevel_register_class();
    ei_register_placer_manager();
    
    racine = frameAllocfunc();
    frameSetdefaultsfunc(racine);
    focus= ei_app_root_widget();
    coloracine=malloc(sizeof(ei_color_t));
    coloracine->red = 255;
    coloracine->green = 0;
    coloracine->blue = 0;
    coloracine->alpha = 255;
    
    // Identifiant
    racine->pick_color = coloracine;
    racine->wclass = ei_widgetclass_from_name("frame");
    racine->pick_id = 255;
    
    // Taille
    racine->requested_size = *main_window_size;
    racine->screen_location.top_left.x = 0;
    racine->screen_location.top_left.y = 0;
    racine->screen_location.size = *main_window_size;
    racine->content_rect = malloc(sizeof(ei_rect_t));
    *(racine->content_rect) = racine->screen_location;
    
    // Initialisation du tableau de widget 
    for ( int i =0 ; i <256 ; i++)
      tab_widget[i]=NULL;

    racine->geom_params = calloc(1, sizeof(ei_geometry_param_t));
    
    window = hw_create_window(main_window_size,fullscreen);
    windowpick = hw_surface_create(window,main_window_size, EI_TRUE);;
}


void ei_app_free()
{
    ei_widget_destroy(racine);
    hw_surface_free(window);
    
    // On termine le widget principale
    hw_quit();
  
    return;
}

void ei_app_run()
{
    ei_linked_rect_t * courant;
    ei_event_t event;
    
    // Premier dessin de la fenere entiere
    frameDrawfunc(racine, window, windowpick, racine->content_rect);
    ei_app_run_rec(racine->children_head, window, windowpick,NULL);
    
   while ( quit == EI_FALSE)
   {
    courant = liste_rect;
    hw_event_wait_next(&event);
    switch ( event.type )
    {
      case ei_ev_none:
      case ei_ev_app:
      case ei_ev_last : break;
      case ei_ev_keydown :
      case ei_ev_keyup :traitement( event, focus);break;
      case ei_ev_mouse_buttondown : focus = ei_widget_pick(&(event.param.mouse.where)); traitement(event, focus) ;break;
      case ei_ev_mouse_buttonup : 
      case ei_ev_mouse_move : traitement(event, ei_widget_pick(&(event.param.mouse.where)));break;
      
    }
    
    while ( courant != NULL)
    {
      ei_app_run_rec(racine->children_head, window, windowpick,&(courant->rect));
      courant=courant->next;
    }  
    freeLinkedRect(liste_rect);
  }  
}


void ei_app_invalidate_rect(ei_rect_t* rect)
{
    
    ei_linked_rect_t * new_rect = calloc(1, sizeof(ei_linked_rect_t));
    new_rect->rect = *rect;
    ei_linked_rect_t * tmp;
  
    if (liste_rect == NULL)
      liste_rect = new_rect;
    else
    {
      tmp=liste_rect;
      for(tmp=liste_rect;tmp->next != NULL; tmp =tmp->next);
      tmp->next= new_rect;
    }
}


ei_bool_t quitEchap(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    if(event->param.key.key_sym == SDLK_RETURN)
	ei_app_quit_request();
    return EI_TRUE;
}



void ei_app_quit_request()
{
    quit = EI_TRUE;
    return;
}

ei_widget_t* ei_app_root_widget()
{
    return racine;
}

ei_surface_t ei_app_root_surface()
{
    return window;
}


ei_bool_t memorizePosition(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
    lastP = currentP;
    currentP = event->param.mouse.where;
    
    return EI_TRUE;
}

ei_point_t getCurrent()
{
    return currentP;
}

ei_point_t getLast()
{
    return lastP;
}
