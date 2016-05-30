/**
 * @file	ei_widget.c
 *
 * @brief 	API for widgets management: creation, configuration, hierarchy, redisplay.
 *
 */

#include "ei_widget.h"
#include "debug.h"

/**
 * @name ei_widget_destroy_rec
 */
void ei_widget_destroy_rec(ei_widget_t * widget)
{
  if (widget == NULL )
    return;
  else
  {
    if (widget->children_head != NULL )
      ei_widget_destroy_rec(widget->children_head);
    if (widget->next_sibling != NULL )
      ei_widget_destroy_rec(widget->next_sibling);

    widget->wclass->releasefunc(widget);
    free(widget);
  }
}

ei_widget_t* ei_widget_create(ei_widgetclass_name_t class_name,
			      ei_widget_t* parent)
{
  ei_widget_t* new_widget ;
  ei_widgetclasse_t * classe_new_widget = ei_widgetclass_from_name(class_name);

  if ( classe_new_widget == NULL)
    return NULL;
  else
  {
    new_widget = (ei_widget*)classe_new_widget->allocfunc();
    classe_new_widget->setdefaultsfunc(new_widget);
    new_widget->wclass = classe_new_widget;

    new_widget->parent =parent;
    new_widget->children_head= NULL;
    new_widget->children_tail = NULL ;
    new_widget->next_sibling = NULL ;
    
    // precondition : le parent lui même n'est jamais NULL
    if (parent->children_head = NULL )
    {
      parent->children_head=new_widget;
      parent->children_tail=new_widget;
    }
    else
    {
      parent->children_tail->next_sibling= new_widget ;
      parent->children_tail = new_widget ;
    }
  }
}


void ei_widget_destroy(ei_widget_t* widget)
{
  ei_widget *p;
  if (widget == NULL )
    return;
  else
  {
    if (widget->parent== NULL)
    {
      ei_widget_destroy_rec(widget->children_head);
      widget->wclass->releasefunc(widget);
      free(widget);
    }
    else
    {
      p=widget->parent->children_head;
      if ( p == widget)
      {
	if (p==widget->parent_children_tail)
	{
	  widget->parent->children_head = NULL;
	  widget->parent->children_tail= NULL;
	  ei_widget_destroy_rec(widget->children_head);
	  widget->wclass->releasefunc(widget);
	  free(widget);
	 }
	 else
	 {
	  widget->parent->children_head= p.next_sibling;
	  ei_widget_destroy_rec(widget->children_head);
	  widget->wclass->releasefunc(widget);
	  free(widget);
	 }
	}
	else
	{
	  while ( p.next_sibling != widget )
	    p=p.next_sibling;
	  p.next_sibling=widget.next_sibling;
	  ei_widget_destroy_rec(widget->children_head);
	  widget->wclass->releasefunc(widget);
	  free(widget);
	 }
     }
  }
}


ei_widget_t* ei_widget_pick(ei_point_t*	where)
{

}


void			ei_frame_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor)
{
  ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;

  if(requested_size != NULL)
    widget->requested_size = *requested_size;

  if(color != NULL)
    wf->color = *color;
  if(border_width != NULL)
    wf->border_width = *border_width;
  if(relief != NULL)
    wf->relief = *relief;
  if(text != NULL)
  {
    if(wf->text != NULL)
      free(wf->text);
    wf->text = *text;
  }
  if(text_font != NULL)
    wf->text_font = *text_font;
  if(text_color != NULL)
    wf->text_color = *text_color;
  if(text_anchor != NULL)
    wf->text_anchor = *text_anchor;
  if(img != NULL)
  {
    if(wf->img != NULL)
      free(wf->img);
    wf->img = *img;
  }
  if(img_rect != NULL)
  {
    if(wf->img_rect != NULL)
      free(wf->img_rect);
    wf->img_rect = *img_rect;
  }
  if(img_anchor != NULL)
    wf->img_anchor = *img_anchor;
}


void			ei_button_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 int*			corner_radius,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor,
							 ei_callback_t*		callback,
							 void**			user_param)
{
  ei_widget_button_t* wb = (ei_widget_button_t*)widget;

  if(requested_size != NULL)
    widget->requested_size = *requested_size;

  if(corner_radius != NULL)
    wb->corner_radius = *corner_radius;
  if(callback != NULL)
    wb->callback = *callback;
  if(user_param != NULL)
  {
    if(wb->user_param != NULL)
      free(wb->user_param);
    wb->user_param = *user_param;
  }

  ei_frame_configure(widget, requested_size, color, border_width, relief, text, text_font, text_color, text_anchor, img, img_rect, img_anchor);
}


void			ei_toplevel_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 ei_color_t*		color,
							 int*			border_width,
							 char**			title,
							 ei_bool_t*		closable,
							 ei_axis_set_t*		resizable,
						 	 ei_size_t**		min_size)
{
  ei_widget_toplevel_t* wtl = (ei_widget_toplevel_t*)widget;

  if(requested_size != NULL)
    widget->requested_size = *requested_size;

  if(color != NULL)
    wtl->color = *color;
  if(border_width != NULL)
    wtl->border_width = *border_width;
  if(title != NULL)
  {
    if(wtl->title != NULL)
      free(wtl->title);
    wtl->title = *title;
  }
  if(closable != NULL)
    wtl->closable = *closable;
  if(resizable != NULL)
    wtl->resizable = *resizable;
  if(min_size != NULL)
  {
    if(wtl->title != NULL)
      free(wtl->title);
    wtl->min_size = *min_size;
  }
}
