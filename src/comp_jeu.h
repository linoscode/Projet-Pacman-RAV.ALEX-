#ifndef COMP_JEU_H
#define COMP_JEU_H

#include <stdio.h>
#include "./partie.h"
#include "../lib/libgraphique.h"

/* Change la position de pacman dans le tableau 'plateau' et
 * retourne les coordonnées tableau de pacman.               */
Pos deplacer_pacman_plateau(Partie p, char ** plateau, int direction);

/* Retranscris le déplacement de pacman sur la fenêtre graphique */
Pos deplacer_pacman_visuel(Partie p, char ** plateau,int direction, int taille);


int nbpacgommes(Partie p);

/* Gère les déplacements des fantomes en fonction de la pos de
 * pacman (comme le monstre). Fonctionne avec 1 seul fantôme pour
 * l'instant                                                     */
Pos deplacer_fantome(Partie p, char **plateau);

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

/* idem mais pour les rectangles car renvoie le COIN. */
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

#endif
