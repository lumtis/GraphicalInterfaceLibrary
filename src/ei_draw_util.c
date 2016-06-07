
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ei_widget_frame.h"
#include "ei_widget_button.h"
#include "ei_widget_toplevel.h"
#include "ei_draw_util.h"
#include "ei_types.h"
#include"ei_widget.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"




/* retourne la distance entre deux points*/
int distPoint(ei_point_t t1, ei_point_t t2)
{
    return (int)sqrt((t1.x-t2.x)*(t1.x-t2.x)+(t1.y-t2.y)*(t1.y-t2.y));
}

int min(int a, int b)
{
    return ((a < b) ? a : b);
}

int max(int a, int b)
{
    return ((a > b) ? a : b);
}


/*Libere une liste de points*/
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


/*parcourt et affiche une liste de points*/
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

/*chaine les sommets d'un rect pour former soit la partie haute, soit la partie basse, soit les deux, d'un frame*/
ei_linked_point_t* rectangular_frame(ei_rect_t rect, ei_bool_t partieHaute, ei_bool_t partieBasse)
{
  
  //declaration de tous les points dont on a besoin pour creer le frame
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


  //h permet de situer les pts interieurs par rapport au frame
  int h = min(rect.size.width,rect.size.height)/2;

  //affectation des valeurs des sommets
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
  
 //affectation des pts Interieurs : pts pour former le relief a l'interieur du bouton 
  pointInterieur1->point.x = rect.top_left.x + h;
  pointInterieur1->point.y = rect.top_left.y + rect.size.height - h;
  
  pointInterieur2->point.x = rect.top_left.x +rect.size.width -  h;
  pointInterieur2->point.y = pointInterieur1->point.y;
  

  ////ci dessous, on chaine les points necessaires pour dessiner la partie qu'on desire afficher, et on retourne le premier point de la liste

  //ici on ne cree que la partie haute du frame
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

  //ici on ne cree que la partie basse du frame
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

  //ici on ne cree aucune partie
  if(partieHaute == EI_FALSE && partieBasse == EI_FALSE)
    {
      return  NULL;
    }
 

  //ici on cree le frame tout entier
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
    
    return EI_FALSE;
}




/*affiche le texte d'un bouton en prenant en compte l'ancrage*/
void drawTextWidget(ei_surface_t surface, struct ei_widget_t* widget, struct ei_widget_frame_t* wf, ei_rect_t* clipper)
{

    //where correspond au point de depart du texte
    ei_point_t where;
    
    //text_width et text_height correspondront respectivement a la largeur et la hauteur du texte, stockees grace a hw_text_compute_size
    int text_width;
    int text_height;
    hw_text_compute_size(wf->text,wf->text_font,&text_width,&text_height); 
    

    //ci dessous on calcule les coordonnee de where, en fonction de l'ancrage
    if(wf->text_anchor == ei_anc_none)
    
      {
    where.x = widget->content_rect->top_left.x;
    where.y = widget->content_rect->top_left.y;
      }
    
    if(wf->text_anchor == ei_anc_center)
    
      {	
    where.x = widget->content_rect->top_left.x + widget->content_rect->size.width/2 - text_width/2;
    where.y = widget->content_rect->top_left.y + widget->content_rect->size.height/2 - text_height/2;
      }
   

 if(wf->text_anchor == ei_anc_north)
    
      {	
	where.x = widget->content_rect->top_left.x + widget->content_rect->size.width/2 - text_width/2;
	where.y = widget->content_rect->top_left.y;
      }
    
    if(wf->text_anchor == ei_anc_northeast)
    
      {
	
    where.x = widget->content_rect->top_left.x + widget->content_rect->size.width - text_width;
    where.y = widget->content_rect->top_left.y;
      }

 if(wf->text_anchor == ei_anc_east)
    
      {
	
    where.x = widget->content_rect->top_left.x + widget->content_rect->size.width - text_width;
    where.y = widget->content_rect->top_left.y + widget->content_rect->size.height/2 - text_height/2;
      }
    
    if(wf->text_anchor == ei_anc_southeast)
    
      {	
    where.x = widget->content_rect->top_left.x + widget->content_rect->size.width - text_width;
    where.y = widget->content_rect->top_left.y + widget->content_rect->size.height - text_height;
      }

 if(wf->text_anchor == ei_anc_south)
    
      {
    where.x = widget->content_rect->top_left.x + widget->content_rect->size.width/2 - text_width/2;
    where.y = widget->content_rect->top_left.y + widget->content_rect->size.height - text_height;
      }
    
    if(wf->text_anchor == ei_anc_southwest)
    
      {	
    where.x = widget->content_rect->top_left.x;
    where.y = widget->content_rect->top_left.y + widget->content_rect->size.height - text_height;
      }


  if(wf->text_anchor == ei_anc_west)
    
      {	
    where.x = widget->content_rect->top_left.x;
    where.y = widget->content_rect->top_left.y + widget->content_rect->size.height/2 - text_height/2;
      }



  if(wf->text_anchor == ei_anc_northwest)
    
      {	
    where.x = widget->content_rect->top_left.x;
    where.y = widget->content_rect->top_left.y;
      }
  
  //ici on dessine le texte selon l'ancrage
  ei_draw_text(surface, &where, wf->text, wf->text_font, &wf->text_color, clipper);

}


