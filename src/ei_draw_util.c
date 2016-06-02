
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

/*Libere un  point*/
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



/*ajoute un point a une liste chainee*/
ei_linked_point_t* addLinkedPoint(ei_linked_point_t* l, ei_point_t p)
{
    ei_linked_point_t* tmp = calloc(1, sizeof(ei_linked_point_t));

    tmp->point = p;
    if(l != NULL)
        l->next = tmp;

    return tmp;
}


/*affiche l->point*/
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


/*renvoie le dernier point d'une liste chainee*/
ei_linked_point_t* lastPoint(ei_linked_point_t* l)
{
  
  ei_linked_point_t* tmp = l;
  while(tmp->next != NULL)
    {
      tmp = tmp->next;
    }
  return tmp;
}

/*retourne le min entre deux entiers*/
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

/*chaine les sommets d'un rect pour former soit la partie haute, soit la partie basse, soit les deux, d'un frame*/
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
  ei_linked_point_t* fin = malloc(sizeof(struct ei_linked_point_t));
  
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
      s4->next = fin;
      fin->point = s1->point;
      fin->next = NULL;

      return(s1);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_TRUE)
    {
      s3->next = s4;
      s4->next = pointInterieur2;
      pointInterieur2->next = pointInterieur1;
      pointInterieur1->next = s2;
      s2->next = fin;
      fin->point = s3->point;
      fin->next = NULL;

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
      s4->next = fin;
      fin->point = s1->point;
      fin->next = NULL;

      return(s1);
    }
}

/*renvoie non(b)*/
ei_bool_t inverseBool(ei_bool_t b)
{
    if(b == EI_FALSE)
	return EI_TRUE;
    else
	return EI_FALSE;
}




/*affiche le texte d'un bouton en prenant en compte l'ancrage*/
void drawTextWidget(ei_surface_t surface, struct ei_widget_t* widget, struct ei_widget_frame_t* wf, ei_rect_t* clipper)
{
    ei_point_t where;
    int* text_width = malloc(sizeof(int));
    int* text_height = malloc(sizeof(int));
    hw_text_compute_size(wf->text,wf->text_font,text_width,text_height); //stocke la largeur et la hauteur du texte dans width_text et height_text
    
    if(wf->text_anchor == ei_anc_none)
    
      {
    where.x = widget->screen_location.top_left.x;
    where.y = widget->screen_location.top_left.y;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }
    
    if(wf->text_anchor == ei_anc_center)
    
      {
	
    where.x = widget->screen_location.top_left.x+ widget->screen_location.size.width/2 - *text_width/2;
    where.y = widget->screen_location.top_left.y+widget->screen_location.size.height/2 - *text_height/2;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }
   

 if(wf->text_anchor == ei_anc_north)
    
      {	
	where.x = widget->screen_location.top_left.x + widget->screen_location.size.width/2 - *text_width/2;
	where.y = widget->screen_location.top_left.y+wf->border_width;
	ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }
    
    if(wf->text_anchor == ei_anc_northeast)
    
      {
	
    where.x = widget->screen_location.top_left.x+ widget->screen_location.size.width - *text_width-wf->border_width;
    where.y = widget->screen_location.top_left.y-wf->border_width;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }

 if(wf->text_anchor == ei_anc_east)
    
      {
	
    where.x = widget->screen_location.top_left.x + widget->screen_location.size.width - *text_width-wf->border_width;
    where.y = widget->screen_location.top_left.y +widget->screen_location.size.height/2 - *text_height/2;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }
    
    if(wf->text_anchor == ei_anc_southeast)
    
      {
	
    where.x = widget->screen_location.top_left.x + widget->screen_location.size.width - *text_width-wf->border_width;
    where.y = widget->screen_location.top_left.y+widget->screen_location.size.height - *text_height - wf->border_width;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }

 if(wf->text_anchor == ei_anc_south)
    
      {
	
    where.x = widget->screen_location.top_left.x + widget->screen_location.size.width/2 - *text_width/2;
    where.y = widget->screen_location.top_left.y + widget->screen_location.size.height - *text_height - wf->border_width;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }
    
    if(wf->text_anchor == ei_anc_southwest)
    
      {
	
    where.x = widget->screen_location.top_left.x + wf->border_width;
    where.y = widget->screen_location.top_left.y+ widget->screen_location.size.height - *text_height - wf->border_width;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }


  if(wf->text_anchor == ei_anc_west)
    
      {
	
    where.x = widget->screen_location.top_left.x + wf->border_width;
    where.y = widget->screen_location.top_left.y+widget->screen_location.size.height/2 - *text_height/2;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }



  if(wf->text_anchor == ei_anc_northwest)
    
      {
	
    where.x = widget->screen_location.top_left.x+wf->border_width;
    where.y = widget->screen_location.top_left.y+wf->border_width;
    ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);
      }



}




