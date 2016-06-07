/**
 *  @file	widgetclass.c
 *  @brief	Definition and registration of widget classes.
 *
 *  \author
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ei_widgetclass.h"
#include "ei_widget_frame.h"
#include "ei_widget_button.h"
#include "ei_widget_toplevel.h"
#include "debug.h"


/**
 *  @var	wc
 *  @brief	Variable globale contenant un chaiage de tout les widgets class
 */
ei_widgetclass_t* wc = NULL;


void ei_widgetclass_register(ei_widgetclass_t* widgetclass)
{
    ei_widgetclass_t* tmp;

    // s'il n'y a pas de classe on l'a definit comme la premiere
    if(wc == NULL)
      	wc = widgetclass;
    else
    {
    
      	for(tmp = wc; tmp->next != NULL; tmp = tmp->next);
      	tmp->next = widgetclass;
    }
}


ei_widgetclass_t* ei_widgetclass_from_name(ei_widgetclass_name_t name)
{
    ei_widgetclass_t* tmp;

    for(tmp = wc; tmp != NULL; tmp = tmp->next)
    {
      	if(!strcmp(ei_widgetclass_stringname(tmp->name), ei_widgetclass_stringname(name)))
      	    return tmp;
    }

    PRINT_DEBUG("ei_widgetclass_from_name : classe non trouvee");

    return NULL;
}


void ei_frame_register_class()
{
    ei_widgetclass_t* frame = malloc(sizeof(ei_widgetclass_t));

    strcpy(frame->name, "frame");
    frame->allocfunc = frameAllocfunc;
    frame->releasefunc = frameReleasefunc;
    frame->drawfunc = frameDrawfunc;
    frame->setdefaultsfunc = frameSetdefaultsfunc;
    frame->geomnotifyfunc = frameGeomnotifyfunc;
    frame->next = NULL;

    ei_widgetclass_register(frame);
}


void ei_button_register_class()
{
    ei_widgetclass_t* button = malloc(sizeof(ei_widgetclass_t));

    strcpy(button->name, "button");
    button->allocfunc = buttonAllocfunc;
    button->releasefunc = buttonReleasefunc;
    button->drawfunc = buttonDrawfunc;
    button->setdefaultsfunc = buttonSetdefaultsfunc;
    button->geomnotifyfunc = buttonGeomnotifyfunc;
    button->next = NULL;

    ei_widgetclass_register(button);
}


void ei_toplevel_register_class()
{
    ei_widgetclass_t* toplevel = malloc(sizeof(ei_widgetclass_t));

    strcpy(toplevel->name, "toplevel");
    toplevel->allocfunc = toplevelAllocfunc;
    toplevel->releasefunc = toplevelReleasefunc;
    toplevel->drawfunc = toplevelDrawfunc;
    toplevel->setdefaultsfunc = toplevelSetdefaultsfunc;
    toplevel->geomnotifyfunc = toplevelGeomnotifyfunc;
    toplevel->next = NULL;

    ei_widgetclass_register(toplevel);
}
