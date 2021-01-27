# Labyrinthe - README

:walking: Membres : Pierre-Louis Bouchez, Benoît Brebion, Gwonaël Clarebout, Bastien Laffon, Anthony Pereira

***
#### :heavy_check_mark: Fonctionnalités implantées :
- Interface du jeu en JavaFX
- Menu principal (avec choix du nombre de joueurs, de la difficulté des IA, etc...)
- Génération aléatoire du plateau (cases et trésors)
- Génération aléatoire des trésors à récupérer
- Placement d'une case sur le plateau
- Déplacement du joueur sur les cases qui lui sont uniquement accessibles
- Récupération des trésors / fin de partie
- IA avec différentes stratégies
- Variante "Trésors Vivants"
- Choix du thème du jeu

***
#### :x: Fonctionnalités non implantées :
- Variante "Bonus/Malus"

***
#### :books: Guide d'utilisation :
- Génération et exécution du jar avec "./runfx" ("./runfx clean" pour supprimer le jar, exécuter le "build.bat" si vous êtes sous Windows)
- Vous pouvez choisir la difficulté, le nombre de joueurs, le thème et l'activation ou non de la variante sur le menu principal (4 joueurs humains par défaut)
- Start lance le jeu avec les différents choix effectués précédemment
- Le plateau est affiché au milieu de l'écran. En bas en partant de la gauche, vous avez : votre nombre de trésors restants à récupérer (sous forme de cartes face cachée), votre trésor à récupérer actuellement, la case que vous devez insérer, 2 boutons pour insérer la case et finir votre tour, et enfin la couleur du joueur donc c'est le tour de jouer
- Vous pouvez appuyer sur le "?" en haut à droite pour afficher différentes informations sur le jeu
- Lorsque c'est votre tour vous devez insérer la case que vous avez en main sur l'une des 12 flèches jaunes situées sur le bord du plateau. Vous pouvez tourner cette case dans le sens souhaité en cliquant sur la case en bas. Vous pouvez ensuite appuyer sur le bouton pour insérer la case
- Une fois la case insérée, vous pouvez déplacer votre joueur en cliquant à l'endroit où vous voulez aller (dans la limite des cases accessibles), puis cliquer sur le bouton pour finir votre tour. Si vous vous déplacez sur la case contenant votre trésor actuel, votre tour sera automatiquement terminé.
- Lorsque vous avez ramassé tout vos trésors, vous devrez vous rendre sur votre case départ (symbolisée par votre couleur) pour terminer la partie
- Vous pouvez cliquer sur le bouton en haut à gauche pour revenir au menu principal ou quitter le jeu (à n'importe quel moment de la partie)
- Les IA jouent automatiquement
- Vous pouvez rajouter un thème de jeu en ajoutant un dossier (dans le dossier /img/) contenant les images de votre thème (respecter le nom des images). Vous devez relancer le jeu pour pouvoir utiliser le thème

***
#### :clipboard: Diagramme de classes :
![Diagramme](https://gitlab.univ-artois.fr/pierre-louis_bouchez/labyrinthe/uploads/d762d77a283cde7427d5352976ac0e6e/DiagrammeFinal.png)
