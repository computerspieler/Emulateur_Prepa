#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "instruction.h"
#include "machine.h"

void initialiserMachine(Machine* machine)
{
	memset(machine, 0, sizeof(Machine));
	ajouterTableau(machine, 0);
}

void ajouterTableau(Machine* machine, unsigned int index)
{
	if(index < machine->nb_tableaux)
		return;

	machine->nb_tableaux = index + 1;

	if(machine->tableaux == NULL)
		machine->tableaux = malloc(machine->nb_tableaux * sizeof(Tableau));
	else
		machine->tableaux = realloc(machine->tableaux, machine->nb_tableaux * sizeof(Tableau));

	if(!machine->tableaux)
	{
		perror("realloc / malloc");
		exit(EXIT_FAILURE);
	}
}

EtatMachine simulerCycle(Machine* machine)
{
	Plateau instruction;
	int opcode;

	ASSERT_INDEX_PLATEAU_INVALIDE(machine, 0, machine->index_programme);

	instruction = machine->tableaux[0].plateaux[machine->index_programme];

	opcode = instruction >> 28 & 0b1111;
	Registre *registre_a = &machine->registres[instruction >> 6  & 0b0111];
 	Registre *registre_b = &machine->registres[instruction >> 3  & 0b0111];
 	Registre *registre_c = &machine->registres[instruction       & 0b0111];

#ifdef DEBUG
	printf(
		"Cycle n°%i: Instruction: %i, Arguments: ",
		machine->nb_cycles,
		opcode
	);
	if(opcode != 13)
		printf(
			"r%i, r%i, r%i",
			instruction >> 6 & 0b0111,
			instruction >> 3 & 0b0111,
			instruction & 0b0111
		);
	else
		printf(
			"r%i, %i",
			instruction >> 25 & 0b0111,
			instruction & 0x1FFFFFF
		);

	printf("\nRegistres = [");
	for(int i = 0; i < 8; i++)
		printf("%x; ", machine->registres[i]);
	printf(
		"], Index Pointer: %i\n",
		machine->index_programme
	);
#endif

	machine->index_programme ++;
	machine->nb_cycles ++;
	switch(opcode)
	{
	case 0:  return instruction0(machine, registre_a, registre_b, registre_c);
	case 1:  return instruction1(machine, registre_a, registre_b, registre_c);
	case 2:  return instruction2(machine, registre_a, registre_b, registre_c);
	case 3:  return instruction3(machine, registre_a, registre_b, registre_c);
	case 4:  return instruction4(machine, registre_a, registre_b, registre_c);
	case 5:  return instruction5(machine, registre_a, registre_b, registre_c);
	case 6:  return instruction6(machine, registre_a, registre_b, registre_c);
	case 7:  return instruction7(machine, registre_a, registre_b, registre_c);
	case 8:  return instruction8(machine, registre_a, registre_b, registre_c);
	case 9:  return instruction9(machine, registre_a, registre_b, registre_c);
	case 10: return instruction10(machine, registre_a, registre_b, registre_c);
	case 11: return instruction11(machine, registre_a, registre_b, registre_c);
	case 12: return instruction12(machine, registre_a, registre_b, registre_c);
	case 13:
		registre_a = &machine->registres[instruction >> 25 & 0b0111];
		return instruction13(machine, registre_a, instruction & 0x01FFFFFF);
	
	default:
		return E_MAUVAISE_INSTRUCTION;
	}

}

