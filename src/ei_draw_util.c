
#include "ei_draw_util.h"


ei_linked_point_t* getCadre(ei_widget_t* widget)
{
    ei_linked_point_t* ret = NULL;
    ei_point_t tmp;

    // Premier point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y;
    ret = addLinkedPoint(ret, tmp);

    // Deuxieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y;
    ret = addLinkedPoint(ret, tmp);

    // Troisieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    ret = addLinkedPoint(ret, tmp);

    // Quatrieme point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    ret = addLinkedPoint(ret, tmp);

    return ret;
}


ei_linked_point_t* getBordure(ei_widget_t* widget, int bord)
{
    ei_linked_point_t* ret = NULL;
    ei_point_t tmp;

    // Premier point
    ret->point.x = widget->screen_location.top_left.x;
    ret->point.y = widget->screen_location.top_left.y;

    // Deuxieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y;
    ret = addLinkedPoint(ret, tmp);

    // Troisieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    ret = addLinkedPoint(ret, tmp);

    // Quatrieme point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height;
    ret = addLinkedPoint(ret, tmp);

    // Cinquieme point
    tmp.x = widget->screen_location.top_left.x;
    tmp.y = widget->screen_location.top_left.y;
    ret = addLinkedPoint(ret, tmp);

    // Sixieme point
    tmp.x = widget->screen_location.top_left.x - bord;
    tmp.y = widget->screen_location.top_left.y - bord;
    ret = addLinkedPoint(ret, tmp);

    // Septieme point
    tmp.x = widget->screen_location.top_left.x - bord;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height + bord;
    ret = addLinkedPoint(ret, tmp);

    // Huitieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width + bord;
    tmp.y = widget->screen_location.top_left.y + widget->screen_location.size.height + bord;
    ret = addLinkedPoint(ret, tmp);

    // Neuvieme point
    tmp.x = widget->screen_location.top_left.x + widget->screen_location.size.width + bord;
    tmp.y = widget->screen_location.top_left.y - bord;
    ret = addLinkedPoint(ret, tmp);

    // Dixieme point
    tmp.x = widget->screen_location.top_left.x - bord;
    tmp.y = widget->screen_location.top_left.y - bord;
    ret = addLinkedPoint(ret, tmp);

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



void drawTextWidget(ei_surface_t surface, ei_widget_t* widget, ei_widget_frame_t* wf, ei_rect_t* clipper)
{
    ei_point_t where;

    // TODO : Gerer les ancrage

    where.x = widget->screen_location.top_left.x;
    where.y = widget->screen_location.top_left.y;
    ei_draw_text(surface, &where, wf->text, wf->text_font, wf->text_color, clipper);
}


void drawImgWidget(ei_surface_t surface, ei_widget_t* widget, ei_widget_frame_t* wf)
{
    // TODO : Gerer les ancrage

    ei_copy_surface(surface, NULL, wf->img, wf->img_rect, EI_FALSE);
}


void arc(ei_point_t centre, int rayon, int angleDebut, int angleFin)
{
    
}
