#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "duel.h"

#define CA 50
#define CE 50

int checkCE(int cE){
    if (cE<0){
        return 1;
    }
    return 0;
}

int choisirPersonnage(Duel *duel, Champion *champion, int joueur){
	/* 
	 * 
	 * retourne 0 si tout s'est bien passé
	 * retourne -2 si ce du joueur insuffisant
	 * retourne -1 sinon
	 * 
	 */
	if(joueur==1){
		duel->cEuseJ1 = 0;
		if(duel->cEequipeJ1 >= CE){
			duel->cEJ1 = CE;
		}
		else{
			duel->cEJ1 = duel->cEequipeJ1;
		}
		if(duel->cEJ1 < champion->cE+2){
			return -2;
		}
		
		duel->championJ1->champion=champion;
		duel->vieJ1 = champion->pvMax;
		duel->cEJ1 -= champion->cE;
		duel->cEequipeJ1 -= champion->cE;
		duel->cEuseJ1 += champion->cE;
		return 0 ;
	}
	else if(joueur == 2){
		duel->cEuseJ2 = 0;
		if(duel->cEequipeJ2 >= CE){
			duel->cEJ2 = CE;
		}
		else{
			duel->cEJ2 = duel->cEequipeJ2;
		}
		if(duel->cEJ2 < champion->cE+2){
			return -2;
		}
		duel->championJ2->champion=champion;
		duel->vieJ2 = champion->pvMax;
		duel->cEJ2 -= champion->cE;
		duel->cEequipeJ2 -= champion->cE;
		duel->cEuseJ2 += champion->cE;
		return 0 ;
	}
	return -1;
} 

int choisirArme(Duel *duel, Arme *arme, int joueur){
	/* 
	 * 
	 * retourne 0 si tout s'est bien passé
	 * retourne -1 sinon
	 * 
	 */
	if (joueur==1){
		if(duel->cEJ1 >= arme->cE){
			duel->championJ1->arme = arme;
			duel->cEJ1 -= arme->cE;
			duel->cEequipeJ1 -= arme->cE;
			duel->cEuseJ1 += arme->cE;
			return 0;
		}
	}
	else if (joueur==2){
		if(duel->cEJ2 >= arme->cE){
			duel->championJ2->arme = arme;
			duel->cEJ2 -= arme->cE;
			duel->cEequipeJ2 -= arme->cE;
			duel->cEuseJ2 += arme->cE;
			return 0;
		}
	}
	return -1;
}

int choisirProtection(Duel *duel, Protection *protection, int joueur){
	/* 
	 * 
	 * retourne 0 si tout s'est bien passé
	 * retourne -1 sinon
	 * 
	 */
	if (joueur==1){
		if(protection == NULL){
			duel->championJ1->protection=protection;
			return CE-duel->championJ1->arme->cE-duel->championJ1->champion->cE;
		}
		else if(duel->cEJ1 >= protection->cE){
			duel->championJ1->protection=protection;
			duel->cEJ1 -= protection->cE;
			duel->cEequipeJ1 -= protection->cE;
			duel->cEuseJ1 += protection->cE;
			return 0;
		}
	}
	else if (joueur==2){
		if(protection == NULL){
			duel->championJ2->protection=protection;
			return CE-duel->championJ2->arme->cE-duel->championJ1->champion->cE;
		}
		else if(duel->cEJ2 >= protection->cE){
			duel->championJ2->protection=protection;
			duel->cEJ2 -= protection->cE;
			duel->cEequipeJ2 -= protection->cE;
			duel->cEuseJ2 += protection->cE;
			return 0;
		}
	}
	return -1;
}

int choisirSoin(Duel *duel, Soin *soin, int joueur){
	/* 
	 * 
	 * retourne 0 si tout s'est bien passé
	 * retourne -1 sinon
	 * 
	 */
	if(joueur==1){
		if(soin == NULL){
			duel->volumeSoinJ1=0;
			duel->championJ1->soin=soin;
			return 0;
		}
		if(duel->cEJ1 >= soin->cE){
			duel->championJ1->soin=soin;
			duel->volumeSoinJ1=soin->volumes;
			duel->cEJ1 -= soin->cE;
			duel->cEequipeJ1 -= soin->cE;
			duel->cEuseJ1 += soin->cE;
			return 0;
		}
	}
	else if(joueur==2){
		if(soin == NULL){
			duel->volumeSoinJ2=0;
			duel->championJ2->soin=soin;
			return 0;
		}
		if(duel->cEJ2 >= soin->cE){
			duel->championJ2->soin=soin;
			duel->volumeSoinJ2=soin->volumes;
			duel->cEJ2 -= soin->cE;
			duel->cEequipeJ2 -= soin->cE;
			duel->cEuseJ2 += soin->cE;
			return 0;
		}
	}
	return -1;
}

