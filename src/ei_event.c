/**
 *  @file	ei_event.c
 *  @brief	Allows the binding and unbinding of callbacks to events.
 *
 *  \author
 *
 */

#include "ei_event.h"
#include "debug.h"

#include <stdlib.h>
typedef struct traitant {
  ei_widget_t*      widget ;
  ei_tag_t          tag;
  ei_callback_t     callback;
  void * user_param;
  struct traitant*         next;
}traitant ;

traitant* tab_event[ei_ev_last] = {NULL};


void		ei_bind			(ei_eventtype_t		eventtype,
					 ei_widget_t*		widget,
					 ei_tag_t		tag,
					 ei_callback_t		callback,
					 void*			user_param)
{
  traitant * tmp = calloc(1,sizeof(struct traitant));
  traitant *tmp1 ;
  tmp->widget= widget;
  tmp->tag = tag;
  tmp->callback = callback;
  tmp->user_param= user_param;
  
  
  if (tab_event[eventtype]== NULL)
    tab_event[eventtype]= tmp;
  else
  {
    
    for (tmp1=tab_event[eventtype]; tmp1->next != NULL ; tmp1=tmp1->next);
    tmp1->next=tmp;
  }
  
 
}

void		ei_unbind		(ei_eventtype_t		eventtype,
					 ei_widget_t*		widget,
					 ei_tag_t		tag,
					 ei_callback_t		callback,
					 void*			user_param)
{
  
  traitant *tmp = tab_event[eventtype] ;
  traitant *tmp1 = tab_event[eventtype];
  if ( widget == NULL) 
  {
    while ( tmp != NULL && ( tmp->tag !=tag || tmp->callback != callback || tmp-> user_param != user_param))
      tmp=tmp->next;
    if ( tmp != NULL )
    {
      if ( tmp== tmp1 )
      {
	tab_event[eventtype]=tmp1->next;
	free(tmp1);
      }
      else 
      {
	while ( tmp1->next != tmp )
	  tmp1 = tmp1->next;
	tmp1->next=tmp->next ;
	free(tmp);
      }
    }
  }
  else 
  {
    
        while ( tmp != NULL && ( tmp->widget !=widget || tmp->callback != callback || tmp-> user_param != user_param))
      tmp=tmp->next;
    if ( tmp != NULL )
    {
      if ( tmp== tmp1 )
      {
	tab_event[eventtype]=tmp1->next;
	free(tmp1);
      }
      else 
      {
	while ( tmp1->next != tmp )
	  tmp1 = tmp1->next;
	tmp1->next=tmp->next ;
	free(tmp);
      }
    } 
  }
}
