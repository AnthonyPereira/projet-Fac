#ifndef _PROTECTION_H_
#define _PROTECTION_H_

#define NB_PROTECTIONS 4

typedef struct{
	int id;
	char *nom;
	int cE;
	int cA;
	int probabilite;
}Protection;

void insererProtection(Protection **tab, int id, char *nom, int cE, int cA, int probabilite);
void printProtections(Protection **protection);
int printProtection(Protection **protection, int i);
void print1Protection(Protection *protection);
int protege(Protection protection);
Protection **creerTableauProtection();

#endif
