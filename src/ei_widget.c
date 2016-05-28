/**
 * @file	ei_widget.c
 *
 * @brief 	API for widgets management: creation, configuration, hierarchy, redisplay.
 *
 */

#include "ei_widget.h"
#include "debug.h"



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
      new_widget->wclass = classe_new_widget;

      new_widget->parent =parent;
      new_widget->children_head= NULL;
      new_widget->children_tail = NULL ;
      new_widget->next_sibling = NULL ;
    	// précondition : le parent lui même n'est jamais NULL
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
  // TODO : initialisation de pick_ id , pick_color , et parametre géometrique
}


void ei_widget_destroy(ei_widget_t* widget)
{
  	if (widget == NULL )
    		return ;
  	else
		{
		    if (widget->parent== NULL)
		    {
		      	if (widget->children_head == NULL)
								widget->wclass->releasefunc();
		      	else
			  				releaserec(children_head);
		    }
		    else
		    {

				}
		}
		//TODO le reste de la fonction : faciiiiiiiile
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

}
