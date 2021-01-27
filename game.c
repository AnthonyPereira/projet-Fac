#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "affiche.h"

#define max(a,b) (a>=b?a:b)

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

void clear(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void viderBuffer(){
    int c = 0;
    while(c != '\n' && c != EOF){
        c = getchar();
    }
}

int afficheChoixArme(Arme **tabArme, int affiche){ /* demander joueur en paramètre */
	int i;
	char monChiffre[4];
	char *chaineValide = NULL;
	int valArme;
	
	if(!affiche){
		for(i=1; i<=NB_ARMES; i++){
			printf(COLOR_YELLOW "[%d] " COLOR_RESET, i);
			printArme(tabArme, i);
		}
	}
	do{
		printf("\nArme> ");
		fgets(monChiffre,4,stdin);
		chaineValide = strchr(monChiffre, '\n');
		if(chaineValide == NULL){
			printf("Valeur invalide : veuillez saisir un entier compris entre 1 et 5\n");
			viderBuffer();
		}
		else{
			valArme = atoi(monChiffre);
			if(valArme<1 || valArme>NB_ARMES){
				printf("Valeur invalide : veuillez saisir un entier compris entre 1 et 5\n");
				chaineValide=NULL;
			}
		}
	}while(chaineValide==NULL);
	
	return valArme-1;
}

int afficheChoixProtection(Protection **tabProtection, int affiche){ /* demander joueur en paramètre */
	int i;
	char monChiffre[4];
	char *chaineValide = NULL;
	int valProtec;
	
	if(!affiche){
		printf(COLOR_YELLOW "[-1] " COLOR_RESET "Aucune protection\n");
		for(i=1; i<=NB_PROTECTIONS; i++){
			printf(COLOR_YELLOW "[%d] " COLOR_RESET, i);
			printProtection(tabProtection, i);
		}
	}
	do{
		printf("\nProtection> ");
		fgets(monChiffre,4,stdin);
		chaineValide = strchr(monChiffre, '\n');
		if(chaineValide == NULL){
			printf("Valeur invalide : veuillez saisir un entier compris entre 1 et 4 (ou -1 si vous ne souhaitez pas de protection pour le duel)\n");
			viderBuffer();
		}
		else{
			valProtec = atoi(monChiffre);
			if((valProtec<1 || valProtec>NB_PROTECTIONS) && valProtec!=-1){
				printf("Valeur invalide : veuillez saisir un entier compris entre 1 et 4 (ou -1 si vous ne souhaitez pas de protection pour le duel)\n");
				chaineValide=NULL;
			}
		}
	}while(chaineValide==NULL);
	
	if(valProtec == -1){
		return valProtec;
	}
	return valProtec-1;
}

int afficheChoixSoin(Soin **tabSoin, int affiche){ /* demander joueur en paramètre */
	int i;
	char monChiffre[4];
	char *chaineValide = NULL;
	int valSoin;
	
	if(!affiche){
		printf(COLOR_YELLOW "[-1] " COLOR_RESET "Aucun soin\n");
		for(i=1; i<=NB_SOINS; i++){
			printf(COLOR_YELLOW "[%d] " COLOR_RESET, i);
			printSoin(tabSoin, i);
		}
	}
	do{
		printf("\nSoin> ");
		fgets(monChiffre,4,stdin);
		chaineValide = strchr(monChiffre, '\n');
		if(chaineValide == NULL){
			printf("Valeur invalide : veuillez saisir un entier compris entre 1 et 3 (ou -1 si vous ne souhaitez pas de soin pour le duel)\n");
			viderBuffer();
		}
		else{
			valSoin = atoi(monChiffre);
			if((valSoin<1 || valSoin>NB_SOINS) && valSoin!=-1){
				printf("Valeur invalide : veuillez saisir un entier compris entre 1 et 3 (ou -1 si vous ne souhaitez pas de soin pour le duel)\n");
				chaineValide=NULL;
			}
		}
	}while(chaineValide==NULL);
	
	if(valSoin == -1){
		return valSoin;
	}
	return valSoin-1;
}

int afficheChoixAchatCA(int affiche){ /* demander joueur en paramètre */
	char monChiffre[4];
	char *chaineValide = NULL;
	int valAchat;
	
	if(!affiche){
		printf(COLOR_YELLOW "[?] " COLOR_RESET "Combien de CA souhaitez-vous acheter ?\n");
	}
	do{
		printf("\nAchat CA> ");
		fgets(monChiffre,4,stdin);
		chaineValide = strchr(monChiffre, '\n');
		if(chaineValide == NULL){
			printf("Valeur invalide : veuillez saisir un entier compris entre 0 et 50\n");
			viderBuffer();
		}
		else{
			valAchat = atoi(monChiffre);
			if(valAchat<0 || valAchat>50){
				printf("Valeur invalide : veuillez saisir un entier compris entre 0 et 50\n");
				chaineValide=NULL;
			}
		}
	}while(chaineValide==NULL);
	
	return valAchat;
}

int gestionCommandes(Champion **tabChampion, Protection **tabProtection, Soin **tabSoin, Arme **tabArme, int *combatEnCours, Duel *duel, int *cptTourDuel, int largeurTerminal, int hauteurTerminal, char **tabL, char **tabF, char **messPrec, int *showed, int *winDudu){
	char *tab[4];
	char ligneCommande[100];
	char validationExit;
	char validationReset;
	int nbArgs=0; /* Nb arguments ligne de commande (compte également le nom de la commande) */
	char *ptr;
	char *chaineValide = NULL;
	int joueur = ((*cptTourDuel)%2)+1;
	int finT;
	int winWar;
	
	if(*combatEnCours){
		clear();
		affichageJeu(largeurTerminal, hauteurTerminal, duel, tabL, tabF);
		printf("%s", *messPrec);
		if(*showed){
			show(duel, joueur);
			*showed = 0;
		}
		if(*winDudu == 1){
			*winDudu = 0;
			*combatEnCours = 0;
			clear();
			printf("Bravo a toi Joueur %d, tu as gagné le duel !\n", (((*cptTourDuel)-1)%2)+1);
			winWar = winCombat(duel);
			if(winWar != 0){
				printf("L'équipe %d a complètement ravagé l'autre équipe !\n", winWar);
				do{
					printf("Voulez-vous recommencer une partie ? ['Y' pour oui / 'n' sinon] : ");
					validationReset = getchar();
					if(validationReset=='\n')
						continue;
					viderBuffer();
				}while(validationReset != 'Y' && validationReset != 'n');
				
				if(validationReset=='Y'){
					duel->cEequipeJ1 = 1000;
					duel->cEequipeJ2 = 1000;
					clear();
					printf("Nombre CE Légumes : %d | Nombre CE Fruits : %d\n",duel->cEequipeJ1,duel->cEequipeJ2);
					printf("\n> ");
				}
				else{
					return 1;
				}
			}
			else{
				printf("\n> ");
			}
		}
		else{
			if(joueur == 1){
				printf("%s (%d)> ", duel->championJ1->champion->variete, duel->cAJ1);
			}
			else if (joueur == 2){
				printf("%s (%d)> ", duel->championJ2->champion->variete, duel->cAJ2);
			}
		}
	}
	else{
		printf("\n> ");
	}
	
	fgets(ligneCommande,100,stdin);
	chaineValide = strchr(ligneCommande, '\n');
	if(chaineValide == NULL){
		printf("Commande invalide\n");
		viderBuffer();
		return 0;
	}

	ligneCommande[strcspn(ligneCommande,"\n")] = '\0';
	
	ptr = strtok(ligneCommande," ");
	while(ptr != NULL){
		if(nbArgs<4){
			tab[nbArgs] = ptr;
		}
		ptr = strtok(NULL," ");
		nbArgs++;
	}
	
	if(nbArgs==0){
		if(*combatEnCours){
			*messPrec = "Veuillez entrer une commande à exécuter\n\n\n";
		}
		else{
			printf("Veuillez entrer une commande à exécuter\n");
		}
	}
	else if(strcmp(tab[0],"exit")==0){
		if(nbArgs==1){
			do{
				printf("Voulez-vous vraiment quitter le jeu ? ['Y' pour quitter / 'n' sinon] : ");
				validationExit = getchar();
				if(validationExit=='\n')
					continue;
				viderBuffer();
			}while(validationExit != 'Y' && validationExit != 'n');
			
			return validationExit == 'Y';
		}
		printf("Commande invalide : trop d'arguments (\"exit\" sans argument pour quitter)\n");
	}
	else if(*combatEnCours == 0){
		if(strcmp(tab[0],"show")==0){
			if(nbArgs>3){
				printf("Commande invalide : \"show\" ne peut avoir que 2 arguments maximum\n");
			}
			else if(nbArgs==2){
				if(strcmp(tab[1],"vegetables")==0){
					printLegumes(tabChampion);
				}
				else if(strcmp(tab[1],"fruits")==0){
					printFruits(tabChampion);
				}
				else if(strcmp(tab[1],"weapons")==0){
					printArmes(tabArme);
				}
				else if(strcmp(tab[1],"protections")==0){
					printProtections(tabProtection);
				}
				else if(strcmp(tab[1],"cares")==0){
					printSoins(tabSoin);
				}
				else{
					printf("Argument 1 inconnu : \"show (vegetables | fruits | weapons | protections | cares)\"\n");
				}
			}
			else if(nbArgs==3){
				int val = atoi(tab[2]);
				if(val<1){
					printf("Argument 2 incorrect - la valeur doit être un entier strictement supérieur à 0\n");
				}
				else{
					if(strcmp(tab[1],"vegetable")==0){
						if(printLegume(tabChampion, val)==-1)
							printf("Aucun légume ne correspond à cet identifiant (\"show vegetables\" pour connaître la liste des légumes)\n");
					}
					else if(strcmp(tab[1],"fruit")==0){
						if(printFruit(tabChampion, val)==-1)
							printf("Aucun fruit ne correspond à cet identifiant (\"show fruits\" pour connaître la liste des fruits)\n");
					}
					else if(strcmp(tab[1],"weapon")==0){
						if(printArme(tabArme, val)==-1)
							printf("Aucune arme ne correspond à cet identifiant (\"show weapons\" pour connaître la liste des armes)\n");
					}
					else if(strcmp(tab[1],"protection")==0){
						if(printProtection(tabProtection,val)==-1)
							printf("Aucune protection ne correspond à cet identifiant (\"show protections\" pour connaître la liste des protections)\n");
					}
					else if(strcmp(tab[1],"care")==0){
						if(printSoin(tabSoin, val)==-1)
							printf("Aucune soin ne correspond à cet identifiant (\"show cares\" pour connaître la liste des soins)\n");
					}
					else{
						printf("Argument 1 inconnu : \"show (vegetable | fruit | weapon | protection | care) i\"\n");
					}
				}
			}
			else{
				printf("Commande invalide : la commande \"show\" (sans argument) ne peut être effectuée que lors d'un combat\n");
			}
		}
		else if(strcmp(tab[0],"fight")==0){
			if(nbArgs==4){
				if(strcmp(tab[2],"versus")==0){
					int fruit, legume;
					int i, trouveLegume=0;
					for(i=0;i<NB_CHAMPIONS;i++){
						if(estLegume(tabChampion[i]) && strcmp(tabChampion[i]->variete,tab[1])==0){
							trouveLegume=1;
							legume = i;
							break;
						}
					}
					if(trouveLegume==1){
						int trouveFruit=0;
						for(i=0;i<NB_CHAMPIONS;i++){
							if(estFruit(tabChampion[i]) && strcmp(tabChampion[i]->variete,tab[3])==0){
								trouveFruit=1;
								fruit = i;
								break;
							}
						}
						if(trouveFruit==1){
							int armeJ1, armeJ2, protectionJ1, protectionJ2, soinJ1, soinJ2, nbCAacheter;
							int choix, affiche;
							*combatEnCours = 1;
							initPos(duel,5,largeurTerminal-6);
							
							/* tout les trucs J1 */
							choix = choisirPersonnage(duel, tabChampion[legume], 1);
							if(choix == -2){
								printf("Les CE des Légumes ne sont pas assez élevés pour prendre %s et une arme\n", tabChampion[legume]->variete);
								*combatEnCours = 0;
								return 0;
							}
							clear();
							printf("CE restants : %d\n", duel->cEJ1);
							choix=-1;
							affiche = 0;
							while(choix == -1){
								armeJ1 = afficheChoixArme(tabArme,affiche);
								choix = choisirArme(duel, tabArme[armeJ1], 1);
								if(choix == -1){
									printf("CE insuffisants\n");
									affiche=1;
								}
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ1);
							choix=-1;
							affiche = 0;
							while(choix == -1){
								protectionJ1 = afficheChoixProtection(tabProtection,affiche);
								if(protectionJ1 != -1){
									choix = choisirProtection(duel, tabProtection[protectionJ1], 1);
									if(choix == -1){
										printf("CE insuffisants\n");
										affiche=1;
									}
								}
								else{
									choix = 0;
								}
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ1);
							choix=-1;
							affiche = 0;
							while(choix == -1){
								soinJ1 = afficheChoixSoin(tabSoin,affiche);
								if(soinJ1 != -1){
									choix = choisirSoin(duel, tabSoin[soinJ1], 1);
									if(choix == -1){
										printf("CE insuffisants\n");
										affiche=1;
									}
								}
								else{
									choix = 0;
								}
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ1);
							choix=-1;
							affiche = 0;
							while(choix ==-1){
								nbCAacheter = afficheChoixAchatCA(affiche);
								choix = CEinCA(duel, nbCAacheter, 1);
								if(choix == -1){
									printf("CE insuffisants\n");
									affiche=1;
								}
							}
							
							
							
							/* tout les trucs J2 */
							choix = choisirPersonnage(duel, tabChampion[fruit], 2);
							if(choix == -2){
								printf("Les CE des Fruits ne sont pas assez élevés pour prendre %s et une arme\n", tabChampion[fruit]->variete);
								*combatEnCours = 0;
								return 0;
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ2);
							choix=-1;
							affiche = 0;
							while(choix == -1){
								armeJ2 = afficheChoixArme(tabArme,affiche);
								choix = choisirArme(duel, tabArme[armeJ2], 2);
								if(choix == -1){
									printf("CE insuffisants\n");
									affiche=1;
								}
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ2);
							choix=-1;
							affiche = 0;
							while(choix == -1){
								protectionJ2 = afficheChoixProtection(tabProtection,affiche);
								if(protectionJ2 != -1){
									choix = choisirProtection(duel, tabProtection[protectionJ2], 2);
									if(choix == -1){
										printf("CE insuffisants\n");
										affiche=1;
									}
								}
								else{
									choix = 0;
								}
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ2);
							choix=-1;
							affiche = 0;
							while(choix == -1){
								soinJ2 = afficheChoixSoin(tabSoin,affiche);
								if(soinJ2 != -1){
									choix = choisirSoin(duel, tabSoin[soinJ2], 2);
									if(choix == -1){
										printf("CE insuffisants\n");
										affiche=1;
									}
								}
								else{
									choix = 0;
								}
							}
							
							clear();
							printf("CE restants : %d\n", duel->cEJ2);
							choix=-1;
							affiche = 0;
							while(choix ==-1){
								nbCAacheter = afficheChoixAchatCA(affiche);
								choix = CEinCA(duel, nbCAacheter, 2);
								if(choix == -1){
									printf("CE insuffisants\n");
									affiche=1;
								}
							}
							*messPrec = COLOR_GREEN"Début du combat !\n\n\n"COLOR_RESET;
						}
						else{
							printf("Commande invalide : le fruit entré ne fait pas partie de la liste des fruits\n");
						}
					}
					else{
						printf("Commande invalide : le légume entré ne fait pas partie de la liste des légumes\n");
					}
				}
				else{
					printf("Commande invalide : la commande doit contenir le mot clé \"versus\" comme ici \"fight nomLegume versus nomFruit\"\n");
				}
			}
			else{
				printf("Commande invalide : la syntaxe de la commande \"fight\" est la suivante \"fight nomLegume versus nomFruit\"\n");
			}
		}
		else if(strcmp(tab[0],"move")==0 || strcmp(tab[0],"use")==0 || strcmp(tab[0],"end")==0){
			printf("Commande invalide : les commandes \"move\", \"use\" et \"end\" ne peuvent être effectuées que lors d'un combat\n");
		}
		else{
			printf("Commande invalide : nom de la commande inconnue\n");
		}
	}
	else{
		if(strcmp(tab[0],"show")==0){
			if(nbArgs==1){
				*showed = 1;
				*messPrec = "";
			}
			else{
				*messPrec = "Commande invalide : \"show\" ne requiert aucun argument durant un combat\n\n\n";
			}
		}
		else if(strcmp(tab[0],"move")==0){
			int move;
			if(nbArgs>3){
				*messPrec = "Commande invalide : \"move\" ne peut avoir que 2 arguments maximum\n\n\n";
			}
			else if(nbArgs==1){
				*messPrec = "Commande invalide : \"move\" doit contenir au moins 1 argument (\"forward\" ou \"backward\")\n\n\n";
			}
			else if(strcmp(tab[1],"forward")==0){
				if(nbArgs==3){
					int val = atoi(tab[2]);
					if(val<1){
						*messPrec = "Argument 2 incorrect - la valeur doit être un entier strictement supérieur à 0\n\n\n";
					}
					else{
						move = moveForward(duel, joueur, largeurTerminal, val);
						*messPrec = "Vous avez avancé de plusieurs cases\n\n\n";
					}
				}
				else{
					move = moveForward(duel, joueur, largeurTerminal, 1);
					*messPrec = "Vous avez avancé de 1 case\n\n\n";
				}
				if(move == -1){
					*messPrec = "Mouvement impossible - vous allez passer de l'autre coté de l'adversaire\n\n\n";
				}
				else if(move == -2){
					*messPrec = "Pas assez de CA pour avancer d'autant de cases\n\n\n";
				}
			}
			else if(strcmp(tab[1],"backward")==0){
				if(nbArgs==3){
					int val = atoi(tab[2]);
					if(val<1){
						*messPrec = "Argument 2 incorrect - la valeur doit être un entier strictement supérieur à 0\n\n\n";
					}
					else{
						move = moveBackward(duel, joueur, largeurTerminal, val);
						*messPrec = "Vous avez reculé de plusieurs cases\n\n\n";
					}
				}
				else{
					move = moveBackward(duel, joueur, largeurTerminal, 1);
					*messPrec = "Vous avez reculé de 1 case\n\n\n";
				}
				if(move == -1){
					*messPrec = "Mouvement impossible - vous allez sortir des limites du terrain\n\n\n";
				}
				else if(move == -2){
					*messPrec = "Pas assez de CA pour reculer d'autant de cases\n\n\n";
				}
			}
			else{
				*messPrec = "Argument 1 inconnu : \"move (forward | backward) i\"\n\n\n";
			}
		}
		else if(strcmp(tab[0],"use")==0){
			int use;
			if(nbArgs>3){
				*messPrec = "Commande invalide : \"use\" ne peut avoir que 2 arguments maximum\n\n\n";
			}
			else if(nbArgs==1){
				*messPrec = "Commande invalide : \"use\" doit contenir au moins 1 argument (\"weapon\", \"protection\" ou \"care\")\n\n\n";
			}
			else if(strcmp(tab[1],"weapon")==0){
				if(nbArgs==3){
					int val = atoi(tab[2]);
					if(val<1){
						*messPrec = "Argument 2 incorrect - la valeur doit être un entier strictement supérieur à 0\n\n\n";
					}
					else{
						use = useWeapon(duel, largeurTerminal, joueur, val);
						*messPrec = "Vous avez attaqué l'ennemi plusieurs fois\n\n\n";
					}
				}
				else{
					use = useWeapon(duel, largeurTerminal, joueur, 1);
					*messPrec = "Vous avez attaqué l'ennemi 1 fois\n\n\n";
				}
				if(use == -1){
					*messPrec = "Pas assez de CA pour utiliser l'arme\n\n\n";
				}
				else if(use == -2){
					*messPrec = "Vous êtes trop loin de l'ennemi pour l'attaquer avec cette arme\nVous avez tout de meme perdu les CA de l'attaque\n\n";
				}
			}
			else if(strcmp(tab[1],"protection")==0){
				if(nbArgs>2){
					*messPrec = "Commande invalide : \"use protection\" ne nécessite pas d'arguement supplémentaire\n\n\n";
				}
				else{
					use = useProtection(duel, joueur);
					*messPrec = "Vous avez équipé votre protection\n\n\n";
					if(use == -1){
						*messPrec = "La protection est déjà équipée\n\n\n";
					}
					else if(use == -2){
						*messPrec = "Pas assez de CA pour équiper la protection\n\n\n";
					}
					else if(use == -3){
						*messPrec = "Vous n'avez pas pris de protection\n\n\n";
					}
				}
			}
			else if(strcmp(tab[1],"care")==0){
				if(nbArgs==3){
					int val = atoi(tab[2]);
					if(val<1){
						*messPrec = "Argument 2 incorrect - la valeur doit être un entier strictement supérieur à 0\n\n\n";
					}
					else{
						use = useSoin(duel, joueur, val);
						*messPrec = "Vous avez utilisé le soin plusieurs fois\n\n\n";
					}
				}
				else{
					use = useSoin(duel, joueur, 1);
					*messPrec = "Vous avez utilisé le soin 1 fois\n\n\n";
				}
				if(use == -1){
					*messPrec = "Pas assez de CA pour utiliser le soin\n\n\n";
				}
				else if(use == -2){
					*messPrec = "Vous avez utilisé tout vos soins disponibles\nOu vous n'avez pas assez de soins à disposition\n\n";
				}
				else if(use == -3){
					*messPrec = "Vous avez déjà vos PV au maximum\n\n\n";
				}
			}
			else{
				*messPrec = "Argument 1 inconnu : \"use (weapon | protection | care) i\"\n\n\n";
			}
		}
		else if(strcmp(tab[0],"end")==0){
			if(nbArgs==1){
				finTour(duel, joueur);
				(*cptTourDuel)++;
				*messPrec = "Fin du tour !\nAu joueur suivant !\n\n";
			}
			else{
				*messPrec = "Commande invalide : \"end\" ne nécessite pas d'arguement\n\n\n";
			}
		}
		else if(strcmp(tab[0],"fight")==0){
			*messPrec = "Commande invalide : un combat est déjà en cours\n\n\n";
		}
		else{
			*messPrec = "Commande invalide : nom de la commande inconnue\n\n\n";
		}
		finT = (joueur == 1 && duel->cAJ1 == 0) || (joueur == 2 && duel->cAJ2 == 0);
		if(finT){
			finTour(duel, joueur);
			(*cptTourDuel)++;
			*messPrec = "Fin du tour ! (aucun CA restant)\nAu joueur suivant !\n\n";
		}
		if(winDuel(duel, joueur)){
			(*winDudu)=1;
			duel->protectionActiveJ1 = 0;
			duel->protectionActiveJ2 = 0;
			duel->vieJ1 = 1;
			duel->vieJ2 = 1;
			if(joueur == 1){
				duel->cEequipeJ1 += 5*max((duel->cEuseJ1-duel->cEuseJ2), 1);
			}
			else if(joueur == 2){
				duel->cEequipeJ2 += 5*max((duel->cEuseJ2-duel->cEuseJ2), 1);
			}
		}
	}
	
	return 0;
}

int main(){
	int nbChampion = 12;
	Champion **tabChampion = creerTableauChampion();
	int nbArme = 5;
	Arme **tabArme = creerTableauArme();
	int nbProtection = 4;
	Protection **tabProtection = creerTableauProtection();
	int nbSoin = 3;
	Soin **tabSoin = creerTableauSoin();
    struct winsize w;
    int i;
	int cptTourDuel=0;
	int fin = 0;
	int *combatEnCours = (int*) malloc(sizeof(int));
	int *showed = (int*) malloc(sizeof(int));
	int *winDudu = (int*) malloc(sizeof(int));
	char *messagePrec[1] = {"\n\n\n"};
	
	char *tabAffLegume[5] = {"\033[0;42m  \033[0m  \033[0;42m  \033[0m", "\033[0;42m  \033[0m  \033[0;42m  \033[0m", "  \033[0;42m  \033[0m  ", "  \033[0;42m  \033[0m  ", "  \033[0;47m  \033[0m  "};
	char *tabAffFruit[5] = {"\033[0;42m  \033[0m  \033[0;42m  \033[0m", " \033[0;43m    \033[0m ", "\033[0;43m      \033[0m", "\033[0;43m      \033[0m", " \033[0;43m    \033[0m "};
	
	Duel *duel = (Duel *) malloc(sizeof(Duel));
	duel->championJ1 = (InitChampion *) malloc(sizeof(InitChampion));
	duel->championJ2 = (InitChampion *) malloc(sizeof(InitChampion));
	duel->cEequipeJ1 = 20;
	duel->cEequipeJ2 = 1000;
	duel->protectionActiveJ1 = 0;
	duel->protectionActiveJ2 = 0;
	*showed = 0;
	*winDudu = 0;
	*combatEnCours = 0;
    ioctl(0, TIOCGWINSZ, &w);
    
    initPos(duel,5,w.ws_col-6);
	
	clear();
	printf("Nombre CE Légumes : %d | Nombre CE Fruits : %d\n",duel->cEequipeJ1,duel->cEequipeJ2);
	
	while(!fin){
		fin = gestionCommandes(tabChampion, tabProtection, tabSoin, tabArme, combatEnCours, duel, &cptTourDuel, w.ws_col, w.ws_row, tabAffLegume, tabAffFruit, messagePrec, showed, winDudu);
	}
	
	for (i=0;i<nbChampion;i++){
		free(tabChampion[i]);
	}
	free(tabChampion);
	
	for (i=0;i<nbArme;i++){
		free(tabArme[i]);
	}
	free(tabArme);
	
	for (i=0;i<nbProtection;i++){
		free(tabProtection[i]);
	}
	free(tabProtection);
	
	for (i=0;i<nbSoin;i++){
		free(tabSoin[i]);
	}
	free(tabSoin);
	
	free(duel->championJ1);
	free(duel->championJ2);
	free(duel);
	free(combatEnCours);
	free(showed);
	free(winDudu);
	

	return 0;
}
