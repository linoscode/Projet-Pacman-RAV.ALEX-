#ifndef COMP_JEU_H
#define COMP_JEU_H

#include <stdio.h>
#include "./partie.h"
#include "../libgraphique.h"

Pos deplacer_pacman_plateau(Partie p, char **plateau, int direction);
int nbpacgommes(Partie p);
void afficher_plan(Partie p);

#define haut 0
#define droite 1
#define bas 2
#define gauche 3

#endif