/*affiche une image dans un widget en tenant compte de l'ancrage*/
void drawImgWidget(ei_surface_t surface, struct ei_widget_t* widget, struct ei_widget_frame_t* wf)
{
     ei_point_t where;
  
    if(wf->img_anchor == ei_anc_none)
    
      {
	where.x = widget->screen_location.top_left.x;
	where.y = widget->screen_location.top_left.y;
      }
    
    if(wf->img_anchor == ei_anc_center)
    
      {	
	where.x = widget->screen_location.top_left.x+ widget->screen_location.size.width/2 - wf->img_rect->size.width/2;
	where.y = widget->screen_location.top_left.y+widget->screen_location.size.height/2 -wf->img_rect->size.height/2;
      }
   

    if(wf->img_anchor == ei_anc_north)
    
      {	
	where.x = widget->screen_location.top_left.x + widget->screen_location.size.width/2 -wf->img_rect->size.width/2;
	where.y = widget->screen_location.top_left.y+wf->border_width;
      }
    
    if(wf->img_anchor == ei_anc_northeast)
    
      {	
	where.x = widget->screen_location.top_left.x+ widget->screen_location.size.width -wf->img_rect->size.width-wf->border_width;
	where.y = widget->screen_location.top_left.y-wf->border_width;
      }
    
    if(wf->img_anchor == ei_anc_east)
    
      {	
	where.x = widget->screen_location.top_left.x + widget->screen_location.size.width -wf->img_rect->size.width -wf->border_width;
	where.y = widget->screen_location.top_left.y +widget->screen_location.size.height/2 -wf->img_rect->size.height/2;
      }
    
    if(wf->img_anchor == ei_anc_southeast)
    
      {	
	where.x = widget->screen_location.top_left.x + widget->screen_location.size.width - wf->img_rect->size.width-wf->border_width;
	where.y = widget->screen_location.top_left.y+widget->screen_location.size.height -wf->img_rect->size.height - wf->border_width;
      }

 if(wf->img_anchor == ei_anc_south)
    
      {	
	where.x = widget->screen_location.top_left.x + widget->screen_location.size.width/2 - wf->img_rect->size.width/2;
	where.y = widget->screen_location.top_left.y + widget->screen_location.size.height - wf->img_rect->size.height - wf->border_width;
      }
    
    if(wf->img_anchor == ei_anc_southwest)
    
      {	
	where.x = widget->screen_location.top_left.x + wf->border_width;
	where.y = widget->screen_location.top_left.y+ widget->screen_location.size.height -wf->img_rect->size.height - wf->border_width;
      }


  if(wf->img_anchor == ei_anc_west)
    
      {	
	where.x = widget->screen_location.top_left.x + wf->border_width;
	where.y = widget->screen_location.top_left.y+widget->screen_location.size.height/2 - wf->img_rect->size.height/2;
      }



  if(wf->img_anchor == ei_anc_northwest)
    
      {
	where.x = widget->screen_location.top_left.x+wf->border_width;
	where.y = widget->screen_location.top_left.y+wf->border_width;
      }
  wf->img_rect->top_left = where;
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

/*chaine les sommets d'un rect pour former soit la partie haute, soit la partie basse, soit les deux, d'un rounded frame ( c a d d'un bouton)*/
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
  ei_linked_point_t* fin = malloc(sizeof(struct ei_linked_point_t));
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
      finArc4bis->next = fin;
      fin->point = debutArc1->point;
      fin->next = NULL;

      return(debutArc1);
    }

  if(partieHaute == EI_FALSE && partieBasse == EI_TRUE)
    {
      finArc3->next = debutArc4;
      finArc4->next = pointInterieur2;
      pointInterieur2->next = pointInterieur1;
      pointInterieur1->next = debutArc2bis;
      finArc2bis->next = fin;
      fin->point = debutArc3->point;
      fin->next = NULL;
      
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
      finArc4bis->next = fin;
      fin->point = debutArc1->point;
      fin->next = NULL;
     
      return(debutArc1);
    }
   
}




