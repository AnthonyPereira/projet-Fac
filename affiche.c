#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "affiche.h"

#define COLOR_RESET   		"\x1b[0m"
#define COLOR_RED     		"\x1b[31m"
#define COLOR_GREEN   		"\x1b[32m"
#define COLOR_YELLOW  		"\x1b[33m"
#define COLOR_BLUE    		"\x1b[34m"
#define COLOR_MAGENTA 		"\x1b[35m"
#define COLOR_CYAN    		"\x1b[36m"
#define BACKGROUND_RED  	"\x1b[41m"
#define BACKGROUND_GREEN 	"\x1b[42m"
#define BACKGROUND_YELLOW  	"\x1b[42m"
#define BACKGROUND_WHITE   	"\x1b[47m"

int lenNombre(int nb){
	int longueur = 0;
	while(nb/10!=0){
		nb/=10;
		longueur++;
	}
	return longueur+1;
}

void printLegFru(int largConsole, int posLeg, int posFruit, char **tabL, char **tabF){
	int i;
	for(i=0; i<5; i++){
		if(posLeg>5){
			printf("%*c", posLeg-5, ' ');
		}
		printf("%s",tabL[i]);
		if(posFruit-posLeg>1){
			printf("%*c", posFruit-posLeg-1, ' ');
		}
		printf("%s\n",tabF[i]);
	}
}

void affichageJeu(int nbColonnes, int nbLignes, Duel *duel, char **tabL, char **tabF){
	int i;
	
	printf("Joueur 1%*cJoueur 2\n", nbColonnes-16, ' ');
	printf("PV : %d%*cPV : %d\n",duel->vieJ1,nbColonnes-(10+lenNombre(duel->vieJ1)+lenNombre(duel->vieJ2)),' ',duel->vieJ2);
    printf("Protection active : ");
    if(duel->protectionActiveJ1)
		printf(BACKGROUND_GREEN"  "COLOR_RESET);
	else
		printf(BACKGROUND_RED"  "COLOR_RESET);
	printf("%*cProtection active : ",nbColonnes-44,' ');
    if(duel->protectionActiveJ2)
		printf(BACKGROUND_GREEN"  \n"COLOR_RESET);
	else
		printf(BACKGROUND_RED"  \n"COLOR_RESET);
	printf("Soins restants : %d%*cSoins restants : %d\n",duel->volumeSoinJ1,nbColonnes-36,' ',duel->volumeSoinJ2);
	
    for(i=0; i<nbLignes-15; i++){
        printf("\n");
    }
    printLegFru(nbColonnes, duel->posJ1, duel->posJ2, tabL, tabF);
    printf("\033[0;41m");
    for(i=0; i<nbColonnes; i++){
		printf(" ");
    }
    printf("\033[0m\n\n");
}