int CEinCA(Duel *duel, int cE, int joueur){
	/* 
	 * 
	 * retourne cE restant si tout s'est bien passé
	 * retourne -1 sinon
	 * 
	 */
	
	if(joueur == 1){
		if(cE<=duel->cEJ1){
			duel->cAMaxJ1=cE+CA;
			duel->cAJ1=duel->cAMaxJ1;
			duel->cEJ1 -= cE;
			duel->cEequipeJ1 -= cE;
			duel->cEuseJ1 += cE;
			return 0;
		}
	}
	if(joueur == 2){
		if(cE<=duel->cEJ2){
			duel->cAMaxJ2=cE+CA;
			duel->cAJ2=duel->cAMaxJ2;
			duel->cEJ2 -= cE;
			duel->cEequipeJ2 -= cE;
			duel->cEuseJ2 += cE;
			return 0;
		}
	}
	return -1;
}

int moveForward(Duel *duel, int joueur, int taille, int nbPas){
	/* retourne -1 si joueur passe de l'autre coté du joueur
	 * retourne -2 si le joueur n'as pas assez de CA
	 * retourne 0 si tout se passe bien 
	 */
    if(joueur == 1){
        if(duel->cAJ1-nbPas<0){
            return -2;
        }
        if(duel->posJ1+nbPas>=duel->posJ2){
            return -1;
        }
        duel->posJ1+=nbPas;
        duel->cAJ1-=nbPas;
    }

    else if (joueur == 2){
        if(duel->cAJ2-nbPas<0){
            return -2;
        }
        if (duel->posJ2-nbPas<=duel->posJ1){
            return -1;
        }
        duel->posJ2-=nbPas;
        duel->cAJ2-=nbPas;
    }
    return 0;
}

int moveBackward(Duel *duel, int joueur, int taille, int nbPas){
	/* retourne -1 si hors des limites du terrain
	 * retourne -2 si le joueur n'as pas assez de CA
	 * retourne 0 si tout se passe bien 
	 */
    if(joueur == 1){
        if(duel->cAJ1-(nbPas*2)<0){
            return -2;
        }
        if(duel->posJ1-nbPas<5){
            return -1;
        }
        duel->posJ1-=nbPas;
        duel->cAJ1-=(nbPas*2);
    }
    else if(joueur == 2){
        if(duel->cAJ2-(nbPas*2)<0){
            return -2;
        }
        if (duel->posJ2+nbPas>=taille-4){
            return -1;
        }
        duel->posJ2+=nbPas;
        duel->cAJ2-=(nbPas*2);
    }
    return 0;
}

void show(Duel *duel, int joueur){
	if(joueur == 1){
		print1Arme(duel->championJ1->arme);
		if(duel->championJ1->protection != NULL){
			print1Protection(duel->championJ1->protection);
			if(duel->protectionActiveJ1){
				printf(" (active)\n");
			}
			else{
				printf(" (non-active)\n");
			}
		}
		if(duel->championJ1->soin != NULL){
			print1Soin(duel->championJ1->soin);
		}
    }
    else if(joueur == 2){
		print1Arme(duel->championJ2->arme);
		if (duel->championJ2->protection != NULL){
			print1Protection(duel->championJ2->protection);
			if(duel->protectionActiveJ2){
				printf(" (active)\n");
            }
			else{
				printf(" (non-active)\n");
			}
		}
		if(duel->championJ2->soin != NULL){
			print1Soin(duel->championJ2->soin);
		}
    }
}

int useProtection(Duel *duel, int joueur){
	/*
	retourne -1 quand déjà équipée
    retourne -2 quand ne peut pas équiper à cause des CA
    retourne 0 quand a pu équiper
    */
    if(joueur == 1 && !duel->protectionActiveJ1){
		if(duel->championJ1->protection == NULL){
			return -3;
		}
		if(duel->cAJ1>=duel->championJ1->protection->cA){
			duel->protectionActiveJ1=1;
			duel->cAJ1-=duel->championJ1->protection->cA;
			return 0;
		}
		return -2;
    }
    else if (joueur == 2 && !duel->protectionActiveJ2){
		if(duel->championJ2->protection == NULL){
			return -3;
		}
		if(duel->cAJ2>=duel->championJ2->protection->cA){
			duel->protectionActiveJ2=1;
			duel->cAJ2-=duel->championJ1->protection->cA;
			return 0;
		}
		return -2;
    }
    return -1;
}

int calculDegat(int degatsBrute, int forceAttaquant, int resistanceDefenseur){
	return degatsBrute*((100+forceAttaquant)/100)*((100+resistanceDefenseur)/100)+0.5;
}

