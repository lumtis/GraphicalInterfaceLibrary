/**
* @file Definit toutes  les fonctions de callbacks internes
**/


#ifndef EI_INTERNCALLBACK
#define EI_INTERNCALLBACK

struct ei_widget_t* widget;
struct ei_event_t* event;


// general


/** \brief obtient la position actuelle de la souris
 *
 * @param widget
 * 
 * @param  event
 *
 * @param  user_param
 *
 * @return 
 */

/**
 * \brief   met à jour le dernie point pointé par la souris , et le précédent 
 *
 * @param widget          le widget du callbacks
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callbacks
 * 
 * @return true si tout s'est bien deroulé
 */
ei_bool_t memorizePosition(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



/**
 * \brief     ferme le tout en cas d'appui su échappe 
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */
ei_bool_t quitEchap(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



// Frame
ei_bool_t refreshFrame(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



// Button
/**
 * \brief     change les reliefs du bouton , et prépare les différents cas de relachement
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */

ei_bool_t pushButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


/**
 * \brief     change les reliefs du bouton si le relachement a lieu au sein du bouton même  
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */

ei_bool_t releaseButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


/**
 * \brief     change les reliefs du bouton si on sort ( ou rerentre ) de (dans) la surface du bouton sans avoir relaché auparavant
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */

ei_bool_t isOutButton(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);




// Top level
/**
 * \brief     analyse à quel endroit du top level la souris a clické et bind les callback nécessaire
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */
ei_bool_t pushToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



/**
 * \brief     detruit le top level si on relache le bouton de fermeture en étant encore sur celui-ci
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */

ei_bool_t releaseCloseToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


/**
 * \brief     mettre à jour les rectangles à modifier lors du  mouvement du top-level 
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */


ei_bool_t moveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



/**
 * \brief     imbind les évènements crées
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */
ei_bool_t releaseMoveToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



/**
 * \brief     redimentionne le toplevel et met à jour les rectangle à redessiner
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return true si tout s'est bien deroulé
 */
ei_bool_t moveResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);



/**
 * \brief     Imbind les évènements crées
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return EI_TRUE si tout s'est bien deroulé
 */
ei_bool_t releaseResizeToplevel(struct ei_widget_t* widget, struct ei_event_t* event, void* user_param);


// Utilitaire

/**
 * \brief     vérifie si le point est dans le rectangle
 *
 * @param widget          le widget du callback 
 * @param event           le dernier evènement 
 * @param user_param      paramètre du callback
 * 
 * @return EI_TRUE si  le point est dans rectangle
 */
ei_bool_t isIn(ei_point_t p, ei_rect_t r);


ei_point_t getCurrent();
ei_point_t getLast();

#endif
