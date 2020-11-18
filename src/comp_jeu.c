#include "./comp_jeu.h"

/***********************************/
/* Fonctions visuelles             */
/***********************************/
void demarrage(void)
{
    Point coin = {0,0} ;
    dessiner_rectangle(coin, LONG, LARG, blanc) ;
    coin.x = LONG/5;
    coin.y = LARG/2 ;
    afficher_texte("PACMAN", 70, coin, bleu);
    coin.x -= 20;
    coin.y -= 10;
    afficher_texte("Ravaka RALAMBOARIVONY et Alexandre PAPAVASILEIOU",
                    20, coin, rouge);
    actualiser();
    attente(1500);
    coin.x = 0;
    coin.y = 0;
    dessiner_rectangle(coin, LONG, LARG, noir) ;
}

Pos deplacer_pacman_visuel(Partie p, char **plateau, int direction, int taille) {

	Point pacman;
	Point pacman_cible;

	printf("( %d , %d ) \n", p.pacman.c, p.pacman.l);
	//à remplacer par pos2coin
	pacman = pos2centre(p.pacman,CASE);// - p.pacman.l%taille;

	p.pacman = deplacer_pacman_plateau(p,plateau,direction);
	printf("( %d , %d ) \n", p.pacman.c, p.pacman.l);
	//à remplacer par pos2coin
	pacman_cible = pos2centre(p.pacman,CASE);

	if(direction == haut || direction == bas)
	{
		//On déplace pacman tant qu'il n'a pas atteint les coordonnées de la case suivante
		while(pacman.y != pacman_cible.y)
		{
			dessiner_disque(pacman, TPACMAN, noir);
			//Utilise selon le vecteur (0;-1) ou (0;1) selon la direction choisie.
			pacman.y += (direction == haut) ? -1 : 1;
			dessiner_disque(pacman, TPACMAN, jaune);
			actualiser();
			//On attend la fréquence
			attente(FREQ);
		}
	}

	if(direction == gauche || direction == droite)
	{
		while(pacman.x != pacman_cible.x)
		{
			dessiner_disque(pacman, TPACMAN, noir);
			//Utilise selon le vecteur (1;0) ou (-1;0) selon la direction choisie.
			pacman.x += (direction == droite) ? 1 : -1;
			if (pacman.x < 0)
			{
				pacman.x = p.C*taille - p.C%taille;
			}
			if (pacman.x > p.C*taille - p.C%taille )
			{
				pacman.x = 0;
			}
			dessiner_disque(pacman, TPACMAN, jaune);
			actualiser();
			attente(FREQ);
		}
	}
	return p.pacman;
}

void dessiner_plateau(Partie p, char **plateau)
{
    for(int i=0 ; i< p.L ; i++)
        for(int j=0 ; j< p.C ; j++)
        {
            if (p.plateau[i][j] == '*') // MUR = RECTANGLE BLEU
            {
                Pos mur = {i, j} ;
                dessiner_rectangle(pos2point(mur, CASE), CASE, CASE, bleu);
            }

            else if (p.plateau[i][j] == '.') // GUM = POINT BLANC
            {
                Pos gum = {i, j};
                changer_pixel(pos2centre(gum,CASE), blanc);
            }

            else if (p.plateau[i][j] == 'P') // PACMAN == DISQUE JAUNE
            {
                Pos pacman = {i, j};
                dessiner_disque(pos2centre(pacman,CASE), TPACMAN, jaune);
            }

            else if (p.plateau[i][j] == 'F') // à voir si on supprime, FANTOME = RECTANGLE ROSE
            {
                Pos fantome = {i, j};
                dessiner_rectangle(pos2point(fantome, CASE), TFANTOME, TFANTOME, pink);
            }

            else if (p.plateau[i][j] == 'B') // BONUS = DISQUE ROUGE
            {
                Pos bonus = {i, j};
                dessiner_disque(pos2centre(bonus,CASE), TPACMAN, rouge);
            }
        }
}

/******************************************/
/* Fonctions modélisant les règles du jeu */
/******************************************/


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
		//Si pacman sort du plateau on le ramène de l'autre côté
		//permet de créer des tunnels en laissant des trous vers l'extérieur du plateau
		if(p.pacman.c==p.C-1)
		{
			p.pacman.c=0;
			plateau[p.pacman.l][p.pacman.c]='P';
		}
		else
		{
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
		else
		{
			p.pacman.c--;
			plateau[p.pacman.l][p.pacman.c]='P';
		}

		return p.pacman;
	}
	return p.pacman;
}

