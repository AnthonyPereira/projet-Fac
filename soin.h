#ifndef _SOIN_H_
#define _SOIN_H_

#define NB_SOINS 3

typedef struct{
	int min;
	int max;
}Effet;

typedef struct{
	int id;
	char *nom;
	int cE;
	int cA;
	int volumes;
	Effet effet;
}Soin;

void insererSoin(Soin **tab, int id, char *nom, int cE, int cA, int Volumes, int effetMin, int effetMax);
void printSoins(Soin **soin);
int printSoin(Soin **soin, int i);
void print1Soin(Soin *soin);
int soin(Soin soin);
Soin **creerTableauSoin();

#endif
