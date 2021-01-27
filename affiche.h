#ifndef _AFFICHE_H_
#define _AFFICHE_H_

#include "duel.h"

int lenNombre(int nb);
void printLegFru(int largConsole, int posLeg, int posFruit, char **tabL, char **tabF);
void affichageJeu(int nbColonnes, int nbLignes, Duel *duel, char **tabL, char **tabF);

#endif
