#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"

INSTRUCTION(0)
{
	if(*registre_c != 0)
		*registre_a = *registre_b;

	return E_OK;
}

INSTRUCTION(1)
{
	*registre_a = machine->tableaux[*registre_b].plateaux[*registre_c];
	return E_OK;
}

INSTRUCTION(2)
{
	machine->tableaux[*registre_a].plateaux[*registre_b] = *registre_c;
	return E_OK;
}

INSTRUCTION(3)
{
	*registre_a = *registre_b + *registre_c;
	return E_OK;
}

INSTRUCTION(4)
{
	*registre_a = *registre_b * *registre_c;
	return E_OK;
}

INSTRUCTION(5)
{
	if(*registre_c == 0)
		return E_DIV_PAR_0;
	
	*registre_a = *registre_b / *registre_c;
	return E_OK;
}

INSTRUCTION(6)
{
	*registre_a = (*registre_b & *registre_c) ^ 0xFFFFFFFF;
	return E_OK;
}

INSTRUCTION(7)
{
	return E_FIN_PROGRAMME;
}

INSTRUCTION(8)
{
	ajouterTableau(machine, machine->nb_tableaux);
	initialiserTableau(&machine->tableaux[machine->nb_tableaux - 1], *registre_c);
	*registre_b = machine->nb_tableaux - 1;
	
	return E_OK;
}

INSTRUCTION(9)
{
	detruireTableau(lireTableau(machine, *registre_c));
	return E_OK;
}

INSTRUCTION(10)
{
	if(*registre_c >= 256)
		return E_SORTIE_INVALIDE;
	
	printf("%c", (char) (*registre_c));
	return E_OK;
}

INSTRUCTION(11)
{
	u_int8_t entree = 0;

	fread(&entree, sizeof(u_int8_t), 1, stdin);
	if(entree != '\0')
		*registre_c = entree;
	else
		*registre_c = -1;	// -1 = 0xFFFFFFFF
	
	return E_OK;
}

INSTRUCTION(12)
{
	copierTableau(lireTableau(machine, 0), lireTableau(machine, *registre_b));
	machine->index_programme = *registre_c;
	
	return E_OK;
}

SPECIAL_INSTRUCTION(13)
{
	*registre = value;

	return E_OK;
}

