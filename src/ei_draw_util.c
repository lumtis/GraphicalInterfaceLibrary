
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ei_widget_frame.h"
#include "ei_widget_button.h"
#include "ei_widget_toplevel.h"
#include "ei_draw_util.h"
#include "math.h"
#include "ei_types.h"
#include"ei_widget.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"

ei_linked_point_t* getCadre(struct ei_widget_t* widget)
{
    ei_linked_point_t* ret = NULL;
    ei_linked_point_t* tmpL;
    ei_point_t tmp;

    // Premier point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y;
    ret = addLinkedPoint(ret, tmp);

    // Deuxieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y;
    tmpL = addLinkedPoint(ret, tmp);

    // Troisieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Quatrieme point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    tmpL = addLinkedPoint(tmpL, tmp);

    return ret;
}


ei_linked_point_t* getBordure(struct ei_widget_t* widget, int bord)
{
    ei_linked_point_t* ret = NULL;
    ei_linked_point_t* tmpL;
    ei_point_t tmp;

    // Premier point
    ret->point.x = widget->screen_location.top_left.x;
    ret->point.y = widget->screen_location.top_left.y;
    ret = addLinkedPoint(ret, tmp);
    
    // Deuxieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y;
    tmpL = addLinkedPoint(ret, tmp);

    // Troisieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Quatrieme point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Cinquieme point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Sixieme point
    tmp.x = widget->screen_location.top_left.x - bord;
    tmp.y = widget->screen_location.top_left.y - bord;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Septieme point
    tmp.x = widget->screen_location.top_left.x - bord;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height + bord;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Huitieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width + bord;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height + bord;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Neuvieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width + bord;
    tmp.y = widget->screen_location.top_left.y - bord;
    tmpL = addLinkedPoint(tmpL, tmp);

    // Dixieme point
    tmp.x = widget->screen_location.top_left.x - bord;
    tmp.y = widget->screen_location.top_left.y - bord;
    tmpL = addLinkedPoint(tmpL, tmp);

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

ei_linked_point_t* addLinkedPoint(ei_linked_point_t* l, ei_point_t p)
{
    ei_linked_point_t* tmp = calloc(1, sizeof(ei_linked_point_t));

    tmp->point = p;
    if(l != NULL)
        l->next = tmp;

    return tmp;
}


void printLinkedPoint(ei_linked_point_t* l)
{
    int i = 0;
  
    while(l != NULL)
    {
	printf("%d: %d %d\n", i, l->point.x, l->point.y);
	l = l->next;
	i++;
    }
}


void drawTextWidget(ei_surface_t surface, struct ei_widget_t* widget, struct ei_widget_frame_t* wf, ei_rect_t* clipper)
{
    ei_point_t where;

    // TODO : Gerer les ancrage

    where.x = widget->screen_location.top_left.x;
    where.y = widget->screen_location.top_left.y;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
}


void drawImgWidget(ei_surface_t surface, struct ei_widget_t* widget, struct ei_widget_frame_t* wf)
{
    // TODO : Gerer les ancrage

    ei_copy_surface(surface, NULL, wf->img, wf->img_rect, EI_FALSE);
}


/*Arc prend en argument le centre, le rayon, l'angle de depart par rapport a l axe des abscisses, et l angle de fin par rapport a l axe des abscisses. Retourne le premier point de l arc et cree la liste de points de cet arc*/

ei_linked_point_t* arc(ei_point_t centre, int rayon, int angleDebut, int angleFin, int nbPoints)
{
  
  ei_linked_point_t* dernierPoint;
  ei_linked_point_t* premierPoint = NULL;
  int pasAngle = (angleFin-angleDebut)/nbPoints;
  ei_point_t newPoint;
  
  premierPoint->point.x = rayon*cos(angleDebut); //on initialise le point du debut
  premierPoint->point.y = rayon*sin(angleDebut);
  premierPoint->next = NULL;
  dernierPoint = premierPoint; //on initialise dernierPoint au premier point

  for(int i=0; i<nbPoints+1;i++)
    {
      newPoint.x=rayon*cos(angleDebut+i*pasAngle); //on cree le point suivant
      newPoint.y=rayon*sin(angleDebut+i*pasAngle);
      dernierPoint=addLinkedPoint(dernierPoint,newPoint); //on chaine ce nouveau point au dernier point
    }
  return premierPoint;
  
  
  return NULL;
}

ei_linked_point_t* rounded_frame(ei_rect_t rect, int rayon, ei_bool_t partieHaute, ei_bool_t partieBasse)
{
  
  ei_point_t centre1;
  ei_linked_point_t* debutArc1;
  ei_linked_point_t* finArc1;
  ei_point_t centre2;  
  ei_linked_point_t* debutArc2;  
  ei_linked_point_t* finArc2;
  ei_linked_point_t* debutArc2bis;  
  ei_linked_point_t* finArc2bis;
  ei_point_t centre3; 
  ei_linked_point_t* debutArc3;  
  ei_linked_point_t* finArc3;
  ei_point_t centre4; 
  ei_linked_point_t* debutArc4;  
  ei_linked_point_t* finArc4;
  ei_linked_point_t* debutArc4bis;  
  ei_linked_point_t* finArc4bis;

  ei_linked_point_t* pointInterieur1 = NULL;
  ei_linked_point_t* pointInterieur2 = NULL;

  int h = min(rect.size.width,rect.size.height)/2;

  //pts Interieurs : pts pour former le relief a l'interieur du bouton 

  pointInterieur1->point.x = rect.top_left.x + h;
  pointInterieur1->point.y = rect.top_left.y + rect.size.width - h;
  
  pointInterieur2->point.x = rect.top_left.x +rect.size.height -  h;
  pointInterieur2->point.y = pointInterieur1->point.y;

  centre1.x = rect.top_left.x + rayon/sqrt(2);
  centre1.y = rect.top_left.y + rayon/sqrt(2); //calcule le centre de l arc qui former le coin arrondi
  debutArc1 = arc(centre1,rayon,90,180,1000); //retourne le 1er pt de l arc
  finArc1 = lastPoint(debutArc1); // retourne le dernier pt de l arc
  
  centre2.x = rect.top_left.x + rayon/sqrt(2);
  centre2.y = rect.top_left.y +rect.size.width - rayon/sqrt(2);
  debutArc2 = arc(centre2,rayon,180,225,1000);
  finArc2 = lastPoint(debutArc2);
  debutArc2bis = arc(centre2,rayon,225,270,1000);
  finArc2bis = lastPoint(debutArc2bis);
  
  centre3.x = rect.top_left.x + rect.size.height - rayon/sqrt(2);
  centre3.y = rect.top_left.y + rect.size.width - rayon/sqrt(2);
  debutArc3 = arc(centre1,rayon,270,360,1000);
  finArc3 = lastPoint(debutArc3);
  
  centre4.x = rect.top_left.x + rect.size.height - rayon/sqrt(2);
  centre4.y = rect.top_left.y + rayon/sqrt(2);
  debutArc4 = arc(centre2,rayon,0,45,1000); 
  finArc4 = lastPoint(debutArc4);
  debutArc4bis = arc(centre2,rayon,45,90,1000);
  finArc4bis = lastPoint(debutArc4bis);

  //a ce stade on a cree toutes les listes de pts des arcs
  //ci dessous on chaine chaque arc au suivant
  
  if (partieHaute == EI_TRUE && partieBasse == EI_FALSE)
  
    {
      finArc1->next = debutArc2; 
      finArc2->next = pointInterieur1;
      pointInterieur1->next = pointInterieur2;
      pointInterieur2->next = debutArc4bis;
      finArc4bis->next = debutArc1;

      return(debutArc1);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_TRUE)
    {
      finArc3->next = debutArc4;
      finArc4->next = pointInterieur2;
      pointInterieur2->next = pointInterieur1;
      pointInterieur1->next = debutArc2bis;
      finArc2bis->next = debutArc3;
      
      return(debutArc3);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_FALSE)
    {
      return  NULL;
    }
 
  if (partieHaute == EI_TRUE && partieBasse == EI_TRUE)
    { 
      finArc1->next = debutArc2;
      finArc2->next = debutArc2bis;
      finArc2bis->next = debutArc3;
      finArc3->next = debutArc4;
      finArc4->next = debutArc4bis;
      finArc4bis->next = debutArc1;
     
      return(debutArc1);
    }
   
  
  return NULL;
}

ei_linked_point_t* lastPoint(ei_linked_point_t* l) //retourne le dernier point d une liste chainee
{
  
  ei_linked_point_t* tmp = l;
  while(tmp->next != NULL)
    {
      tmp = tmp->next;
    }
  return tmp;
  
}

int min(int a, int b)
{
  if(a<b)
    {
      return a;
    }
  else
    {
      return b;
    }
}


void draw_button(ei_rect_t rect, int rayon, ei_bool_t enfonce)
{
  
  ei_size_t s;
  ei_surface_t surface;
  ei_color_t fonce;
  ei_color_t clair;
  
  s.width = 400;
  s.height = 800;

  surface = hw_surface_create(hw_create_window(&s,EI_FALSE),&s,EI_FALSE);
  
  hw_surface_lock(surface);
  
  fonce.red = 50;
  fonce.blue = 50;
  fonce.green = 50;
  fonce.alpha = 0;
   
  clair.red = 150;
  clair.blue = 150;
  clair.green = 150;
  clair.alpha = 0;
  
  if(enfonce)
    {
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_TRUE,EI_FALSE),fonce,NULL);
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_FALSE,EI_TRUE),clair,NULL);
  
    }
  else
    {
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_TRUE,EI_FALSE),fonce,NULL);
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_FALSE,EI_TRUE),clair,NULL);
    }
     
    hw_surface_unlock(surface);
    hw_surface_update_rects(surface, NULL);
}

