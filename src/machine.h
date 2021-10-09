#ifndef _MACHINE_H_
#define _MACHINE_H_

#include "tableau.h"

typedef Plateau Registre;
typedef enum EtatMachine EtatMachine;
typedef struct Machine Machine;

enum EtatMachine
{
	E_OK,
	E_FIN_PROGRAMME,
	E_DIV_PAR_0,
	E_SORTIE_INVALIDE,
	E_OUT_OF_BOUNDS,
	E_ACCES_TABLEAU_INACTIF,
	E_MAUVAISE_INSTRUCTION
};

struct Machine
{
	Registre registres[8];
	Registre index_programme;
	unsigned int nb_cycles;

	Tableau* tableaux;
	unsigned int nb_tableaux;
};

void initialiserMachine(Machine* machine);
void ajouterTableau(Machine* machine, unsigned int index);
EtatMachine simulerCycle(Machine* machine);

#endif
