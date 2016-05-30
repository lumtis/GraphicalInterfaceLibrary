/**
 *  @file	ei_application.c
 *  @brief	Manages the main steps of a graphical application: initialization, main window,
 *		main loop, quitting, resource freeing.
 *
 *  \author 
 *
 */

#include "ei_application.h"
#include "debug.h"
#include "ei_widgetclass.h"

ei_widget_frame_t * racine ;

ei_surface_t window;

ei_surface_t windowpick;


void ei_app_run_rec(ei_widget *widget, ei_surface_t window, ei_surface_t windowpick)
{
  if (widget== NULL) 
    return ;
  
  widget->wclass->drawfunc(widget ,window,windowpick,widget->parent->content_rect);
  ei_app_run_rec(widget->next_sibling, window,windowpick);
  ei_app_run_rec(widget->children_head,window,windowpick); 
		 
  
}

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
  hw_init();
  racine=frameAllocfunc();
  frameSetdefaultsfunc(racine);
  ei_frame_register_class();
  window=hw_create_window(main_window_size,fullscreen);
  windowpick=hw_create_window(main_window_size,fullscreen);
  
  // Boucle principale d'entrée
  ei_app_run();
  
  // On termine le widget principale
  hw_quit();
  
  ei_app_free();
}


void ei_app_free()
{
  
  return;
}

void ei_app_run()
{
  frameDrawfunc(racine, window, windowpick,racine->content_rect);
  ei_app_run_rec(racine->children_head, window,windowpick);
  getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{
  return;
}

void ei_app_quit_request()
{
  return;
}

ei_widget_t* ei_app_root_widget()
{
  return;
}

ei_surface_t ei_app_root_surface()
{
  return;
}


