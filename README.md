______________________________________________________________________________________________________________________________________________________________________________
PROJET PACMAN 
-Alexandre PAPAVASILEIOU
-Ravaka RALAMBOARIVONY
INF1-A2
______________________________________________________________________________________________________________________________________________________________________________

TRAVAIL ACCOMPLI :
	Organisation des fichiers :
		-Comp_jeu.c = définition de toutes les fonctions utilisées.
		-comp_jeu.h = prototypes et explication de ces fonctions.
		-main.c = Algorithme de jeu. (les fonctions sont appelées ici)
		-main.h = inclut les librairies utiles.
		-partie.c = le même que dans l'archive. 
			Aucune modification apportée.
		-partie.h = le même que dans l'archive. 
			Aucune modification apportée. 
	
	Fonctions :
		-deplacer_pacman_plateau() 
		-deplacer_pacman_visuel()
		-deplacer_fantome(), algo naïf (comme le monstre)
		-afficher_plan().
		-dessiner_plateau().
		-fonction pos2point() / pos2centre().
		-demarrage().
	

PROBLEMES RENCONTRES :
	- Algorithme du plus court chemin :

BUGS CONNUS :
	- Plateau affiché en miniature, sur un espace de la taille indiquée
	dans le fichier test.txt (27x21) dans le coin supérieur gauche.
	Oubli de calculer la taille dans les fonctions pos2point, pos2centre.
	Corrigé.
	
	-Déplacement pacman, non prise en compte des murs. Corrigé.
	
IDEES ORIGINALES :
	- Affichage de présentation au démarrage 
	- Utiliser l'algorithme de plus court chemin pour le déplacement
	des fantômes plutôt que l'algo naïf
	

