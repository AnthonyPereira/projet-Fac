#ifndef _INITCHAMPION_H_
#define _INITCHAMPION_H_

#include "champion.h"
#include "protection.h"
#include "arme.h"
#include "soin.h"

typedef struct{
	Champion *champion;
	Protection *protection;
	Arme *arme;
	Soin *soin; 
}InitChampion;

void defineChampion(InitChampion *initChampion, Champion champion);
int ajoutProtection(InitChampion *initChampion, Protection protection);
int ajoutArme(InitChampion *initChampion, Arme arme);
int ajoutSoin(InitChampion *initChampion, Soin soin);

void supprChampion(InitChampion *initChampion);
void supprProtection(InitChampion *initChampion);
void supprArme(InitChampion *initChampion);
void supprSoin(InitChampion *soin);

int peutCombattre(InitChampion *initChampion);

#endif
