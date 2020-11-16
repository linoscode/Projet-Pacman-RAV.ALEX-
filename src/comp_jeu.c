#include "./comp_jeu.h"

Pos deplacer_pacman_visuel(Partie p, char **plateau, int direction, int taille) {
	Point pacman;
	Point pacman_cible;
	printf("( %d , %d ) \n", p.pacman.c, p.pacman.l);
	pacman.x = p.pacman.c*taille - p.pacman.c%taille;
	pacman.y = p.pacman.l*taille - p.pacman.l%taille;
	p.pacman = deplacer_pacman_plateau(p,plateau,direction);
	printf("( %d , %d ) \n", p.pacman.c, p.pacman.l);
	pacman_cible.x = p.pacman.c*taille - p.pacman.c%taille;
	pacman_cible.y = p.pacman.l*taille - p.pacman.l%taille;

	if(direction == haut || direction == bas)
	{
		while(pacman.y != pacman_cible.y)
		{
			dessiner_disque(pacman, taille, noir);
			pacman.y += (direction == haut) ? -1 : 1;
			dessiner_disque(pacman, taille, jaune);
			actualiser();
			attente(FREQ);
		}
	}

	if(direction == gauche || direction == droite)
	{
		while(pacman.x != pacman_cible.x)
		{
			dessiner_disque(pacman, taille, noir);
			pacman.x += (direction == droite) ? 1 : -1;
			if (pacman.x < 0) {
				pacman.x = p.C*taille - p.C%taille;
			}
			if (pacman.x > p.C*taille - p.C%taille ) {
				pacman.x = 0;
			}
			dessiner_disque(pacman, taille, jaune);
			actualiser();
			attente(FREQ);
		}
	}
	return p.pacman;
}


Pos deplacer_pacman_plateau(Partie p,char **plateau,int direction) {
  //On efface pacman de son ancien emplacement
	//On dessine pacman dans la direction donné
	if(direction==haut && plateau[p.pacman.l-1][p.pacman.c]!='*')
	{
		plateau[p.pacman.l][p.pacman.c]=' ';
		p.pacman.l--;
		plateau[p.pacman.l][p.pacman.c]='P';
		return p.pacman;
	}

	else if (direction==droite && p.plateau[p.pacman.l][p.pacman.c+1]!='*')
	{
		plateau[p.pacman.l][p.pacman.c]=' ';
		if(p.pacman.c==p.C-1)
		{
			p.pacman.c=0;
			plateau[p.pacman.l][p.pacman.c]='P';
		}
		else {
			p.pacman.c++;
			plateau[p.pacman.l][p.pacman.c]='P';
		}
		return p.pacman;
	}

	else if (direction==bas && plateau[p.pacman.l+1][p.pacman.c]!='*')
	{
		plateau[p.pacman.l][p.pacman.c]=' ';
		p.pacman.l++;
		plateau[p.pacman.l][p.pacman.c]='P';
		return p.pacman;
	}

	else if (direction==gauche && plateau[p.pacman.l][p.pacman.c-1]!='*')
	{
		plateau[p.pacman.l][p.pacman.c]=' ';
		if(p.pacman.c==0)
		{
			p.pacman.c=p.C-1;
			plateau[p.pacman.l][p.pacman.c]='P';
		}
		else {
			p.pacman.c--;
			plateau[p.pacman.l][p.pacman.c]='P';
		}
		return p.pacman;
	}

	return p.pacman;

}

int nbpacgommes(Partie p) {
	for(int i=0; i<p.L;i++)
	{
		for(int j=0;j<p.C;j++)
		{
			if(p.plateau[i][j]=='.')
			{
				p.nbpacgommes++;
			}
		}
	}
	return p.nbpacgommes;
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
