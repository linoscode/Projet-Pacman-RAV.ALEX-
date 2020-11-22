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
    Pos     fantomes[NBFANTOMES];
    Pos     target[NBFANTOMES];
    Pos     dir_fant[NBFANTOMES];
    Pos     dir_prec[NBFANTOMES];
    Pos     dir_pos[NBFANTOMES][4]; // direction précédente des fantomes
    int     nbbonus; // les positions de chaque fantôme
    int     gameov;
    int     tours_bonus;
    int     nbpacgommes; // le nombre de bonus restants à manger
    // ...et vous pouvez ajouter tout ce dont vous avez besoin
    } Partie;

// PROTOTYPES
/* charge_plan : lit un fichier contenant un plateau de jeu et le charge
                    en mémoire, dans le champ 'plateau' d'une Partie */
Partie charge_plan(char *fichier);

#endif