/*dessine le frame ou le bouton a partir de la liste chainee generee par rounded frame ou rectangular frame*/
void draw_frameButton(struct ei_widget_t* widget, ei_surface_t surface, ei_rect_t* clipper, ei_bool_t enfoncer, ei_bool_t isFrame)
{
  ei_widget_frame_t* frame = (ei_widget_frame_t*) widget;
  
  ei_rect_t rect = frame->w.screen_location;
  int bordurewidth = frame->border_width;
  
  ei_rect_t rectint;
  rectint.top_left.x = rect.top_left.x + bordurewidth;
  rectint.top_left.y = rect.top_left.y + bordurewidth;
  rectint.size.width = rect.size.width - 2*bordurewidth;
  rectint.size.height = rect.size.height - 2*bordurewidth;
  
  ei_linked_point_t* partieAvecBordure;
  ei_linked_point_t* partieFonce;
  ei_linked_point_t* partieClaire;
  ei_linked_point_t* partieSansBordure;
  
  if(isFrame)
  {
      partieAvecBordure = rectangular_frame(rect,EI_TRUE,EI_TRUE);
      partieFonce = rectangular_frame(rect,enfoncer,inverseBool(enfoncer));
      partieClaire = rectangular_frame(rect,inverseBool(enfoncer),enfoncer);
      partieSansBordure = rectangular_frame(rectint,EI_TRUE,EI_TRUE);
  }
  else
  {
      partieAvecBordure = rounded_frame(rect, 20,EI_TRUE,EI_TRUE);
      partieFonce = rounded_frame(rect, 20,enfoncer,inverseBool(enfoncer));
      partieClaire = rounded_frame(rect, 20,inverseBool(enfoncer),enfoncer);
      partieSansBordure = rounded_frame(rectint, 20,EI_TRUE,EI_TRUE);
  }
  
  // couleurs pour les bordures
  ei_color_t fonce; 
  ei_color_t clair;
  ei_color_t color = frame->color; 
  
  fonce.red = 30;
  fonce.green = 30;
  fonce.blue = 30;
  if(frame->relief == ei_relief_none)
     fonce.alpha = 0;
  else
     fonce.alpha = 127;
  
  clair.red = 225;
  clair.green = 225;
  clair.blue = 225;
  if(frame->relief == ei_relief_none)
     clair.alpha = 0;
  else
     clair.alpha = 127;
  
  if(bordurewidth > 0)
  {
      // Premier dessin
      ei_draw_polygon(surface,partieAvecBordure, color,clipper);
      
      // Partie fonce de la bordure
      ei_draw_polygon(surface, partieFonce,fonce,clipper);
      
      // Partie claire de la bordure
      ei_draw_polygon(surface, partieClaire, clair,clipper);
  }
      
  // Dessin du bouton
  ei_draw_polygon(surface, partieSansBordure, color,clipper);
  
  // Creation des lignes entres les bords
  fonce.alpha = 255;
  ei_draw_polyline(surface,partieSansBordure, fonce, clipper);
  if(bordurewidth > 0)
      ei_draw_polyline(surface,partieAvecBordure, fonce, clipper);
  
  freeLinkedPoint(partieAvecBordure);
  freeLinkedPoint(partieFonce);
  freeLinkedPoint(partieClaire);
  freeLinkedPoint(partieSansBordure);
}
