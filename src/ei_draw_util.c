
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



ei_linked_point_t* rectangular_frame(ei_rect_t rect, ei_bool_t partieHaute, ei_bool_t partieBasse)

{
  
  ei_point_t sommet1 = rect.top_left;
  ei_point_t sommet2;
  ei_point_t sommet3;
  ei_point_t sommet4;
  
  ei_linked_point_t* s1 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* s2 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* s3 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* s4 = malloc(sizeof(struct ei_linked_point_t));
 
  ei_linked_point_t* pointInterieur1 = malloc(sizeof(struct ei_linked_point_t)) ;
  ei_linked_point_t* pointInterieur2 = malloc(sizeof(struct ei_linked_point_t)) ;

  int h = min(rect.size.width,rect.size.height)/2;

  sommet2.x = rect.top_left.x;
  sommet2.y = rect.top_left.y + rect.size.height;
  
  sommet3.x = rect.top_left.x + rect.size.width;
  sommet3.y = rect.top_left.y + rect.size.height;

  sommet4.x = rect.top_left.x + rect.size.width;
  sommet4.y = rect.top_left.y;

  s1->point = sommet1;
  s2->point = sommet2;
  s3->point = sommet3;
  s4->point = sommet4;

  s1->next = NULL;
  s2->next = NULL;
  s3->next = NULL;
  s4->next = NULL;

  printLinkedPoint(s1);printLinkedPoint(s2);printLinkedPoint(s3);printLinkedPoint(s4);
  
 //pts Interieurs : pts pour former le relief a l'interieur du bouton 

  pointInterieur1->point.x = rect.top_left.x + h;
  pointInterieur1->point.y = rect.top_left.y + rect.size.height - h;
  
  pointInterieur2->point.x = rect.top_left.x +rect.size.width -  h;
  pointInterieur2->point.y = pointInterieur1->point.y;
  
  if (partieHaute == EI_TRUE && partieBasse == EI_FALSE)
  
    {
      s1->next =  s2;
      s2->next = pointInterieur1;
      pointInterieur1->next = pointInterieur2;
      pointInterieur2->next = s4;

      return(s1);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_TRUE)
    {
      s3->next = s4;
      s4->next = pointInterieur2;
      pointInterieur2->next = pointInterieur1;
      pointInterieur1->next = s2;
      
      return(s3);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_FALSE)
    {
      return  NULL;
    }
 
  if (partieHaute == EI_TRUE && partieBasse == EI_TRUE)
    {  
      s1->next = s2;
      s2->next = s3;
      s3->next = s4;
      
      return(s1);
    }
   
}


void draw_frame(ei_widget_t* widget, ei_surface_t surface)
{
  ei_widget_frame_t* frame = (ei_widget_frame_t*) widget;
  
  ei_rect_t rect = frame->w.screen_location;
  int bordurewidth = frame->border_width;
  ei_rect_t rectint;
  rectint.top_left.x = rect.top_left.x + bordurewidth;
  rectint.top_left.y = rect.top_left.y + bordurewidth;
  rectint.size.width = rect.size.width - 2*bordurewidth;
  rectint.size.height = rect.size.height - 2*bordurewidth;
  ei_color_t* fonce = malloc(sizeof(struct ei_color_t*)); 
  fonce->red = 140;
  fonce->green = 140;
  fonce->blue = 140;
  fonce->alpha = 255;
  
  ei_color_t* clair = malloc(sizeof(struct ei_color_t*));
  clair->red = 210;
  clair->green = 210;
  clair->blue = 210;
  clair->alpha = 255;

  ei_color_t* color = malloc(sizeof(struct ei_color_t*)); 
  color->red = 170;
  color->green = 170;
  color->blue = 170;
  color->alpha = 255;
  
  ei_draw_polygon(surface,rectangular_frame(rect,EI_TRUE,EI_FALSE),*fonce,NULL);
  ei_draw_polygon(surface,rectangular_frame(rect,EI_FALSE,EI_TRUE),*clair,NULL);
  ei_draw_polygon(surface,rectangular_frame(rectint,EI_TRUE,EI_TRUE),*color,NULL);
 
     
  hw_surface_unlock(surface);
  hw_surface_update_rects(surface, NULL);
}



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

ei_linked_point_t* arc(ei_point_t centre, int rayon, int angleD, int angleF, int nbPoints)
{
  float angleDebut = angleD*3.1415926/180;
  float angleFin = angleF*3.1415926/180;
  ei_linked_point_t* dernierPoint = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* premierPoint = malloc(sizeof(struct ei_linked_point_t));
  float pasAngle = (angleF-angleD)*3.1415926/(180*nbPoints);
  ei_linked_point_t* newPoint = malloc(sizeof(struct ei_linked_point_t));
  
  premierPoint->point.x = rayon*cos(angleDebut)+centre.x; //on initialise le point du debut
  premierPoint->point.y = -rayon*sin(angleDebut)+centre.y;
  premierPoint->next = NULL;
  dernierPoint = premierPoint;
  dernierPoint = addLinkedPoint(dernierPoint,premierPoint->point);
  for(int i=1; i<nbPoints+1;i++)
    {
      newPoint->point.x = rayon*cos(angleDebut+i*pasAngle)+centre.x; //on cree le point suivant
      newPoint->point.y = -rayon*sin(angleDebut+i*pasAngle)+centre.y;
      newPoint->next = NULL;
      dernierPoint = addLinkedPoint(dernierPoint,newPoint->point);//on chaine ce nouveau point au dernier point
      }
  
  return premierPoint;
  
  
  
}

ei_linked_point_t* rounded_frame(ei_rect_t rect, int rayon, ei_bool_t partieHaute, ei_bool_t partieBasse)

