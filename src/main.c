#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void usage()
{
	printf("./program [fichier]\n");
}

int main(int argc, char* argv[])
{
	int i;
	Machine machine;

	if(argc != 2)
	{
		usage();
		return -1;
	}

	initialiserMachine(&machine);	
	chargerTableau(&machine.tableaux[0], argv[1]);

	while(simulerCycle(&machine) == E_OK);
			
	for(i = 0; i < machine.nb_tableaux; i++)
		detruireTableau(&machine.tableaux[i]);

	return 0;
}
