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
  ei_color_t* color = malloc(sizeof(struct ei_color_t*));
  color->red = 255;
  color->green = 0;
  color->blue = 0;
  color->alpha = 255;
  ei_size_t s = {640,480};
  ei_surface_t surface = hw_create_window(&s,EI_FALSE);

  rect.top_left.x = 50;
  rect.top_left.y = 100;
  rect.size.width = 200;
  rect.size.height = 100;
  
  hw_init();
  hw_surface_lock(surface);
  
    ei_linked_point_t* test = malloc(sizeof(struct  ei_linked_point_t));
    
    test = rectangular_frame(rect,EI_TRUE,EI_FALSE);
    ei_linked_point_t* test2 = malloc(sizeof(struct  ei_linked_point_t));
    test2 =rectangular_frame(rect,EI_FALSE,EI_TRUE);
    //ei_linked_point_t* test3 = malloc(sizeof(struct  ei_linked_point_t));
   
    //test = rounded_frame(rect,30,EI_FALSE,EI_TRUE);
    //test = arc(centre,10,90,180,100);
    ei_draw_polygon(surface,test,*color,NULL);
    ei_draw_polygon(surface,test2,*color,NULL);
    //draw_button(rect,20,EI_TRUE,surface,10);
    //getchar();
    //draw_button(rect,20,EI_FALSE,surface,10);
    hw_surface_unlock(surface);
    hw_surface_update_rects(surface, NULL);
    
  getchar();
  hw_quit();
  return (EXIT_SUCCESS);
}