// DEPLACEMENT DES fantomes[i]

Pos deplacer_fantome_plateau(Partie p, char **plateau)
{
    for(int i=0 ; i<NBFANTOMES ; i++)
    {
        plateau[p.fantomes[i].l][p.fantomes[i].c]=' ';
        //On efface le fantôme avant de le redessiner
        // On redessine le fantome en fonction de la pos de pacman:

        /* Si le pacman est à droite du fantome ET que la case voisine droite du fantome
        * n'est pas un mur, alors on dessine le fantôme. */
        if ( (p.pacman.c > p.fantomes[i].c) && (plateau[p.fantomes[i].l][p.fantomes[i].c ++] != '*') )
        {
            p.fantomes[i].c ++;
            plateau[p.fantomes[i].l][p.fantomes[i].c] = 'F';
        }

        /* Même principe */
        else if ( (p.pacman.c < p.fantomes[i].c) && (plateau[p.fantomes[i].l][p.fantomes[i].c --] != '*') )
        {
            p.fantomes[i].c --;
            plateau[p.fantomes[i].l][p.fantomes[i].c] = 'F';
        }

        /* Si pacman à gauche du fantôme et case voisine non mur alors ... */
        if ( (p.pacman.l > p.fantomes[i].l) && (plateau[p.fantomes[i].l ++][p.fantomes[i].c] != '*') )
        {
            p.fantomes[i].l ++;
            plateau[p.fantomes[i].l][p.fantomes[i].c] = 'F';
        }

        /* Même principe */
        else if ( (p.pacman.c < p.fantomes[i].c) && (plateau[p.fantomes[i].l --][p.fantomes[i].c] != '*') )
        {
            p.fantomes[i].l --;
            plateau[p.fantomes[i].l][p.fantomes[i].c] = 'F';
        }
    }
}

//Fonction qui permet de compter le nombre de pacgommes sur le plateau
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
/******************************************/
/* Fonctions de calculs                 */
/******************************************/

Point pos2point(Pos p,int taille)
{
    Point point = {p.c*taille , p.l*taille};
    return point;
}

// DEFINITION POS2COIN (rectangles)

Point pos2centre(Pos p, int taille)
{
    Point coin ;
    coin.x = p.c*taille + (int)(taille/2);
    coin.y = p.l*taille + (int)(taille/2);
    return coin ;
}

// ALGORITHME DE PLUS COURT CHEMIN 

int distance(Pos p1,Pos p2)
{	/* Variables pour calculer la distance */
	int dist_ligne = p1.l - p2.l; 
	int dist_colonne = p1.c - p2.c;
	
	/* Parce qu'une distance est positive ... */
	if (dist_ligne < 0)
		dist_ligne *= -1;
	else if (dist_colonne < 0)
		dist_colonne *= -1;
		
	/* Pythagore pour avoir la distance à vol d'oiseau */
	int dist = DLIGNES + DCOLONNES; //voir les macros
	return dist;
}

Pos plus_court_chemin(Pos source, Pos cible)
{   
	Pos voisin_haut = {source.l-1, source.c}; //case au dessus de la source
	Pos voisin_bas = {source.l+1, source.c}; //case en dessous de la source
	Pos voisin_avant = {source.l, source.c}; //case voisine vers la source
	//Conditions pour déterminer si l'avant est à droite ou à gauche 
	//de la source :
	if (cible.c > source.c)
		voisin_avant.c = source.c+1 ;
	else if (cible.c < source.c)
		voisin_avant.c = source.c-1 ;
	
	/* Tableau stockant la distance entre les cases voisines
	 * et la cible :                                          */
	int directions[3] = {distance(voisin_haut, cible), distance(voisin_bas, cible), 
						distance(voisin_avant, cible)} ;
	int lpc = 100; //lpc = le plus court chemin
	
	/* Boucle pour déterminer le plus petit élément du tableau, 
	 * cad la plus petite distance :                            */
	for(int i ; i<3 ; i++) 
	{
		if (directions[i] < lpc)
			lpc = directions[i];
	}
	/* Conditions pour retourner la case voisine la plus proche
	 * de la cible                                               */
	 if (lpc == directions[0])
		return voisin_haut;
	else if (lpc == directions[1])
		return voisin_bas;
	else
		return voisin_avant;
}
	

/******************************************/
/* Fonctions de déboggage                 */
/******************************************/

void afficher_plan(Partie p) {
	for(int i=0; i<p.L;i++) {
		for(int j=0;j<p.C;j++) {
		       printf("%c", p.plateau[i][j]);
		}
	printf("\n");
 	}
}
