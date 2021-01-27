#ifndef _ARME_H_
#define _ARME_H_

#define NB_ARMES 5

typedef struct{
	int min;
	int max;
}Degats;

typedef struct{
	int id;
	char *nom;
	int cE;
	int cA;
	Degats degats;
	int portee;
}Arme;

void insererArme(Arme **tab,int id, char *nom, int cE, int cA, int degatsMin, int degatsMax, int portee);
void printArmes(Arme **arme);
int printArme(Arme **arme, int i);
void print1Arme(Arme *arme);
int touche(Arme arme, int distance);
int hit(Arme arme);
Arme **creerTableauArme();

#endif
