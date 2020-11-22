/******************************************************************************/
/* CHARGEMENT.h                                                               */
/******************************************************************************/
#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include <stdio.h>
#include <stdlib.h>

#define NBFANTOMES  4 // nombres de fantômes dans les plateaux chargés

// STRUCTURES
/* Structure Pos: permet de stocker un couple ligne/colonne                   */
typedef struct pos {
    int     l;
    int     c;
    } Pos;

/* Structure Partie:  permet de stocker les paramètres d'une partie           */
typedef struct partie {
    char ** plateau; // le tableau de caractères contenant le plateau de jeu
    int     L; // le nb de lignes du plateau de jeu
    int     C; // le nb de colonne du plateau de jeu
    Pos     pacman; // la position de Pacman dans le plateau
    Pos     fantomes[NBFANTOMES];//position du fantome
    int     isMange[NBFANTOMES];//variable pour savoir si le fantome a été mangé
    Pos     target[NBFANTOMES];//cible du fantome
    Pos     dir_fant[NBFANTOMES];//vecteur de direction du fantome
    Pos     dir_prec[NBFANTOMES];//précédent vecteur de direction du fantome
    Pos     dir_pos[NBFANTOMES][4]; // direction précédente des fantomes
    int     nbbonus; // les positions de chaque fantôme
    int     gameov; //Etat du jeu : game over ou pas ?
    int     tours_bonus; //Nombre tour restant en mode bonus
    int     nbpacgommes; // le nombre de bonus restants à manger
    // ...et vous pouvez ajouter tout ce dont vous avez besoin
    } Partie;

// PROTOTYPES
/* charge_plan : lit un fichier contenant un plateau de jeu et le charge
                    en mémoire, dans le champ 'plateau' d'une Partie */
Partie charge_plan(char *fichier);

#endif
