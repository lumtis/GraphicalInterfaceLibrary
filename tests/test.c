#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ei_draw_util.h"
#include "ei_types.h"
#include "ei_draw.h"
#include "hw_interface.h"

int ei_main(int argc, char* argv[])
{
  ei_rect_t rect;
  ei_point_t centre = {200,200};
  ei_color_t color;
  color.red = 255;
  color.green = 0;
  color.blue = 0;
  color.alpha = 255;
  ei_size_t s = {640,480};
  ei_surface_t surface = hw_create_window(&s,EI_FALSE);
  ei_linked_point_t* test = malloc(sizeof(struct ei_linked_point_t));
  rect.top_left.x =100;
  rect.top_left.y =100 ;
  rect.size.width = 400;
  rect.size.height = 300;
  
  test = round_and_rectangular_frame(rect,15);

  hw_init();
  hw_surface_lock(surface);
  draw_toplevel(rect,1,surface,NULL);
  //ei_draw_polygon(surface,test,color,NULL);
  //getchar();
   
   hw_surface_unlock(surface);
  hw_surface_update_rects(surface, NULL);
  getchar(); 
  hw_quit();
  return (EXIT_SUCCESS);
}
