#ifndef _DUEL_H_
#define _DUEL_H_

#include "initChampion.h"

typedef struct{
	InitChampion *championJ1;
	InitChampion *championJ2;
    int vieJ1;
    int vieJ2;
    int cAJ1;
    int cAMaxJ1;
    int cAJ2;
    int cAMaxJ2;
    int cEJ1;
    int cEequipeJ1;
	int cEequipeJ2;
    int cEJ2;
    int cEuseJ1;
    int cEuseJ2;
    int protectionActiveJ1;
    int protectionActiveJ2;
    int posJ1;
    int posJ2;
    int volumeSoinJ1;
    int volumeSoinJ2;
}Duel;

int choisirPersonnage(Duel *duel, Champion *champion, int joueur);
int choisirArme(Duel *duel, Arme *arme, int joueur);
int choisirProtection(Duel *duel, Protection *protection, int joueur);
int choisirSoin(Duel *duel, Soin *soin, int joueur);
int CEinCA(Duel *duel, int cE, int joueur);
void show(Duel *duel, int joueur);
int moveForward(Duel *duel, int joueur, int taille, int nbPas);
int moveBackward(Duel *duel, int joueur, int taille, int nbPas);
int calculDegat(int degatsBrute, int forceAttaquant, int resistanceDefenseur);
int useWeapon(Duel *duel, int taille, int joueur, int nbHit);
int useProtection(Duel *duel, int joueur);
int useSoin(Duel *duel, int joueur, int nbUse);
void finTour(Duel *duel, int joueur);
void initPos(Duel *duel, int posJ1, int posJ2);
int winDuel(Duel *duel, int joueur);
int winCombat(Duel *duel);

#endif
