#ifndef COMP_JEU_H
#define COMP_JEU_H

#include <stdio.h>
#include "./partie.h"
#include "../lib/libgraphique.h"


/******************************************/
/* Fonctions visuels et de démarrage      */
/******************************************/
/*Regroupe toutes les fonctions et démarre le jeu */
int demarrer_partie(Partie p );

/* Affiche PACMAN en grand au démarrage   */
void demarrage(void);


/* Retranscris le déplacement de pacman sur la fenêtre graphique */
Pos deplacements_visuels(Partie p, char ** plateau,Pos direction);


/******************************************/
/* Fonctions modélisant les règles du jeu */
/******************************************/

/* Compte le nombre de pacgommes (=Partie nbbonus) restant sur le plateau */
int nbpacgommes(Partie p);

/* Gère les déplacements des fantomes en fonction de la direction choisie */
void deplacer_fantome_plateau(Partie p,Pos fantomes[], int i_fant, Pos direction);

/* Change la position de pacman dans le tableau 'plateau' et
 * retourne les coordonnées tableau de pacman.               */
Pos deplacer_pacman_plateau(Partie p, char ** plateau, Pos direction);

/*Récupère la dernière touche pressée */
int evenement_touche();

/*Permet de cibler la case qui est à l'opposé d'un autre fantome*/
Pos target_oppose(Partie p, Pos dir,int i_fant);

/* Permet de définir la cible comme 2 cases devant la case où se trouve pacman */
Pos target_devant_pacman(Partie p, Pos dir);

/* Permet de définir la cible comme la case ou se trouve pacman */
Pos target_pacman(Partie p);

/*Modélise la cible et le comportement de Clyde*/
Pos target_pacman_clyde(Partie p,int i_fant);

/*Définie les cibles des fantomes aléatoirement */
void deplacements_aleatoire(Partie p,Pos *target);

/*Vérifie si un des fantomes a été mangé */
void estMange(Partie p, int *isMange);

/*Assigne toutes les targets qui modélise le comportement
de chaque fantome*/
void modeChasse(Partie p,Pos * target, Pos dir_pacman);

/*Permet de réafficher tous les bonus et pacgommes et compte le nombre de ceux-ci*/
int rafraichir(Partie p);

/*Permet de vérifier si la case sur laquelle pacman va se déplacer est un bonus*/
int isbonus(Partie p, Pos dir);

/*Permet de déplacer tous les fantomes*/
Partie deplacer_fantome(Partie p);

/* Fonction déterminant la case voisine la plus proche de la cible.
 * Exemple d'utilisation : la source est 1fantôme, la cible est Pacman.
 * La fonction renvoie la case voisine la plus proche de pacman,
 * on se déplace sur cette case. */

Pos plus_court_chemin(Pos source, Pos cible,int i_fant,Pos dir_pos[][4], Pos dir_prec[]);



/* Détermine les directions empruntables par le fantome */
void direction_possibles(Partie p,int i_fant, Pos dir_prec[], Pos dir_pos[][4]);

/* Permet de débuguer */
void afficher_plan(Partie p);



/* Repère les caractères dans le tableau 'plateau' et dessine
 * les murs, les fantomes, les points, ... graphiquement.     */
void dessiner_plateau(Partie p, char **plateau);

/*On donne les coordonnées plateau d'un dessin (sauf rectangles)
 * et nous renvoie les coordonnées grapiques.
 * Facilite dessiner_plateau                                    */

 /******************************************/
 /* Fonctions de calculs                   */
 /******************************************/
/* Position du coin haut gauche de la case sur la fenetre*/
Point pos2point(Pos p, int taille);

/* Position du centre de la case*/
Point pos2centre(Pos p, int taille);

/* position du coin haut gauche des carré représentants les fantomes*/
Point pos2coin(Pos p,int taille);

/* Vérifie si la partie est perdue */
int game_over(Partie p);

/* Calcule la distance à vol d'oiseau entre 2 positions */
int distance(Pos p1,Pos p2);

/* Vérifie si les positions sont égales */
int areEqual(Pos p1, Pos p2);

/*Calcul le vecteur opposé*/
Pos opposite(Pos d);

/*récupère le vecteur direction correspondant à chaque touche directionnelle */
Pos touche2pos(int touche);

/*Permet de récupérer l'indice du tableau dir_pos qui correspond
à une directions une direction donnée*/
int i2dir(Pos dir);

/******************************************/
/* Fonctions de déboggage                 */
/******************************************/
void afficher_plan(Partie p);


//Pour l'affichage
#define FREQ 8
#define LONG 800
#define LARG 600

//Pour les tailles
#define TPACMAN  5  //rayon pacman
#define TFANTOME 10 //taille fantomes
#define CASE 20     //taille des cases

//Pour les calculs de distances
#define DLIGNES dist_ligne*dist_ligne
#define DCOLONNES dist_colonne*dist_colonne
#endif
