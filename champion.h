#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#define NB_CHAMPIONS 12

enum Type{Fruit, Legume};

typedef struct{
	int id;
	char *variete;
	enum Type typ;
	int force;
	int resistance;
	int pvMax;
	int cE;
}Champion;

/*fruit*/
void printFruits(Champion **fruit);
int printFruit(Champion **fruit, int i);
int estFruit(Champion *fruit);

/*legume*/
void printLegumes(Champion **legume);
int printLegume(Champion **legume, int i);
int estLegume(Champion *legume);

/*commun*/
void printChampion(Champion champion);

void insererChampion(Champion **tab, int id, char *variete, enum Type typ, int force, int resistance, int pvMax, int cE);

Champion **creerTableauChampion();

#endif
