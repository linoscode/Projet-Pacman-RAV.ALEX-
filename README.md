______________________________________________________________________________________________________________________________________________________________________
PROJET PACMAN
-Alexandre PAPAVASILEIOU
-Ravaka RALAMBOARIVONY
INF1-A2
______________________________________________________________________________________________________________________________________________________________________

LANCEMENT DU JEU :
	1- Se rendre dans la racine du dossier du projet et faire un make.
	2- Rajouter des droits d'éxecution pour pacman.sh avec : chmod +x pacman.sh
	3- Puis executer pacman.sh. 

TRAVAIL ACCOMPLI :
	Organisation des fichiers :
		-Comp_jeu.c = définition de toutes les fonctions utilisées.
		-comp_jeu.h = prototypes et explication de ces fonctions.
		-main.c = Algorithme de jeu. (les fonctions sont appelées ici)
		Le chargement des niveaux 3 niveaux se succède à l'aide d'une
		boucle.
		-main.h = inclut les librairies utiles.
		-partie.c = le même que dans l'archive.
			Aucune modification apportée.
		-partie.h = le même que dans l'archive.
			Ajout de champs.

	Fonctions (toutes décrites dans comp_jeu.h):
		-int demarrer_partie();
		-Pos deplacer_pacman_plateau();
		-Pos deplacements_visuels();
		-int nbpacgommes();
		-void deplacer_fantome_plateau();
		-Pos touche2pos();
		-Pos target_oppose();
		-Pos target_devant_pacman();
		-Pos target_pacman();
		-int rafraichir();
		-int isbonus();
		-Partie deplacer_fantome();
		-Pos plus_court_chemin();
		-int distance();
		-int areEqual();
		-Pos opposite();
		-void directions_possibles();
		-void afficher_plan();
		-void demarrage();
		-void dessiner_plateau();
		-Point pos2point();
		-Point pos2centre();
		-int game_over();

	Bilan : Jeu en temps réel, chaque fantôme a son comportement.
			Le chargement des niveaux se fait automatiquement une
			fois que tous les pacgommes ont été mangés. Les bonus
			font que les fantômes deviennent bleus, ne peuvent plus
			manger pacman et ciblent des cases aléatoires.


PROBLEMES RENCONTRES :
	- Plateau s'affichait en miniature en haut à gauche.
	- Fantômes mangeaient les bonus.
	- Fantomes mangeaient les murs.
	- Fantômes se téléportaient.
	- Fantomes passaient par le tunnel puis sortaient du plateau.
	- Affichage fantôme bug.

BUGS CONNUS :
	- Bug visuel : lorsqu'un fantôme passe dans un tunnel, un carré
	rose reste à l'entrée de celui-ci.
	- Très occasionnellement les fantômes traversent pacman sans
	provoquer de game over.
	- Avec un excellent timing, on peut traverser les fantômes en changeant de direction.

IDEES ORIGINALES :
	- Affichage de présentation au démarrage.
	- Utilisation d'un algo de plus court chemin.
	- Déplacement des fantômes en temps réel.
	- Chaque fantôme a son comportement :
		- 1 poursuit directement pacman
		- 1 poursuit directement pacman mais s'enfui lorsqu'il se trouve à moins de
		8 blocks de pacman.
		- 1 ciblent 2 cases devant pacman
		- 1 cible le point étant le symétrique d'un fantôme par
		rapport à pacman.
