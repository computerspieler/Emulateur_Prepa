#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stddef.h>

#include "machine.h"

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