ei_rect_t intersection(ei_rect_t r1, ei_rect_t r2)
{
    ei_rect_t ret;
    
    ret.top_left.x = r1.top_left.x;
    ret.top_left.y = r1.top_left.y;
    ret.size.width = min(r1.size.width,r2.size.width);
    ret.size.height = min(r1.size.height,r2.size.height);
    
    return ret;
}


/*affiche une image dans un widget en tenant compte de l'ancrage; cette fonction fonctionne de la meme facon que drawTextWidget*/
void drawImgWidget(ei_surface_t surface, struct ei_widget_t* widget)
{
     
  ei_widget_frame_t* wf = (ei_widget_frame_t*)widget;
  int copie;

  //coordonnees du topleft de l'image
  ei_rect_t img_rect;
  ei_rect_t dst_rect;

  
  if(wf->img_rect == NULL)
  {
      img_rect = intersection(hw_surface_get_rect(wf->img), *(widget->content_rect));
      dst_rect = intersection(*(widget->content_rect), hw_surface_get_rect(wf->img));
  }
  else
  {
      img_rect = intersection(*(wf->img_rect), *(widget->content_rect));
      dst_rect = intersection(*(widget->content_rect), *(wf->img_rect));
  }
  
  
  if(wf->img_anchor == ei_anc_center)
    
    {	
      dst_rect.top_left.x += widget->content_rect->size.width/2 - dst_rect.size.width/2;
      dst_rect.top_left.y += widget->content_rect->size.height/2 - dst_rect.size.height/2;
    }
   

  if(wf->img_anchor == ei_anc_north)
    
    {	
      dst_rect.top_left.x += widget->content_rect->size.width/2 - dst_rect.size.width/2;
      //dst_rect.top_left.y += ;
    }
    
  if(wf->img_anchor == ei_anc_northeast)
    
    {	
      dst_rect.top_left.x += widget->content_rect->size.width - dst_rect.size.width;
      //dst_rect.top_left.y += ;
    }
    
  if(wf->img_anchor == ei_anc_east)
    
    {	
      dst_rect.top_left.x += widget->content_rect->size.width - dst_rect.size.width;
      dst_rect.top_left.y += widget->content_rect->size.height/2 - dst_rect.size.height/2;
    }
    
  if(wf->img_anchor == ei_anc_southeast)
    
    {	
      dst_rect.top_left.x += widget->content_rect->size.width - dst_rect.size.width;
      dst_rect.top_left.y += widget->content_rect->size.height - dst_rect.size.height;
    }

  if(wf->img_anchor == ei_anc_south)
    
    {	
      dst_rect.top_left.x += widget->content_rect->size.width/2 - dst_rect.size.width/2;
      dst_rect.top_left.y += widget->content_rect->size.height - dst_rect.size.height;
    }
    
  if(wf->img_anchor == ei_anc_southwest)
    
    {	
      //dst_rect.top_left.x += ;
      dst_rect.top_left.y += widget->content_rect->size.height - dst_rect.size.height;
    }


  if(wf->img_anchor == ei_anc_west)
    
    {	
      //dst_rect.top_left.x += ;
      dst_rect.top_left.y += widget->content_rect->size.height/2 - dst_rect.size.height/2;
    }
  
  //dessin de l'image
  hw_surface_lock(wf->img);
  copie = ei_copy_surface(surface, &dst_rect, wf->img, &img_rect, EI_FALSE);
  hw_surface_unlock(wf->img);
}


/*Arc prend en argument le centre, le rayon, l'angle de depart par rapport a l axe des abscisses, et l angle de fin par rapport a l axe des abscisses. Retourne le premier point de l arc et cree la liste de points de cet arc*/

