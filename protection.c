#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "protection.h"

void insererProtection(Protection **tab,int id, char *nom, int cE, int cA, int probabilite){
	Protection *protection = (Protection*) malloc(sizeof(Protection));
	protection->id=id;
	protection->nom=nom;
	protection->cE=cE;
	protection->cA=cA;
	protection->probabilite=probabilite;
	tab[id]=protection;
}

void printProtections(Protection **protection){
	int i;
	for(i=0;i<NB_PROTECTIONS;i++){
		printf("%d- %s\n", i+1, protection[i]->nom); 
	}
}

int printProtection(Protection **protection, int i){
	i--;
	if(i>=0 && i<NB_PROTECTIONS){
		printf("Nom : %s | CE : %d | CA : %d | Probabilité : %d\n", protection[i]->nom, protection[i]->cE, protection[i]->cA, protection[i]->probabilite); 
		return 0;
	}
	return -1;
}

void print1Protection(Protection *protection){
    printf("Protection : %s | CE : %d | CA : %d | Probabilité : %d", protection->nom, protection->cE, protection->cA, protection->probabilite);
}

int protege(Protection protection){
	srand(time(NULL));
	return (protection.probabilite>(rand() % 101));
}

Protection **creerTableauProtection(){
	int id=0;
	Protection **tab=(Protection **) malloc(NB_PROTECTIONS*sizeof(Protection));
	insererProtection(tab,id++,"Casque-Égouttoir",1,2,25);
	insererProtection(tab,id++,"Casque-Entonnoir",3,4,40);
	insererProtection(tab,id++,"Woklier",5,6,60);
	insererProtection(tab,id++,"Tablier-Armure",10,8,80);
	return tab;

}
