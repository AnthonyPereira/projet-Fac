#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "soin.h"

void insererSoin(Soin **tab, int id, char *nom, int cE, int cA, int volumes, int effetMin, int effetMax){
	Soin *soin = (Soin*) malloc(sizeof(Soin));
	soin->id=id;
	soin->nom=nom;
	soin->cE=cE;
	soin->cA=cA;
	soin->volumes=volumes;
	soin->effet.min=effetMin;
	soin->effet.max=effetMax;
	tab[id]=soin;
}
void printSoins(Soin **soin){
	int i;
	for(i=0;i<NB_SOINS;i++){
		printf("%d- %s\n", i+1, soin[i]->nom); 
	}
}

int printSoin(Soin **soin, int i){
	i--;
	if(i>=0 && i<NB_SOINS){
		printf("Nom : %s | CE : %d | CA : %d | Volumes : %d | Effet : %d-%d\n", soin[i]->nom, soin[i]->cE, soin[i]->cA, soin[i]->volumes, soin[i]->effet.min, soin[i]->effet.max); 
		return 0;
	}
	return -1;
}

void print1Soin(Soin *soin){
    printf("Soin : %s | CE : %d | CA : %d | Volumes : %d | Effet : %d-%d\n", soin->nom, soin->cE, soin->cA, soin->volumes, soin->effet.min, soin->effet.max);
}

int soin(Soin soin){
	return ((rand() % (soin.effet.max - soin.effet.min)) + soin.effet.min);
}


Soin **creerTableauSoin(){
	int id=0;
	Soin **tab=(Soin **) malloc(NB_SOINS*sizeof(Soin));
	insererSoin(tab,id++,"Humus-Neutronique",1,5,4,2,4);
	insererSoin(tab,id++,"Compost-Protonique",5,10,3,5,8);
	insererSoin(tab,id++,"Engrais-Ionique",7,15,2,8,12);
	return tab;
}
