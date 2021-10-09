#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void usage()
{
	printf("./program [fichier]\n");
}

int main(int argc, char* argv[])
{
	unsigned int i;
	Machine machine;
	EtatMachine etat;

	if(argc != 2)
	{
		usage();
		return EXIT_FAILURE;
	}

	initialiserMachine(&machine);	
	chargerTableau(&machine.tableaux[0], argv[1]);

	while((etat = simulerCycle(&machine)) == E_OK);

	printf("Code de sortie : %i\n", etat);
	
	for(i = 0; i < machine.nb_tableaux; i++)
		detruireTableau(&machine.tableaux[i]);

	return EXIT_SUCCESS;
}
