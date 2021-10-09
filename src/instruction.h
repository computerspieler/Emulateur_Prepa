#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stddef.h>

#include "machine.h"

#define ASSERT_INDEX_TABLEAU_INVALIDE(machine, index_tableau)	\
	if(index_tableau >= machine->nb_tableaux)		\
		return E_OUT_OF_BOUNDS;

#define ASSERT_TABLEAU_INACTIF(machine, index_tableau)		\
	if(machine->tableaux[index_tableau].plateaux == NULL)	\
		return E_ACCES_TABLEAU_INACTIF;

#define ASSERT_INDEX_PLATEAU_INVALIDE(machine, index_tableau, index_plateau)	\
	if(index_plateau >= machine->tableaux[index_tableau].nb_plateaux)	\
		return E_OUT_OF_BOUNDS;

#define INSTRUCTION(instr_value)		\
	EtatMachine instruction##instr_value(	\
			Machine* machine,	\
			Registre* registre_a,	\
			Registre* registre_b,	\
			Registre* registre_c)

#define SPECIAL_INSTRUCTION(instr_value) 	\
	EtatMachine instruction##instr_value(	\
			Machine* machine,	\
			Registre* registre,	\
			u_int32_t value)

INSTRUCTION(0);
INSTRUCTION(1);
INSTRUCTION(2);
INSTRUCTION(3);
INSTRUCTION(4);
INSTRUCTION(5);
INSTRUCTION(6);
INSTRUCTION(7);
INSTRUCTION(8);
INSTRUCTION(9);
INSTRUCTION(10);
INSTRUCTION(11);
INSTRUCTION(12);
SPECIAL_INSTRUCTION(13);

#endif
