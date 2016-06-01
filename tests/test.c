#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ei_draw_util.h"
#include "ei_types.h"

int ei_main(int argc, char* argv[])
{
  ei_rect_t rect;
  rect.top_left.x = 5.0;
  rect.top_left.y = 5.0;
  rect.size.width = 80;
  rect.size.height = 100;
  draw_button(rect,20,EI_FALSE);

  return (EXIT_SUCCESS);
}
