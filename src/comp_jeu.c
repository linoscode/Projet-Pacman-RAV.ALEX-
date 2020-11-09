#include "./comp_jeu.h"

#define haut 0
#define droite 1
#define bas 2
#define gauche 3


Pos deplacer_pacman(Partie p,char **plateau,int direction) {
	plateau[p.pacman.l][p.pacman.c]=' ';//On efface pacman de son ancien emplacement
	//On dessine pacman dans la direction donné
	if(direction==haut && plateau[p.pacman.l-1][p.pacman.c]!='*') {
		p.pacman.l--;
		plateau[p.pacman.l][p.pacman.c]='P';
		return p.pacman;
	} else if (direction==droite && plateau[p.pacman.l][p.pacman.c+1]!='*') {
		p.pacman.c++;
		plateau[p.pacman.l][p.pacman.c]='P';
		return p.pacman;
	} else if (direction==bas && plateau[p.pacman.l+1][p.pacman.c]!='*') {
		p.pacman.l++;
		plateau[p.pacman.l][p.pacman.c]='P';
		return p.pacman;
	} else if (direction==gauche && plateau[p.pacman.l][p.pacman.c-1]!='*') {
		p.pacman.c--;
		plateau[p.pacman.l][p.pacman.c]='P';
		return p.pacman;
	}
}


//Pour debuguer
void afficher_plan(Partie p) {
	for(int i=0; i<p.L;i++) {
		for(int j=0;j<p.C;j++) {
		       printf("%c", p.plateau[i][j]);
		}
	printf("\n");
 	}		
}

