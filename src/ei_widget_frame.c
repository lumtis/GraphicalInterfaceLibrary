
#include "ei_widget_fame.h"

void* frameAllocfunc()
{
    // calloc initialise automatiquement les données à 0
    return calloc(1, sizeof(ei_widget_frame_t));
}

void frameReleasefunc(struct ei_widget_t* widget)
{
  // On convertie le widget pour effectuer les opérations
  ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;

  // on libere tout les membres qui ont ete alloués
	if(wf->text != NULL)
    free(wf->text);
	if(wf->img_rect != NULL)
    free(wf->img_rect);
  if(wf->img != NULL)
    free(wf->img);
}

void frameDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)
{

}

void frameSetdefaultsfunc(struct ei_widget_t* widget)
{
  // On convertie le widget pour effectuer les opérations
  ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;

  wf->border_width = 0;
	wf->color = ei_default_background_color;
	wf->relief = ei_relief_none;
	wf->text = NULL;
	wf->text_font = ei_default_font;
	wf->text_color = ei_font_default_color;
	wf->text_anchor = ei_anc_center;
	wf->img = NULL;
	wf->img_rect = NULL;
	wf->img_anchor = ei_anc_center;
}

void frameGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)
{

}
