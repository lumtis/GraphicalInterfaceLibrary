
#ifndef EI_WIDGET_FRAME_H
#define EI_WIDGET_FRAME_H

typedef struct ei_widget_frame_t {
	ei_widgetclass_t*	wclass;
	uint32_t		pick_id;
	ei_color_t*		pick_color;

	/* Widget Hierachy Management */
	struct ei_widget_t*	parent;
	struct ei_widget_t*	children_head;
	struct ei_widget_t*	children_tail;
	struct ei_widget_t*	next_sibling;

	/* Geometry Management */
	struct ei_geometry_param_t* geom_params;
	ei_size_t		requested_size;
	ei_rect_t		screen_location;
	ei_rect_t*		content_rect;
	
	// Specifique a frame
	int*			border_width,
	ei_relief_t*		relief,
	char**			text,
	ei_font_t*		text_font,
	ei_color_t*		text_color,
	ei_anchor_t*		text_anchor,
	ei_surface_t*		img,
	ei_rect_t**		img_rect,
	ei_anchor_t*		img_anchor
} ei_widget_frame_t;


void* frameAllocfunc()
void frameReleasefunc(struct ei_widget_t* widget)
void frameDrawfunc(struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper)			       
void frameSetdefaultsfunc(struct ei_widget_t* widget)
void frameGeomnotifyfunc(struct ei_widget_t* widget, ei_rect_t rect)