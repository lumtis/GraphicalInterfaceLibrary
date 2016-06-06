#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ei_draw_util.h"
#include "ei_types.h"
#include "ei_draw.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_widget_frame.h"
int ei_main(int argc, char* argv[])
{
  ei_rect_t rect;
  ei_linked_rect_t* rect1 = malloc(sizeof(struct ei_linked_rect_t));
  rect.top_left.x =100;
  rect.top_left.y =100 ;
  rect.size.width = 400;
  rect.size.height = 300;
  rect1 = &rect;
  ei_point_t centre = {200,200};
  ei_color_t color;
  color.red = 255;
  color.green = 0;
  color.blue = 0;
  color.alpha = 255;
  ei_anchor_t anc = ei_anc_north;
  ei_widget_t* w;
  ei_widget_frame_t* frame = malloc(sizeof(struct ei_widget_frame_t));
  ei_size_t s;
  ei_size_t s1 = {640,480};
  ei_surface_t surface1;
  ei_surface_t surface = hw_create_window(&s1,EI_FALSE);

  ei_frame_configure(ei_app_root_widget(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  ei_app_create();
  frame = ei_widget_create("frame",ei_app_root_widget());

  //frameSetdefaultsfunc(&(frame->w));
  //s = frame->w.requested_size;
   //surface1 = hw_image_load("misc/ball.png",surface);
  //ei_frame_configure(frame,&s,&color,NULL,NULL,NULL,NULL,NULL,NULL,&surface1,&rect1,&anc);
  //surface = hw_image_load("misc/ball.png",surface);
  //drawImgWidget(surface,ei_widget_create(frame,NULL),ei_widget_create(frame,NULL));
  hw_init();
  hw_surface_lock(surface);
  //drawImgWidget(surface,frame);

  hw_surface_unlock(surface);
  hw_surface_update_rects(surface, NULL);
  getchar(); 
  hw_quit();
  return (EXIT_SUCCESS);
}
