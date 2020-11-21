#include "./comp_jeu.h"

const Pos haut = {-1,0};
const Pos bas = {1,0};
const Pos gauche = {0,-1};
const Pos droite = {0,1};


/***********************************/
/* Fonctions visuelles             */
/***********************************/
void demarrage(void)
{
    Point coin = { 0 , 0 } ;
    dessiner_rectangle(coin, LONG, LARG, blanc);
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

Pos deplacer_pacman_visuel(Partie p, char **plateau, Pos direction) {

	Point pacman;
	Point pacman_cible;
  //Calcul des coordonnées de pacman sur la fenêtre
	pacman = pos2centre(p.pacman,CASE);
  //Calcul des coordonnées de la prochaine position de pacman dans la fenêtre
	p.pacman = deplacer_pacman_plateau(p,plateau,direction);

	pacman_cible = pos2centre(p.pacman,CASE);

	if( direction.l == -1 || direction.l == 1 ) {
		//On déplace pacman tant qu'il n'a pas atteint les coordonnées de la case suivante
		while ( pacman.y != pacman_cible.y ) {
			dessiner_disque(pacman, TPACMAN, noir);
			//Utilise selon le vecteur (0;-1) ou (0;1) selon la direction choisie.
			pacman.y += direction.l;
			dessiner_disque(pacman, TPACMAN, jaune);
			actualiser();
      /*On attend un certain temps pour que la vitesse du jeu ne dépendent pas
			de la vitesse de calcul */
			attente(FREQ);
		}
	}

	if(direction.c == -1 || direction.c == 1) {
		while(pacman.x != pacman_cible.x) {
			dessiner_disque(pacman, TPACMAN, noir);
			//Utilise selon le vecteur (1;0) ou (-1;0) selon la direction choisie.
			pacman.x += direction.c;

			if (pacman.x < 0) {
				pacman.x = p.C*CASE - p.C%CASE;
			}

			if (pacman.x > p.C*CASE - p.C%CASE ) {
				pacman.x = 0;
			}

			dessiner_disque(pacman, TPACMAN, jaune);
			actualiser();
			/*On attend un certain temps pour que la vitesse du jeu ne dépendent pas
			de la vitesse de calcul */
			attente(FREQ);
		}
	}
	return p.pacman;
}

void deplacer_fantome_visuel(Partie p,int i_fant) {
  Point p_fant_cible = pos2point(p.fantomes[0],CASE);
  Point p_fant = p_fant_cible;
  if (p.dir_prec[i_fant]==gauche || p.dir_prec[i_fant]==droite) {
    p_fant.x += (p.dir_prec[i_fant]==gauche) ? CASE : -CASE;
  }
  if (p.dir_prec[i_fant]==haut || p.dir_prec[i_fant]==bas) {
    p_fant.y += (p.dir_prec[i_fant]==haut) ? CASE : -CASE;
  }
  dessiner_rectangle(p_fant, TFANTOME , TFANTOME, noir);
  dessiner_rectangle(p_fant_cible, TFANTOME , TFANTOME, pink);
  actualiser();
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
                //dessiner_rectangle(pos2point(fantome, CASE), TFANTOME, TFANTOME, pink);
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


Pos deplacer_pacman_plateau(Partie p,char **plateau,Pos direction) {
  //On efface pacman de son ancien emplacement
	//On dessine pacman dans la direction donné
  if (plateau[p.pacman.l+direction.l][p.pacman.c+direction.c]!='*') {
    plateau[p.pacman.l][p.pacman.c]=' ';
    if(p.pacman.c==0 && direction.c==-1) {
      plateau[p.pacman.l][p.C-1]='P';
      p.pacman.c=C-1;
    } else if (p.pacman.c==C-1 && direction.c==1) {
      plateau[p.pacman.l][0]='P';
      p.pacman.c=0;
    } else {
      p.pacman.c+=direction.c;
      p.pacman.l+=direction.l
      plateau[p.pacman.l+direction.l][p.pacman.c+direction.c]='P';
    }
  }
  return p.pacman;
}

// DEPLACEMENT DES fantomes[i]

void deplacer_fantome_plateau(Pos fantomes[], char **plateau, int i_fant, Pos direction)
{

  plateau[fantomes[i_fant].l][fantomes[i_fant].c]=' ';
  //On efface le fantôme avant de le redessiner
  // On redessine le fantome en fonction de la pos de pacman:
  plateau[fantomes[i_fant].l+direction.l][fantomes[i_fant.c+direction.c]]='F';
  fantomes[i_fant].c += direction.c;
  fantomes[i_fant].l += direction.l;

}

//Fonction qui permet de compter le nombre de pacgommes sur le plateau
int nbpacgommes(Partie p) {

	for(int i=0; i<p.L;i++)
		for(int j=0;j<p.C;j++)
			if(p.plateau[i][j]=='.')
				p.nbpacgommes++;
	return p.nbpacgommes;
}



void direction_possibles(Partie p,int i_fant, Pos dir_prec[], int dir_pos[][4])
{
  if(p.plateau[p.fantomes[i_fant].l-1][p.fantomes[i_fant].c]=='*') {
    dir_pos[i_fant][haut]=-1;
  } else {
    dir_pos[i_fant][haut]=haut;
  }

  if(p.plateau[p.fantomes[i_fant].l][p.fantomes[i_fant].c+1]=='*') {
    dir_pos[i_fant][droite]=-1;
  } else {
    dir_pos[i_fant][droite]=droite;
  }

  if(p.plateau[p.fantomes[i_fant].l+1][p.fantomes[i_fant].c]=='*') {
    dir_pos[i_fant][bas]=-1;
  } else {
    dir_pos[i_fant][bas]=bas;
  }

  if(p.plateau[p.fantomes[i_fant].l][p.fantomes[i_fant].c-1]=='*') {
    dir_pos[i_fant][gauche]=-1;
  } else {
   dir_pos[i_fant][gauche]=gauche;
 }
  dir_pos[i_fant][(dir_prec[i_fant]+2)%4]=-1;
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

Pos plus_court_chemin(Pos source, Pos cible,int i_fant,Pos dir_pos[][4], Pos dir_prec[])
{
	Pos voisin_haut = {source.l-1, source.c}; //case au dessus de la source
	Pos voisin_bas = {source.l+1, source.c}; //case en dessous de la source
	Pos voisin_gauche = {source.l, source.c-1}; //case voisine vers la source
  Pos voisin_droite = {source.l, source.c+1};

	/* Tableau stockant la distance entre les cases voisines
	 * et la cible :                                          */
	int directions[4] = {distance(voisin_haut, cible), distance(voisin_droite, cible),
						distance(voisin_bas, cible), distance(voisin_gauche, cible)} ;
	int lpc = 100; //lpc = le plus court chemin

	/* Boucle pour déterminer le plus petit élément du tableau,
	 * cad la plus petite distance :                            */
	for(int i = 0; i<4 ; i++)
	{
		if (dir_pos[i_fant][i]!=-1 && directions[i] <= lpc)
			lpc = directions[i];
	}
	/* Conditions pour retourner la case voisine la plus proche
	 * de la cible                                               */
	if (lpc == directions[0]) {
    dir_prec[i_fant]=haut;
		return haut;
  }
	else if (lpc == directions[1]) {
    dir_prec[i_fant]=droite;
		return droite;
  }
	else if (lpc == directions[2]) {
    dir_prec[i_fant]=bas;
		return bas;
  }
  else if (lpc == directions[3]){
    dir_prec[i_fant]=gauche;
    return gauche;
  }
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
