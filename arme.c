#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "arme.h"

void insererArme(Arme **tab,int id, char *nom, int cE, int cA, int degatsMin, int degatsMax, int portee){
	Arme *arme = (Arme*) malloc(sizeof(Arme));
	arme->id=id;
	arme->nom=nom;
	arme->cE=cE;
	arme->cA=cA;
	arme->degats.min=degatsMin;
	arme->degats.max=degatsMax;
	arme->portee=portee;
	tab[id]=arme;
}

void printArmes(Arme **arme){
	int i;
	for(i=0;i<NB_ARMES;i++){
		printf("%d- %s \n", i+1, arme[i]->nom); 
	}
}

int printArme(Arme **arme, int i){
	i--;
	if(i>=0 && i<NB_ARMES){
		printf("Nom : %s | CE : %d | CA : %d | Dégats : %d-%d | Portée : %d\n", arme[i]->nom, arme[i]->cE, arme[i]->cA, arme[i]->degats.min, arme[i]->degats.max, arme[i]->portee); 
		return 0;
	}
	return -1;
}

void print1Arme(Arme *arme){
    printf("Arme : %s | CE : %d | CA : %d | Dégats : %d-%d | Portée : %d\n", arme->nom, arme->cE, arme->cA, arme->degats.min, arme->degats.max, arme->portee);
}

int touche(Arme arme, int distance){
	return arme.portee>distance;
}

int hit(Arme arme){
	return ((rand() % (arme.degats.max - arme.degats.min)) + arme.degats.min);
}

Arme **creerTableauArme(){
	int id=0;
	Arme **tab=(Arme **) malloc(NB_ARMES*sizeof(Arme));
	insererArme(tab,id++,"Éplucheur Laser",2,1,1,2,2);
	insererArme(tab,id++,"Mandoline Sonique",5,3,1,3,3);
	insererArme(tab,id++,"Couperet Laser",10,5,2,6,5);
	insererArme(tab,id++,"Hachoir Neuronique",20,7,4,9,7);
	insererArme(tab,id++,"Mixeur Blaster",30,10,7,12,11);
	return tab;
}
