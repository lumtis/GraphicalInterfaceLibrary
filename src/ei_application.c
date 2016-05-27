/**
 *  @file	ei_application.c
 *  @brief	Manages the main steps of a graphical application: initialization, main window,
 *		main loop, quitting, resource freeing.
 *
 *  \author 
 *
 */

#include "ei_application.h"

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
  hw_init();
  hw_create_window(main_window_size,fullscreen);
  hw_quit();
}

void ei_app_free()
{
  return;
}

void ei_app_run()
{
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


