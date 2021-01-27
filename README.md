# Projet P-WEB Siam
Binôme : Benoît Brebion & Anthony Pereira

### Choix Techniques
- Les différentes actions de jeu sont récupérées via formulaires, puis les infos sont transmises à la partie orientée objet qui gère toute la partie jeu (insertion, déplacement etc...)
- La BDD n'est mise à jour qu'à la fin de chaque tour de jeu
- Utilisation des sessions pour conserver les informations à chaque réactualisation de la page
- Utilisation de Bootstrap pour un meilleur rendu front du jeu

### Architecture Choisie
- Gestion du Front : HTML, CSS, Bootstrap, PHP
- Gestion du Back : Formulaires PHP, Sessions PHP, Orienté Objet PHP
- BDD : SQLite3

### Schéma de la Base de Données
- Table utilisateurs : id | pseudo | mot_de_passe
- Table parties : id | nom | createur | joueur1 | joueur2 | tour | jeu

Le mot de passe est crypté. "jeu" contient toute la partie orientée objet du jeu et du plateau.

### Infos diverses :
- "authentification.php" est la première page du site (redirection automatique vers celle-ci si non connecté)
- L'admin peut rejoindre une partie avec une place libre (et être donc considéré comme un joueur de la partie), l'admin a également accès à toutes les autres parties en cours où il n'est pas joueur. Dans tout les cas, l'admin peut jouer à la place de n'importe qui.
- La BDD contient déjà 3 utilisateurs :
    - (Pseudo) / (Mot de Passe) :
    - admin / admin
    - test / test
    - player / player