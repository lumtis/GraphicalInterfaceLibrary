
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ei_widget_toplevel.h"


void* toplevelAllocfunc()
{
    // calloc initialise automatiquement les données à 0
    return calloc(1, sizeof(ei_widget_toplevel_t));
}


void toplevelReleasefunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

    if(wtl->title != NULL)
        free(wtl->title);
    if(wtl->min_size != NULL)
        free(wtl->min_size);
}


void toplevelDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{
  ei_widget_toplevel_t* tpl = (ei_widget_toplevel_t*)widget;
  ei_color_t  pickColor = (*widget->pick_color);
  
  hw_surface_lock(surface);
  
  draw_toplevel(tpl,surface,clipper);
   hw_surface_unlock(surface);
    //hw_surface_unlock(pick_surface);
   hw_surface_update_rects(surface, NULL);

}


void toplevelSetdefaultsfunc(struct ei_widget_t* widget)
{
    // On convertie le widget pour effectuer les opérations
    ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

    wtl->border_width = 4;
    wtl->color = ei_default_background_color;
    wtl->title = malloc(strlen("Toplevel") + 1);
    strcpy(wtl->title, "Toplevel");
    wtl->closable = EI_TRUE;
    wtl->resizable = ei_axis_both;
    wtl->min_size = malloc(sizeof(ei_size_t));
    wtl->min_size->width = 160;
    wtl->min_size->height = 120;
}


void toplevelGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}



/**********************************************************************
***************** Events **********************************************
**********************************************************************/



ei_bool_t moveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}

ei_bool_t pushMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}

ei_bool_t releaseMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}


ei_bool_t pushCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}

ei_bool_t releaseCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}


ei_bool_t pushResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}

ei_bool_t releaseResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}

ei_bool_t resizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
  
}
