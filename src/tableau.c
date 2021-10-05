#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tableau.h"

void initialiserTableau(Tableau* tableau, int nb_elements)
{
	tableau->nb_plateaux = nb_elements;

	tableau->plateaux = calloc(nb_elements, sizeof(Plateau));
	if(!tableau->plateaux)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
}

void detruireTableau(Tableau* tableau)
{
	if(tableau != NULL)
	{
		if(tableau->plateaux != NULL && tableau->nb_plateaux != 0)
			free(tableau->plateaux);
		memset(tableau, 0, sizeof(Tableau));
	}
}

void chargerTableau(Tableau* tableau, char* filename)
{
	int i;
	FILE* file;

	if(!tableau)
		return;

	file = fopen(filename, "r");
	if(!file)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	initialiserTableau(tableau, ftell(file) / sizeof(Plateau));
	rewind(file);

	if(fread(tableau->plateaux, sizeof(Plateau), tableau->nb_plateaux, file) != tableau->nb_plateaux)
	{
		perror("fread");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < tableau->nb_plateaux; i++)
		tableau->plateaux[i] =
			((tableau->plateaux[i] >> 24 & 0xFF)      ) + 
			((tableau->plateaux[i] >> 16 & 0xFF) << 8 ) + 
			((tableau->plateaux[i] >>  8 & 0xFF) << 16) +
			((tableau->plateaux[i]       & 0xFF) << 24);

	fclose(file);
}

void copierTableau(Tableau* dest, Tableau* source)
{
	if(!dest || !source)
		return;

	if(dest->nb_plateaux != source->nb_plateaux)
	{
		detruireTableau(dest);
		initialiserTableau(dest, source->nb_plateaux);
	}
	memcpy(dest->plateaux, source->plateaux, source->nb_plateaux * sizeof(Plateau));
}
