#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "machine.h"

void initialiserMachine(Machine* machine)
{
	memset(machine, 0, sizeof(Machine));
	ajouterTableau(machine, 0);
}

void ajouterTableau(Machine* machine, int index)
{
	if(index < machine->nb_tableaux)
		return;

	machine->nb_tableaux = index + 1;

	machine->tableaux = reallocarray(machine->tableaux, machine->nb_tableaux, sizeof(Tableau));
	if(!machine->tableaux)
	{
		perror("reallocarray");
		exit(EXIT_FAILURE);
	}
}

EtatMachine simulerCycle(Machine* machine)
{
	u_int8_t entree;
	Plateau instruction;
	int opcode;
	EtatMachine etat_tmp;

	etat_tmp = verifierValiditeAdresse(machine, 0, machine->index_programme);
	if(etat_tmp != E_OK)
		return etat_tmp;

	instruction = machine->tableaux[0].plateaux[machine->index_programme];

	opcode = instruction >> 28 & 0b1111;
	Registre *registre_a = &machine->registres[instruction >> 6  & 0b0111];
 	Registre *registre_b = &machine->registres[instruction >> 3  & 0b0111];
 	Registre *registre_c = &machine->registres[instruction       & 0b0111];

#ifdef DEBUG
	printf("\nCycle n°%i: Instruction: %i, Arguments: ", machine->nb_cycles, opcode);
	if(opcode != 13)
		printf("r%i, r%i, r%i", instruction >> 6 & 0b0111, instruction >> 3 & 0b0111, instruction & 0b0111);
	else
		printf("r%i, %i", instruction >> 25 & 0b0111, instruction & 0xFFFFFF);

	printf("\nRegistres = [");
	for(int i = 0; i < 8; i++)
		printf("%x; ", machine->registres[i]);
	printf("], Index Pointer: %i\n", machine->index_programme);
#endif

	machine->index_programme ++;
	switch(opcode)
	{
	case 0:
		if(*registre_c != 0)
			*registre_a = *registre_b;
		break;

	case 1:
		*registre_a = machine->tableaux[*registre_b].plateaux[*registre_c];
		break;

	case 2:
		machine->tableaux[*registre_a].plateaux[*registre_b] = *registre_c;
		break;

	case 3:
		*registre_a = *registre_b + *registre_c;
		break;

	case 4:
		*registre_a = *registre_b * *registre_c;
		break;

	case 5:
		if(*registre_c != 0)
			*registre_a = *registre_b / *registre_c;
		else
			return E_DIV_PAR_0;
		break;

	case 6:
		*registre_a = (*registre_b & *registre_c) ^ 0xFFFFFFFF;
		break;

	case 7:
		return E_FIN_PROGRAMME;

	case 8:
		ajouterTableau(machine, machine->nb_tableaux);
		initialiserTableau(&machine->tableaux[machine->nb_tableaux - 1], *registre_c);
		*registre_b = machine->nb_tableaux - 1;
		break;

	case 9:
		detruireTableau(lireTableau(machine, *registre_c));
		break;

	case 10:
		if(*registre_c < 256)
			printf("%c", (char) (*registre_c));
		else
			return E_SORTIE_INVALIDE;
		break;
	
	case 11:
		fread(&entree, sizeof(u_int8_t), 1, stdin);
		if(entree != '\0')
			*registre_c = entree;
		else
			*registre_c = -1;	// -1 = 0xFFFFFFFF
		break;
	
	case 12:
		copierTableau(lireTableau(machine, 0), lireTableau(machine, *registre_b));
		machine->index_programme = *registre_c;
		break;
	
	case 13:
		registre_a = &machine->registres[instruction >> 25 & 0b0111];
		*registre_a = (instruction & 0x01FFFFFF);
		break;
	
	default:
		return E_MAUVAISE_INSTRUCTION;
	}

	machine->nb_cycles ++;

	return E_OK;
}

Tableau* lireTableau(Machine* machine, int index)
{
	if(index >= machine->nb_tableaux)
		return NULL;

	if(machine->tableaux[index].plateaux == NULL)
		return NULL;

	return &machine->tableaux[index];
}

EtatMachine verifierValiditeAdresse(Machine* machine, int index_tableau, int index_plateau)
{
	Tableau *tableau;

	if(index_tableau >= machine->nb_tableaux)
		return E_OUT_OF_BOUNDS;

	if(machine->tableaux[index_tableau].plateaux == NULL)
		return E_ACCES_TABLEAU_INACTIF;

	tableau = &machine->tableaux[index_tableau];	
	if(index_plateau >= tableau->nb_plateaux)
		return E_OUT_OF_BOUNDS;

	return E_OK;
}
