#ifndef COMP_JEU_H
#define COMP_JEU_H

#include <stdio.h>
#include "./partie.h"
#include "../lib/libgraphique.h"

/* Change la position de pacman dans le tableau 'plateau' et
 * retourne les coordonnées tableau de pacman.               */
Pos deplacer_pacman_plateau(Partie p, char ** plateau, int direction);

/* Retranscris le déplacement de pacman sur la fenêtre graphique */
Pos deplacer_pacman_visuel(Partie p, char ** plateau,int direction);


int nbpacgommes(Partie p);

/* Gère les déplacements des fantomes en fonction de la pos de
 * pacman (comme le monstre pour l'instant                      */
Pos deplacer_fantome_plateau(Partie p, char **plateau);

/* Fonction déterminant la case voisine la plus proche de la cible.
 * Exemple d'utilisation : la source est 1fantôme, la cible est Pacman.
 * La fonction renvoie la case voisine la plus proche de pacman,
 * on se déplace sur cette case. */
int plus_court_chemin(Pos source, Pos cible,int i_fant,int dir_pos[][4]);

/* Calcule la distance à vol d'oiseau entre 2 positions */
int distance(Pos p1,Pos p2);

/* Détermine les directions empruntables par le fantome */
void direction_possibles(Partie p,int i_fant, int dir_prec, int dir_pos[][4]);

/* Permet de débuguer */
void afficher_plan(Partie p);

/* Affiche PACMAN en grand au démarrage   */
void demarrage(void);

/* Repère les caractères dans le tableau 'plateau' et dessine
 * les murs, les fantomes, les points, ... graphiquement.     */
void dessiner_plateau(Partie p, char **plateau);

/*On donne les coordonnées plateau d'un dessin (sauf rectangles)
 * et nous renvoie les coordonnées grapiques.
 * Facilite dessiner_plateau                                    */
Point pos2point(Pos p, int taille);

/* idem mais pour les rectangles, renvoie le centre. */
Point pos2centre(Pos p, int taille);

//Définition des directions
#define haut 0
#define droite 1
#define bas 2
#define gauche 3

//Pour l'affichage
#define FREQ 10
#define LONG 800
#define LARG 600

//Pour les tailles
#define TPACMAN  5  //rayon pacman
#define TFANTOME 10  //taille fantomes
#define CASE 20

//Pour les calculs de distances
#define DLIGNES dist_ligne*dist_ligne
#define DCOLONNES dist_colonne*dist_colonne
#endif
