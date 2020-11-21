______________________________________________________________________________________________________________________________________________________________________
PROJET PACMAN 
-Alexandre PAPAVASILEIOU
-Ravaka RALAMBOARIVONY
INF1-A2
______________________________________________________________________________________________________________________________________________________________________

TRAVAIL ACCOMPLI :
	Organisation des fichiers :
		-Comp_jeu.c = définition de toutes les fonctions utilisées.
		-comp_jeu.h = prototypes et explication de ces fonctions.
		-main.c = Algorithme de jeu. (les fonctions sont appelées ici)
		-main.h = inclut les librairies utiles.
		-partie.c = le même que dans l'archive. 
			Aucune modification apportée.
		-partie.h = le même que dans l'archive. 
			Ajout de 2 champs pour la direction à prendre des fantômes. 
	Fonctions :
		-deplacer_pacman_plateau() 
		-deplacer_pacman_visuel()
		-deplacer_fantome_plateau(), algo naïf (comme le monstre)
		-afficher_plan().
		-dessiner_plateau().
		-pos2point() / pos2centre().
		-demarrage().
		-plus_court_chemin(), pour le déplacement des fantômes.
		-distance(), facilite plus_court_chemin.
	

PROBLEMES RENCONTRES :
	- Algorithme du plus court chemin :

BUGS CONNUS :
	- Plateau affiché en miniature, sur un espace de la taille indiquée
	dans le fichier test.txt (27x21) dans le coin supérieur gauche.
	Oubli de calculer la taille dans les fonctions pos2point, pos2centre.
	Corrigé.
	- Déplacement pacman, non prise en compte des murs. 
	Corrigé.
	
IDEES ORIGINALES :
	- Affichage de présentation au démarrage 
	- Utiliser l'algorithme de plus court chemin pour le déplacement
	des fantômes plutôt que l'algo naïf
	-Déplacement des fantômes en temps réel.
	-Afficher les commandes à droite du plateau.
	-Afficher le niveau actuel à droite du plateau.
	