{
  
  ei_point_t centre1;
  ei_linked_point_t* debutArc1 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* finArc1 = malloc(sizeof(struct ei_linked_point_t));
  
  ei_point_t centre2;
  ei_linked_point_t* debutArc2 = malloc(sizeof(struct ei_linked_point_t));  
  ei_linked_point_t* finArc2 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* debutArc2bis = malloc(sizeof(struct ei_linked_point_t));  
  ei_linked_point_t* finArc2bis = malloc(sizeof(struct ei_linked_point_t));
  
  ei_point_t centre3;
  ei_linked_point_t* debutArc3 = malloc(sizeof(struct ei_linked_point_t));  
  ei_linked_point_t* finArc3 = malloc(sizeof(struct ei_linked_point_t));
  
  ei_point_t centre4;
  ei_linked_point_t* debutArc4 = malloc(sizeof(struct ei_linked_point_t));  
  ei_linked_point_t* finArc4 = malloc(sizeof(struct ei_linked_point_t)) ;
  ei_linked_point_t* debutArc4bis = malloc(sizeof(struct ei_linked_point_t)) ;  
  ei_linked_point_t* finArc4bis = malloc(sizeof(struct ei_linked_point_t)) ;

  ei_linked_point_t* pointInterieur1 = malloc(sizeof(struct ei_linked_point_t)) ;
  ei_linked_point_t* pointInterieur2 =malloc(sizeof(struct ei_linked_point_t)) ;

  int h = min(rect.size.width,rect.size.height)/2;

  //pts Interieurs : pts pour former le relief a l'interieur du bouton 

  pointInterieur1->point.x = rect.top_left.x + h;
  pointInterieur1->point.y = rect.top_left.y + rect.size.height - h;
  
  pointInterieur2->point.x = rect.top_left.x +rect.size.width -  h;
  pointInterieur2->point.y = pointInterieur1->point.y;

  centre1.x = rect.top_left.x + rayon;
  centre1.y = rect.top_left.y + rayon;
  //calcule le centre de l arc qui former le coin arrondi
  debutArc1 = arc(centre1,rayon,90,180,1000); //retourne le 1er pt de l arc
  finArc1 = lastPoint(debutArc1); // retourne le dernier pt de l arc
  
  centre2.x = rect.top_left.x + rayon;
  centre2.y = rect.top_left.y +rect.size.height - rayon;
  debutArc2 = arc(centre2,rayon,180,225,1000);
  finArc2 = lastPoint(debutArc2);
  debutArc2bis = arc(centre2,rayon,225,270,1000);
  finArc2bis = lastPoint(debutArc2bis);
  
  centre3.x = rect.top_left.x + rect.size.width - rayon;
  centre3.y = rect.top_left.y + rect.size.height - rayon;
  debutArc3 = arc(centre3,rayon,270,360,1000);
  finArc3 = lastPoint(debutArc3);
  
  centre4.x = rect.top_left.x + rect.size.width - rayon-1;
  centre4.y = rect.top_left.y + rayon;
  debutArc4 = arc(centre4,rayon,0,45,1000); 
  finArc4 = lastPoint(debutArc4);
  debutArc4bis = arc(centre4,rayon,45,90,1000);
  finArc4bis = lastPoint(debutArc4bis);

  //a ce stade on a cree toutes les listes de pts des arcs
  //ci dessous on chaine chaque arc au suivant
  
  if (partieHaute == EI_TRUE && partieBasse == EI_FALSE)
  
    {
      finArc1->next = debutArc2; 
      finArc2->next = pointInterieur1;
      pointInterieur1->next = pointInterieur2;
      pointInterieur2->next = debutArc4bis;
      finArc4bis->next = NULL;

      return(debutArc1);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_TRUE)
    {
      finArc3->next = debutArc4;
      finArc4->next = pointInterieur2;
      pointInterieur2->next = pointInterieur1;
      pointInterieur1->next = debutArc2bis;
      finArc2bis->next = NULL;
      
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
      finArc4bis->next = NULL;
     
      return(debutArc1);
    }
   
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


void draw_button(ei_rect_t rect, int rayon, ei_bool_t enfonce,ei_surface_t surface,int bordurewidth)
{
  ei_rect_t rectint;
  rectint.top_left.x = rect.top_left.x+bordurewidth;
  rectint.top_left.y = rect.top_left.y+bordurewidth;
  rectint.size.width = rect.size.width - 2*bordurewidth;
  rectint.size.height = rect.size.height - 2*bordurewidth;
  ei_color_t* fonce = malloc(sizeof(struct ei_color_t*)); 
  fonce->red = 140;
  fonce->green = 140;
  fonce->blue = 140;
  fonce->alpha = 255;
  
  ei_color_t* clair = malloc(sizeof(struct ei_color_t*));
  clair->red = 210;
  clair->green = 210;
  clair->blue = 210;
  clair->alpha = 255;

  ei_color_t* color = malloc(sizeof(struct ei_color_t*)); 
  color->red = 170;
  color->green = 170;
  color->blue = 170;
  color->alpha = 255;
  
  if(enfonce)
    {
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_TRUE,EI_FALSE),*fonce,NULL);
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_FALSE,EI_TRUE),*clair,NULL);
      ei_draw_polygon(surface,rounded_frame(rectint,rayon,EI_TRUE,EI_TRUE),*color,NULL);
    }
  else
    {
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_FALSE,EI_TRUE),*fonce,NULL);
      ei_draw_polygon(surface,rounded_frame(rect,rayon,EI_TRUE,EI_FALSE),*clair,NULL);
      ei_draw_polygon(surface,rounded_frame(rectint,rayon,EI_TRUE,EI_TRUE),*color,NULL);
    }
     
    hw_surface_unlock(surface);
    hw_surface_update_rects(surface, NULL);
}

