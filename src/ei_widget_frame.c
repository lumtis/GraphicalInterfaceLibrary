
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
   ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;
   ei_linked_point_t* cadre = getCadre(widget);
   ei_linked_point_t* bocadre_bgrdure;
   
   // Couleurs  de relief avec alpha au milieu
   ei_color_t white = {0xF0, 0xF0, 0xF0, 0x70};
   ei_color_t black  = {0x10, 0x10, 0x10, 0x70};
   //ei_color_t grey  = {0x70, 0x70, 0x70, 0xFF};
   ei_color_t pickColor;
   
   
   // On dessine un relief si le bord est supérieur à 0
   if (wf->border_width > 0) 
   {
      bordure = getBordure(widget, widget->border_width);

      // Différents cas de bordure
      switch (wf->relief) 
      {
	case (ei_relief_none): // Pas de bordure
	  break;
	case (ei_relief_raised): // Bordure plus claire
	  ei_draw_polygon(surface, bordure, white, clipper);
	  ei_draw_polygon(surface, bordure, wf->color, clipper);
	  //ei_draw_polyline(surface, cadre_bg, grey, clipper);
	  break;
	case (ei_relief_sunken): // Bordure plus foncée
	  ei_draw_polygon(surface, bordure, black, clipper);
	  ei_draw_polygon(surface, bordure, wf->color, clipper);
	  //ei_draw_polyline(surface, cadre_bg, grey, clipper);
	  break;
      }

      // Libération liste
      freeLinkedPoint(bordure);

    }

    // Dessin du cadre
    ei_draw_polygon(surface, cadre, wf->color, clipper);
    ei_draw_polyline(surface, cadre, gris, clipper);
    // Offsreen
    pickColor = *(widget->pick_color);
    ei_draw_polygon(pick_surface, cadre, pickColor, clipper);
    
    freeLinkedPoint(cadre);

    // Texte
    if (wf->text != NULL) 
      ei_draw_widget_text(surface, widget, wf->text, wf->text_font, wf->text_color, wf->text_anchor);

    // Image
    if (wf->img != NULL) 
      ei_draw_widget_img(surface, widget, wf->img, wf->img_rect, wf->img_anchor, 0);
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



/**
*	Fonctions utilitaires
**/

ei_linked_point_t* getCadre(ei_widget_t* widget)
{
  ei_linked_point_t* ret = NULL;
  ei_linked_point_t* tmp1 = ret;
  ei_linked_point_t* tmp2 = ret;
  
  // Premier point
  ret = calloc(sizeof(ei_linked_point_t));
  ret->point.x = widget->screen_location.top_left.x;
  ret->point.y = widget->screen_location.top_left.y;
  
  // Deuxieme point
  tmp1 = calloc(sizeof(ei_linked_point_t));
  tmp1->point.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
  tmp1->point.y = widget->screen_location.top_left.y;
  ret->next = tmp1;
  
  // Troisieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
  tmp2->point.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
  tmp1->next = tmp2;
  tmp1 = tmp2;
  
  // Quatrieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x;
  tmp2->point.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
  
  return ret;
}


ei_linked_point_t* getBordure(ei_widget_t* widget, int bord)
{
  ei_linked_point_t* ret = NULL;
  ei_linked_point_t* tmp1 = ret;
  ei_linked_point_t* tmp2 = ret;
  
  // Premier point
  ret = calloc(sizeof(ei_linked_point_t));
  ret->point.x = widget->screen_location.top_left.x;
  ret->point.y = widget->screen_location.top_left.y;
  
  // Deuxieme point
  tmp1 = calloc(sizeof(ei_linked_point_t));
  tmp1->point.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
  tmp1->point.y = widget->screen_location.top_left.y;
  ret->next = tmp1;
  
  // Troisieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
  tmp2->point.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
  tmp1->next = tmp2;
  tmp1 = tmp2;
  
  // Quatrieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x;
  tmp2->point.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
  tmp1->next = tmp2;
  
  // Cinquieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x;
  tmp2->point.y = widget->screen_location.top_left.y;
  tmp1->next = tmp2;
  
  // Sixieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x - bord;
  tmp2->point.y = widget->screen_location.top_left.y - bord;
  tmp1->next = tmp2;
  
  // Septieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x - bord;
  tmp2->point.y = widget->screen_location.top_left.y + widget->screen_location.size.height + bord;
  tmp1->next = tmp2;
  
  // Huitieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x + widget->screen_location.size.width + bord;
  tmp2->point.y = widget->screen_location.top_left.y + widget->screen_location.size.height + bord;
  tmp1->next = tmp2;
  
  // Neuvieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x + widget->screen_location.size.width + bord;
  tmp2->point.y = widget->screen_location.top_left.y - bord;
  tmp1->next = tmp2;
  
  // Dixieme point
  tmp2 = calloc(sizeof(ei_linked_point_t));
  tmp2->point.x = widget->screen_location.top_left.x - bord;
  tmp2->point.y = widget->screen_location.top_left.y - bord;
  
  return ret;
}


void freeLinkedPoint(ei_linked_point_t* l)
{
  ei_linked_point_t* tmp1 = l;
  ei_linked_point_t* tmp2;
  
  if(tmp1 == NULL)
     return;
  
  tmp2 = tmp1->next;
  
  while(tmp2 != NULL)
  {
    free(tmp1);
    tmp1 = tmp2;
    tmp2 = tmp1->next;
  }
}