ei_linked_point_t* arc(ei_point_t centre, int rayon, int angleD, int angleF, int nbPoints)
{

  //initialisation des parametres : angles convertis en radians, creation du premier et dernier point de l'arc
  float angleDebut = angleD*3.1415926/180;
  float angleFin = angleF*3.1415926/180;
  ei_linked_point_t* dernierPoint = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* premierPoint = malloc(sizeof(struct ei_linked_point_t));
  float pasAngle = (angleF-angleD)*3.1415926/(180*nbPoints);
  ei_linked_point_t* newPoint = malloc(sizeof(struct ei_linked_point_t));
  

  //on initialise le premier point de l'arc, et dernier point = premierpoint
  premierPoint->point.x = rayon*cos(angleDebut)+centre.x; 
  premierPoint->point.y = -rayon*sin(angleDebut)+centre.y;
  premierPoint->next = NULL;
  dernierPoint = premierPoint;
  dernierPoint = addLinkedPoint(dernierPoint,premierPoint->point);

  //on cree autant de points que voulus grace a la trigonometrie
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
  //declaration de tous les points dont on a besoin pour creer le rounded frame : le debut, la fin et le centre de chaque arc
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
 
  //calcule le centre de l arc qui formera le coin arrondi
  centre1.x = rect.top_left.x + rayon;
  centre1.y = rect.top_left.y + rayon;
  debutArc1 = arc(centre1,rayon,90,180,1000);
  finArc1 = lastPoint(debutArc1);
  
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
   
   return NULL;
}


//chaine les sommets d'un rect pour former un toplevel : coins arrondis en haut et angles droits en bas
ei_linked_point_t* round_and_rectangular_frame(ei_rect_t rect, int rayon)
{
  
  ei_point_t centre1;
  ei_linked_point_t* debutArc1 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* finArc1 = malloc(sizeof(struct ei_linked_point_t));
  
  
  ei_point_t centre4;
  ei_linked_point_t* debutArc4 = malloc(sizeof(struct ei_linked_point_t));  
  ei_linked_point_t* finArc4 = malloc(sizeof(struct ei_linked_point_t)) ;
  ei_linked_point_t* fin = malloc(sizeof(struct ei_linked_point_t));

  ei_linked_point_t* s2 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* s3 = malloc(sizeof(struct ei_linked_point_t));

  int h = min(rect.size.width,rect.size.height)/2;

  ei_point_t sommet2, sommet3;
  
  sommet2.x = rect.top_left.x;
  sommet2.y = rect.top_left.y + rect.size.height;
  
  sommet3.x = rect.top_left.x + rect.size.width;
  sommet3.y = rect.top_left.y + rect.size.height;

  centre1.x = rect.top_left.x + rayon;
  centre1.y = rect.top_left.y + rayon;
  //calcule le centre de l arc qui former le coin arrondi
  debutArc1 = arc(centre1,rayon,90,180,1000); //retourne le 1er pt de l arc
  finArc1 = lastPoint(debutArc1); // retourne le dernier pt de l arc
  
  centre4.x = rect.top_left.x + rect.size.width - rayon;
  centre4.y = rect.top_left.y + rayon;
  debutArc4 = arc(centre4,rayon,0,90,1000); 
  finArc4 = lastPoint(debutArc4);
 
  s2->point = sommet2;
  s2->next = NULL;
  s3->point = sommet3;
  s3->next = NULL;
  //a ce stade on a cree toutes les listes de pts des arcs
  //ci dessous on chaine chaque arc au suivant
  
  finArc1->next = s2; 
  s2->next = s3;
  s3->next = debutArc4;
  finArc4->next = fin;
  fin->point = debutArc1->point;
  fin->next = NULL;  
  return(debutArc1);
}



