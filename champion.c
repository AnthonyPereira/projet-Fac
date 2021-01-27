#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "champion.h"

/*commun */
void insererChampion(Champion **tab, int id, char *variete, enum Type typ, int force, int resistance, int pvMax, int cE){
	Champion *champion = (Champion*) malloc(sizeof(Champion));
	champion->id=id;
	champion->variete=variete;
	champion->typ=typ;
	champion->force=force;
	champion->resistance=resistance;
	champion->pvMax=pvMax;
	champion->cE=cE;
	tab[id]=champion;
}

Champion **creerTableauChampion(){
	int id=0;
	Champion **tab=(Champion **) malloc(NB_CHAMPIONS*sizeof(Champion));
	insererChampion(tab,id++,"Haricot",Legume,10,10,40,5);
	insererChampion(tab,id++,"Fenouil",Legume,12,15,40,7);
	insererChampion(tab,id++,"Poireau",Legume,15,20,60,10);
	insererChampion(tab,id++,"Aubergine",Legume,20,20,60,15);
	insererChampion(tab,id++,"Courgette",Legume,20,25,80,20);
	insererChampion(tab,id++,"Carotte",Legume,25,25,80,25);
	insererChampion(tab,id++,"Banane",Fruit,10,10,40,5);
	insererChampion(tab,id++,"Kiwi",Fruit,12,15,40,7);
	insererChampion(tab,id++,"Poire",Fruit,15,20,60,10);
	insererChampion(tab,id++,"Pomme",Fruit,20,20,60,15);
	insererChampion(tab,id++,"Ananas",Fruit,20,25,80,20);
	insererChampion(tab,id++,"Durian",Fruit,25,25,80,25);
	return tab;

}

void printChampion(Champion champion){
	char *type;
	if(champion.typ==1){
		type = "Légume";
	}
	else{
		type = "Fruit";
	}
	printf("Variété : %s | Type : %s | Force : %d | Résistance : %d | PV Max : %d | CE : %d\n", champion.variete, type, champion.force, champion.resistance, champion.pvMax, champion.cE);
}

/*fruit */
int estFruit(Champion *fruit){
	return fruit->typ==Fruit;
}

void printFruits(Champion **fruit){
	int i, cpt=1;
	for(i=0;i<NB_CHAMPIONS;i++){
		if(estFruit(fruit[i])){
			printf("%d- %s\n", cpt++, fruit[i]->variete);
		}
	}
}

int printFruit(Champion **fruit, int i){
	int j, cpt=0;
	i--;
	for(j=0;j<NB_CHAMPIONS;j++){
		if(estFruit(fruit[j])){
			if(cpt==i){
				printChampion(*fruit[j]);
				return 0;
			}
			cpt+=1;
		}
	}
	return -1;
}

/*legume */
int estLegume(Champion *legume){
	return legume->typ==Legume;
}

void printLegumes(Champion **legume){
	int i, cpt=1;
	for(i=0;i<NB_CHAMPIONS;i++){
		if(estLegume(legume[i])){
			printf("%d- %s\n", cpt++, legume[i]->variete);
		}
	}
}

int printLegume(Champion **legume, int i){
	int j, cpt=0;
	i--;
	for(j=0;j<NB_CHAMPIONS;j++){
		if(estLegume(legume[j])){
			if(cpt==i){
				printChampion(*legume[i]);
				return 0;
			}
			cpt+=1;
		}
	}
	return -1;
}
