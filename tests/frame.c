#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "ei_widget_frame.h"

/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
	ei_size_t	screen_size		= {600, 600};
	ei_color_t	root_bgcol		= {0x52, 0x7f, 0xb4, 0xff};

	ei_widget_frame_t*	frame;
	ei_size_t	frame_size		= {300,200};
	int		frame_x			= 150;
	int		frame_y			= 200;
	ei_color_t	frame_color		= {0x80, 0x90, 0x20, 0xff};
	ei_relief_t	frame_relief		= ei_relief_raised;
	int		frame_border_width	= 6;
	
	ei_surface_t surface_image;
	
	
	ei_app_create(&screen_size, EI_FALSE);	
	ei_frame_configure(ei_app_root_widget(), &screen_size, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	ei_anchor_t anc = ei_anc_north;
	ei_widget_t* w;
	ei_surface_t surface = ei_app_root_surface();

	surface_image= hw_image_load("misc/klimt.jpg",surface);
	ei_rect_t rect_image = hw_surface_get_rect(&surface_image);
	frame = ei_widget_create("frame", ei_app_root_widget());
/* Create the application and change the color of the background. */
	
	/* Create, configure and place the frame on screen. */

	ei_frame_configure(frame, &frame_size, &frame_color, &frame_border_width, &frame_relief, NULL, NULL, NULL, NULL, &surface_image, NULL, &anc);


	ei_place(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL ); 

	
	/* Run the application's main loop. */
	ei_app_run();

	/* We just exited from the main loop. Terminate the application (cleanup). */
	ei_app_free();

	return (EXIT_SUCCESS);
}