/*dessine le frame ou le bouton a partir de la liste chainee generee par rounded frame ou rectangular frame*/
void draw_frameButton(struct ei_widget_t* widget, ei_surface_t surface, ei_rect_t* clipper, ei_bool_t enfoncer, ei_bool_t isFrame, ei_surface_t pick_surface)
{
  ei_widget_button_t* button = (ei_widget_button_t*) widget;
  ei_widget_frame_t* frame = (ei_widget_frame_t*) widget;
  
  ei_rect_t rect = frame->w.screen_location;
  int bordurewidth = frame->border_width;
  ei_color_t pickColor;
  
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
      partieAvecBordure = rounded_frame(rect, button->corner_radius, EI_TRUE,EI_TRUE);
      partieFonce = rounded_frame(rect, button->corner_radius, enfoncer,inverseBool(enfoncer));
      partieClaire = rounded_frame(rect, button->corner_radius, inverseBool(enfoncer),enfoncer);
      partieSansBordure = rounded_frame(rectint, button->corner_radius, EI_TRUE,EI_TRUE);
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
  
  // Offsreen
  pickColor = *(widget->pick_color);
  ei_draw_polygon(pick_surface, partieAvecBordure, pickColor, clipper);
  
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



/*dessine un toplevel*/
void draw_toplevel(struct ei_widget_t* widget,ei_surface_t surface, ei_rect_t* clipper, ei_surface_t pick_surface)
{
  ei_widget_toplevel_t* tpl = (ei_widget_toplevel_t*)widget;
  ei_rect_t rect = tpl->w.screen_location;
  int bordurewidth = tpl->border_width;
  int entete = 20;
  ei_rect_t rectint,rectresize;
  ei_point_t centre;
  int rayon = 8;
  ei_point_t where;
  ei_color_t pickColor;

  //tpl = toplevelAllocfunc();
  //toplevelSetdefaultsfunc(&(tpl->w));

  centre.x = rect.top_left.x + 1.5*rayon;
  centre.y = rect.top_left.y +1.5*rayon;

  where.x = rect.top_left.x + 3*rayon;
  where.y =  rect.top_left.y -1 ;

  rectint.top_left.x = rect.top_left.x+1 + bordurewidth;
  rectint.top_left.y = rect.top_left.y+1 + bordurewidth+entete;
  rectint.size.width = rect.size.width-2 - 2*bordurewidth;
  rectint.size.height = rect.size.height-2 - 2*bordurewidth - entete;

  rectresize.size.height = 10;
  rectresize.size.width = 10;
  rectresize.top_left.x = rect.top_left.x + rect.size.width-rectresize.size.width;
  rectresize.top_left.y = rect.top_left.y + rect.size.height-rectresize.size.height;
  
  ei_linked_point_t* cadre_arriere = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* cadre_avant = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* bouton_close = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* bouton_close2 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* bouton_close3 = malloc(sizeof(struct ei_linked_point_t));
  ei_linked_point_t* bouton_resize = malloc(sizeof(struct ei_linked_point_t));
  
  cadre_arriere = round_and_rectangular_frame(rect,15);
  cadre_avant = rectangular_frame(rectint,EI_TRUE,EI_TRUE);
  

  // couleurs
  ei_color_t fonce; 
  ei_color_t clair = tpl->color;
  ei_color_t color,color2,color3;
  ei_color_t white; 
  ei_color_t black;
  
  fonce.red = 0;
  fonce.green = 0;
  fonce.blue = 0;
  fonce.alpha = 127;
  
  clair.red = 215;
  clair.green = 215;
  clair.blue = 215;
  clair.alpha = 255;
  
  color.red = 140;
  color.green = 240;
  color.blue = 198;
  color.alpha = 255;

  color2.red = 110;
  color2.green = 210;
  color2.blue = 158;
  color2.alpha = 255;

  color3.red = 170;
  color3.green = 255;
  color3.blue = 230;
  color3.alpha = 255;

 
  white.red = 255;
  white.green = 255;
  white.blue = 255;
  white.alpha = 255;
  
  black.red = 0;
  black.green = 0;
  black.blue = 0;
  black.alpha = 255;

  bouton_close = arc(centre,rayon-4,0,360,1000); 
  bouton_close2 = arc(centre,rayon,45,225,1000);
  bouton_close3 = arc(centre,rayon,-135,45,1000);
  bouton_resize = rectangular_frame(rectresize,EI_TRUE,EI_TRUE);
  
  ei_draw_polygon(surface,cadre_arriere,tpl->color,clipper);
  ei_draw_polygon(surface,cadre_arriere,fonce,clipper);  
  ei_draw_polyline(surface,cadre_arriere,black,clipper);  
  
  ei_draw_polygon(surface,cadre_avant,tpl->color,clipper);
  ei_draw_polyline(surface,cadre_avant,black,clipper);

  if(tpl->closable)

    {
      ei_draw_polygon(surface,bouton_close2,color2,clipper);
      ei_draw_polygon(surface,bouton_close3,color3,clipper); 
      ei_draw_polyline(surface,bouton_close2,black,clipper);
      ei_draw_polyline(surface,bouton_close3,black,clipper);
      ei_draw_polygon(surface,bouton_close,color,clipper);
    
     
    }
 if(tpl->resizable)

    {
  ei_draw_polygon(surface,bouton_resize,fonce,clipper);
  ei_draw_polyline(surface,bouton_resize,black,clipper);
    }
  //hw_text_create_surface(tpl->title,tpl->text_font,white);
  

 if(tpl->title !=NULL)
   {
  ei_draw_text(surface,&where,tpl->title,NULL,&white, clipper);
   }

  // Offsreen
  pickColor = *(widget->pick_color);
  ei_draw_polygon(pick_surface, cadre_arriere, pickColor, clipper);
 
  freeLinkedPoint(cadre_arriere);
  freeLinkedPoint(cadre_avant);
  freeLinkedPoint(bouton_resize);
  freeLinkedPoint(bouton_close);
}
