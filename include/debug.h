/**
** Fichier pour inclure les fonction de debuggage
**/

#ifndef DEBUG_H
#define DEBUG_H

// A definir tant que la version n'est pas finale
#define DEBUG


#ifdef DEBUG_H
#define PRINT_DEBUG(str) printf("%s\n", str)
#else
#define PRINT_DEBUG(str)
#endif


#endif