int useWeapon(Duel *duel, int taille, int joueur, int nbHit){
    /*
    retourne -1 quand cout trop fort en action
    retourne -2 quand pas a portée
    retourne 0 quand tout c'est bien passé
    */
    int distance=duel->posJ2-duel->posJ1;
    int degats;
    int i;
    if(joueur == 1){
        if(duel->cAJ1<(nbHit*duel->championJ1->arme->cA)){
            return -1;
        }
        if(distance>duel->championJ1->arme->portee){
			duel->cAJ1-=nbHit*duel->championJ1->arme->cA;
            return -2;
        }
        else{
            for(i=0; i<nbHit;i++){
				degats = calculDegat(hit(*duel->championJ1->arme), duel->championJ1->champion->force, duel->championJ1->champion->resistance);
                if(duel->championJ2->protection!=NULL && duel->protectionActiveJ2){
					if(!protege(*duel->championJ2->protection)){
						duel->vieJ2-=degats;
					}
				}
                else {
                    duel->vieJ2-=degats;
                }
                duel->cAJ1-=duel->championJ1->arme->cA;
            }
       }
    }
    else if(joueur == 2){
        if(duel->cAJ2<(nbHit*duel->championJ2->arme->cA)){
            return -1;
        }
        if(distance>duel->championJ2->arme->portee){
			duel->cAJ2-=nbHit*duel->championJ2->arme->cA;
            return -2;
        }
        else{
            for(i=0; i<nbHit;i++){
				degats = calculDegat(hit(*duel->championJ2->arme), duel->championJ2->champion->force, duel->championJ2->champion->resistance);
                if(duel->protectionActiveJ1 && duel->championJ1->protection!=NULL){
					if(!protege(*duel->championJ1->protection)){
						duel->vieJ1-=degats;   
					}
				}	
                else {
                    duel->vieJ1-=degats;
                }
                duel->cAJ2-=duel->championJ2->arme->cA;
            }
        }
    }
    return 0;
}

int useSoin(Duel *duel, int joueur, int nbUse){
    /*
    retourne -1 quand cA insuffisant
    retourne -2 quand volume insuffisant
    retourne -3 quand vie déjà max
    retourne 0 quand bien passer
    */
    int i, soignez;
    
    if(joueur == 1){
		if(duel->volumeSoinJ1 < nbUse){
			return -2;
		}
        if(duel->cAJ1 < duel->championJ1->soin->cA*nbUse){
            return -1;
        }
        if(duel->vieJ1 == duel->championJ1->champion->pvMax){
			return -3;
		}
        soignez=soin(*duel->championJ1->soin);
        for(i=0;i<nbUse && duel->vieJ1+soignez;i++){
			if(soignez+duel->vieJ1 < duel->championJ1->champion->pvMax){
				duel->vieJ1+=soignez;
			}
			else{
				duel->vieJ1 = duel->championJ1->champion->pvMax;			
			}
            soignez=soin(*duel->championJ1->soin);
            duel->cAJ1-=duel->championJ1->soin->cA;
			duel->volumeSoinJ1--;
        }
	}
	if(joueur == 2){
		if(duel->volumeSoinJ2 < nbUse){
			return -2;
		}
        if(duel->cAJ2<duel->championJ2->soin->cA*nbUse){
            return -1;
        }
        if(duel->vieJ2 == duel->championJ2->champion->pvMax){
			return -3;
		}
        soignez=soin(*duel->championJ2->soin);
        for(i=0;i<nbUse && duel->vieJ2+soignez;i++){
            if(soignez+duel->vieJ2 < duel->championJ2->champion->pvMax){
				duel->vieJ2+=soignez;
			}
			else{
				duel->vieJ2 = duel->championJ2->champion->pvMax;			
			}
            soignez=soin(*duel->championJ2->soin);
            duel->cAJ2-=duel->championJ2->soin->cA;
            duel->volumeSoinJ2--;
        }
    }
    return 0;
}

void finTour(Duel *duel, int joueur){
	if(joueur == 1){
		duel->cAJ1=duel->cAMaxJ1;
		duel->protectionActiveJ2=0;
		if(duel->championJ1->soin != NULL){
			duel->volumeSoinJ1=duel->championJ1->soin->volumes;
		}	
	}
	else{
		duel->cAJ2=duel->cAMaxJ2;
		duel->protectionActiveJ1=0;
		if(duel->championJ2->soin != NULL){
			duel->volumeSoinJ2=duel->championJ2->soin->volumes;
		}
	}
}

void initPos(Duel *duel, int posJ1, int posJ2){
	duel->posJ1 = posJ1;
	duel->posJ2 = posJ2;
}

int winDuel(Duel *duel, int joueur){
	if(joueur == 1 && duel->vieJ2 <= 0){
		return 1;
	}
	else if(joueur == 2 && duel->vieJ1 <= 0){
		return 1;
	}
	return 0;
}

int winCombat(Duel *duel){
	/* 
	 * 
	 * retourne l'equipe gagnante si l'une d'entre elle a gagné 
	 * retourne 0 sinon
	 * 
	 */
	if(duel->cEequipeJ1 < 7){
		return 2;
	}
	else if(duel->cEequipeJ2 < 7){
		return 1;
	}
	return 0;
}
