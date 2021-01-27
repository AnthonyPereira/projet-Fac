#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "initChampion.h"

#define CEMAX 50

void defineChampion(InitChampion *initChampion, Champion champion){
	initChampion->champion=&champion;
}
int ajoutProtection(InitChampion *initChampion, Protection protection){
	if(initChampion->arme==NULL && initChampion->soin==NULL &&  CEMAX >= protection.cE+initChampion->champion->cE){
		initChampion->protection= &protection;
		return 0;
	}
	else if(initChampion->soin==NULL && CEMAX >= (initChampion->champion->cE+protection.cE + initChampion->arme->cE)){
		initChampion->protection= &protection;
		return 0;
	}
	else if(initChampion->arme==NULL &&  CEMAX >= (initChampion->champion->cE+protection.cE + initChampion->soin->cE)){
		initChampion->protection= &protection;
		return 0;
	}
	else if( CEMAX >= (initChampion->champion->cE+protection.cE + initChampion->arme->cE + initChampion->soin->cE)){
		initChampion->protection= &protection;
		return 0;
	}
	return -1;
}
	
int ajoutArme(InitChampion *initChampion, Arme arme){
	if(initChampion->protection==NULL && initChampion->soin==NULL && CEMAX >= initChampion->champion->cE+arme.cE){
		initChampion->arme= &arme;
		return 0;
	}
	else if(initChampion->soin==NULL && CEMAX >= ( initChampion->champion->cE+arme.cE + initChampion->protection->cE)){
		initChampion->arme= &arme;
		return 0;
	}
	else if(initChampion->protection==NULL && CEMAX >= (initChampion->champion->cE+arme.cE + initChampion->soin->cE)){
		initChampion->arme= &arme;
		return 0;
	}
	else if(CEMAX >= (initChampion->champion->cE+arme.cE + initChampion->protection->cE + initChampion->soin->cE)){
		initChampion->arme= &arme;
		return 0;
	}
	return -1;
}

int ajoutSoin(InitChampion *initChampion, Soin soin){
	if(initChampion->protection==NULL && initChampion->arme==NULL &&  CEMAX >= initChampion->champion->cE+soin.cE){
		initChampion->soin= &soin;
		return 0;
	}
	else if(initChampion->arme==NULL && CEMAX >= (initChampion->champion->cE+soin.cE + initChampion->protection->cE)){
		initChampion->soin= &soin;
		return 0;
	}
	else if(initChampion->protection==NULL && CEMAX >= (initChampion->champion->cE+soin.cE + initChampion->arme->cE)){
		initChampion->soin= &soin;
		return 0;
	}
	else if(CEMAX >= (initChampion->champion->cE+soin.cE + initChampion->protection->cE + initChampion->arme->cE)){
		initChampion->soin= &soin;
		return 0;
	}
	return -1;
}

void supprChampion(InitChampion *initChampion){
	initChampion->champion=NULL;
}
void supprProtection(InitChampion *initChampion){
	initChampion->protection=NULL;
}
void supprArme(InitChampion *initChampion){
	initChampion->arme=NULL;
}
void supprSoin(InitChampion *initChampion){
	initChampion->soin=NULL;
}

int peutCombattre(InitChampion *initChampion){
	int cE=0;
	if (initChampion->protection!=NULL) cE+=initChampion->protection->cE;
	if (initChampion->arme!=NULL) cE += initChampion->arme->cE;
	if (initChampion->soin!=NULL) cE += initChampion->soin->cE;
	return (cE <= initChampion->champion->cE);
}
