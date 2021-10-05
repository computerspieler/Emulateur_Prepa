#ifndef _TABLEAU_H_
#define _TABLEAU_H_

#include <stddef.h>

typedef u_int32_t Plateau;
typedef struct Tableau Tableau;

struct Tableau
{
	Plateau* plateaux;
	size_t nb_plateaux;
};

void initialiserTableau(Tableau* tableau, int nb_elements);
void detruireTableau(Tableau* tableau);
void chargerTableau(Tableau* tableau, char* filename);
void copierTableau(Tableau* dest, Tableau* source);

#endif
