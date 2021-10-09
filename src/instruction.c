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
	ASSERT_INDEX_TABLEAU_INVALIDE(machine, *registre_b);
	ASSERT_TABLEAU_INACTIF(machine, *registre_b);
	ASSERT_INDEX_PLATEAU_INVALIDE(machine, *registre_b, *registre_c);

	*registre_a = machine->tableaux[*registre_b].plateaux[*registre_c];
	return E_OK;
}

INSTRUCTION(2)
{
	ASSERT_INDEX_TABLEAU_INVALIDE(machine, *registre_a);
	ASSERT_TABLEAU_INACTIF(machine, *registre_a);
	ASSERT_INDEX_PLATEAU_INVALIDE(machine, *registre_a, *registre_b);

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
	int index_tableau = machine->nb_tableaux;

	ajouterTableau(machine, index_tableau);
	initialiserTableau(&machine->tableaux[index_tableau], *registre_c);
	*registre_b = index_tableau;
	
	return E_OK;
}

INSTRUCTION(9)
{
	ASSERT_INDEX_TABLEAU_INVALIDE(machine, *registre_c);
	ASSERT_TABLEAU_INACTIF(machine, *registre_c);

	detruireTableau(&machine->tableaux[*registre_c]);
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
	/*
	 *  Pas la peine de copier les tableaux si le 
	 *  tableau de départ et d'arrivé sont les mêmes
	 */
	if(*registre_b != 0)
	{
		ASSERT_INDEX_TABLEAU_INVALIDE(machine, *registre_b);
		ASSERT_TABLEAU_INACTIF(machine, *registre_b);

		copierTableau(&machine->tableaux[0], &machine->tableaux[*registre_b]);
	}
	
	machine->index_programme = *registre_c;
	
	return E_OK;
}

SPECIAL_INSTRUCTION(13)
{
	*registre = value;

	return E_OK;
}

