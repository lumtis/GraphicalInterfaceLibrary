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
#include "ei_application.h"
#include "debug.h"
#include "ei_widgetclass.h"
#include "ei_widget_frame.h"
#include "ei_global.h"

ei_widget_t * racine;
ei_surface_t window;
ei_surface_t windowpick;
ei_widget_t* tab_widget[256];


void ei_app_run_rec(ei_widget_t* widget, ei_surface_t window, ei_surface_t windowpick)
{
    if(widget == NULL)
        return;

    widget->wclass->drawfunc(widget ,window, windowpick, widget->parent->content_rect);
    ei_app_run_rec(widget->next_sibling, window,windowpick);
    ei_app_run_rec(widget->children_head,window,windowpick);
}


void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{ 
    ei_color_t * coloracine;
  
    hw_init();
    // initialisation de la racine frame 
    ei_frame_register_class();
    racine = frameAllocfunc();
    frameSetdefaultsfunc(racine);
    
    coloracine=malloc(sizeof(ei_color_t));
    coloracine->red = 255;
    coloracine->green = 0;
    coloracine->blue = 0;
    coloracine->alpha = 255;
    racine->pick_color = coloracine;
    
    // initialisation du tableau de widget 
    for ( int i =0 ; i <256 ; i++)
      tab_widget[i]=NULL;

    window = hw_create_window(main_window_size,fullscreen);
    windowpick = hw_create_window(main_window_size,fullscreen);
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
    frameDrawfunc(racine, window, windowpick, racine->content_rect);
    ei_app_run_rec(racine->children_head, window, windowpick);
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
    return racine;
}

ei_surface_t ei_app_root_surface()
{
    return window;
}
