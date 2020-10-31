#ifndef COMP_JEU_H
#define COMP_JEU_H

#include <stdio.h>
#include "./partie.h"

Pos deplacer_pacman(Partie p, char **plateau, int direction);

void afficher_plan(Partie p);

#endif
