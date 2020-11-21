#include "./comp_jeu.h"

const Pos haut    = {-1,0};
const Pos bas     = { 1,0};
const Pos gauche  = {0,-1};
const Pos droite  = {0, 1};
const Pos def = {0, 0};

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
    afficher_texte("Ravaka RALAMBOARIVONY et Alexandre PAPAVASILEIOU"
                    , 20, coin, rouge);
    actualiser();
    attente(1500);
    coin.x = 0;
    coin.y = 0;
    dessiner_rectangle(coin, LONG, LARG, noir) ;
}

void rafraichirbonuspg(Partie p) {
  for(int i=0; i<p.L;i++)
  {
    for(int j=0;j<p.C;j++)
    {
      if (p.plateau[i][j] == '.') // GUM = POINT BLANC
      {
          Pos gum = {i, j};
          changer_pixel(pos2centre(gum,CASE), blanc);
      }
      if (p.plateau[i][j] == 'B') // BONUS = DISQUE ROUGE
      {
          Pos bonus = {i, j};
          dessiner_disque(pos2centre(bonus,CASE), TPACMAN, rouge);
      }
    }
  }
}

void demarrer_partie(Partie p ) {
  dessiner_plateau(p, p.plateau);
  actualiser();

  // Algorithme du jeu :
  int touche;
  Pos dir;
  // Tout mettre dans une fonction
  //deplacer_hors_spawn(p.fantomes, p.plateau);

  while(touche != SDLK_ESCAPE)
  {
    touche = attendre_touche_duree(1);
    dir = touche2pos(touche);

    for(int i = 0; i<NBFANTOMES;i++) {
      direction_possibles(p,i,p.dir_prec,p.dir_pos);
      p.target[i].c=1;
      p.target[i].l=1;
      p.dir_fant[i] = plus_court_chemin(p.fantomes[i], p.target[i], i,
                                          p.dir_pos, p.dir_prec);
      printf("dir fant %d %d \n", p.dir_fant[i].c, p.dir_fant[i].l);
      deplacer_fantome_plateau(p.fantomes,p.plateau,i,p.dir_fant[i]);
    }
    p.pacman = deplacements_visuels(p, p.plateau, dir);
  }
}

Pos deplacements_visuels(Partie p, char **plateau, Pos direction) {

  int pdone = 0;
  int fdone = 0;

	Point pacman;
	Point pacman_cible;

  Point p_fant[NBFANTOMES];
  Point p_fant_cible[NBFANTOMES];

  for(int i=0; i<NBFANTOMES;i++) {
    p_fant_cible[i] = pos2point(p.fantomes[i],CASE);
    p_fant[i] = p_fant_cible[i];
    p_fant[i].x -= p.dir_fant[i].c*CASE;
    p_fant[i].y -= p.dir_fant[i].l*CASE;
  }
  //Calcul des coordonnées de pacman sur la fenêtre
	pacman = pos2centre(p.pacman,CASE);
  //Calcul des coordonnées de la prochaine position de pacman dans la fenêtre
	p.pacman = deplacer_pacman_plateau(p,plateau,direction);

	pacman_cible = pos2centre(p.pacman,CASE);

      //On déplace pacman tant qu'il n'a pas atteint les coordonnées de la case suivante
  while (!pdone || !fdone) {

    for(int i=0; i<NBFANTOMES;i++) {
      if (p_fant[i].x != p_fant_cible[i].x || p_fant[i].y != p_fant_cible[i].y) {
          dessiner_rectangle(p_fant[i], TFANTOME , TFANTOME, noir);
          p_fant[i].x += p.dir_fant[i].c;
          p_fant[i].y += p.dir_fant[i].l;
          dessiner_rectangle(p_fant[i], TFANTOME , TFANTOME, pink);
    } else {
      fdone = 1;
    }
  }

    if (pacman.x != pacman_cible.x || pacman.y != pacman_cible.y) {
      dessiner_disque(pacman, TPACMAN, noir);
      if(pacman.x > p.C*CASE) {
        pacman.x=0;
      }
      if(pacman.x < 0 ) {
        pacman.x=p.C*CASE;
      }
      //Utilise selon le vecteur (0;-1) ou (0;1) selon la direction choisie.
      pacman.x += direction.c;
      pacman.y += direction.l;
      dessiner_disque(pacman, TPACMAN, jaune);
    } else {
      pdone = 1;
    }

    actualiser();
    /*On attend un certain temps pour que la vitesse du jeu ne dépendent pas
    de la vitesse de calcul */
    attente(FREQ);
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
Pos touche2pos(int touche) {
  Pos dir;
  switch ( touche )
  {
    case SDLK_UP:
      dir = haut;
      break;
    case SDLK_LEFT:
      dir = gauche;
      break;
    case SDLK_DOWN:
      dir = bas;
      break;
    case SDLK_RIGHT:
      dir = droite;
      break;
    default:
      dir = def;
      break;
  }
  return dir;
}


Pos deplacer_pacman_plateau(Partie p,char **plateau,Pos direction) {
  //On efface pacman de son ancien emplacement
	//On dessine pacman dans la direction donné
  if (plateau[p.pacman.l+direction.l][p.pacman.c+direction.c]!='*') {
    plateau[p.pacman.l][p.pacman.c]=' ';
    if(p.pacman.c==0 && direction.c==-1) {
      p.pacman.c=p.C-1;
      plateau[p.pacman.l][p.pacman.c]='P';
    } else if (p.pacman.c==p.C-1 && direction.c==1) {
      p.pacman.c=0;
      plateau[p.pacman.l][0]='P';
    } else {
      p.pacman.c+=direction.c;
      p.pacman.l+=direction.l;
    }
    plateau[p.pacman.l][p.pacman.c]='P';
  }
  return p.pacman;
}

// DEPLACEMENT DES fantomes[i]

void deplacer_fantome_plateau(Pos fantomes[], char **plateau, int i_fant, Pos direction)
{

  plateau[fantomes[i_fant].l][fantomes[i_fant].c]=' ';
  //On efface le fantôme avant de le redessiner
  // On redessine le fantome en fonction de la pos de pacman:
  plateau[fantomes[i_fant].l+direction.l][fantomes[i_fant].c+direction.c]='F';
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

int areEqual(Pos p1, Pos p2) {
  if(p1.c==p2.c && p2.l==p1.l) {
    return 1;
  }
  return 0;
}

int i2dir(Pos dir) {
  if(areEqual(dir,haut)) {
    return 0;
  }
  else if(areEqual(dir,droite)) {
    return 1;
  }
  else if(areEqual(dir,bas)) {
    return 2;
  }
  else if(areEqual(dir,gauche)) {
    return 3;
  }
  return 2;
}

void direction_possibles(Partie p,int i_fant, Pos dir_prec[], Pos dir_pos[][4])
{
  if(p.fantomes[i_fant].l==0 || p.plateau[p.fantomes[i_fant].l-1][p.fantomes[i_fant].c]=='*') {
    dir_pos[i_fant][0]=def;
  } else {
    dir_pos[i_fant][0]=haut;
  }

  if(p.fantomes[i_fant].c==p.C || p.plateau[p.fantomes[i_fant].l][p.fantomes[i_fant].c+1]=='*') {
    dir_pos[i_fant][1]=def;
  } else {
    dir_pos[i_fant][1]=droite;
  }

  if(p.fantomes[i_fant].l==p.L || p.plateau[p.fantomes[i_fant].l+1][p.fantomes[i_fant].c]=='*') {
    dir_pos[i_fant][2]=def;
  } else {
    dir_pos[i_fant][2]=bas;
  }

  if(p.fantomes[i_fant].c==0 || p.plateau[p.fantomes[i_fant].l][p.fantomes[i_fant].c-1]=='*') {
    dir_pos[i_fant][3]=def;
  } else {
   dir_pos[i_fant][3]=gauche;
  }
  dir_pos[i_fant][i2dir(dir_prec[i_fant])]=def;

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
	Pos voisin_haut = {source.l-1, source.c};   //case au dessus de la source
	Pos voisin_bas = {source.l+1, source.c};    //case en dessous de la source
	Pos voisin_gauche = {source.l, source.c-1}; //case voisine vers la source
  Pos voisin_droite = {source.l, source.c+1};

	/* Tableau stockant la distance entre les cases voisines
	 * et la cible :                                          */
	int directions[4] = {distance(voisin_haut, cible), distance(voisin_droite, cible),
						           distance(voisin_bas, cible), distance(voisin_gauche, cible)} ;
	int lpc = 1000000000; //lpc = le plus court chemin

	/* Boucle pour déterminer le plus petit élément du tableau,
	 * cad la plus petite distance :                            */
	for(int i = 0; i<4 ; i++)
	{
		if (!areEqual(dir_pos[i_fant][i],def) && directions[i] <= lpc) {
			lpc = directions[i];
    }
	}
  for(int i = 0; i<4 ; i++) {
    printf("%d %d \n",dir_pos[i_fant][i].c,dir_pos[i_fant][i].l);
  }

  for(int i = 0; i<4;i++) {
    if(!areEqual(dir_pos[i_fant][i],def) && lpc == directions[i]) {
      dir_prec[i_fant]=opposite(dir_pos[i_fant][i]);
      return dir_pos[i_fant][i];
    }
  }
  return def;
}

Pos opposite(Pos d) {
  if(areEqual(d,haut)) {
    return bas;
  }
  else if(areEqual(d,bas)) {
    return haut;
  }
  else if(areEqual(d,gauche)) {
    return droite;
  }
  else if(areEqual(d,droite)) {
    return gauche;
  } else if(areEqual(d,def)) {
    printf("No decision made\n");
    return def;
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

void deplacer_hors_spawn(Pos *fantomes, char **plateau) {
  deplacer_fantome_plateau(fantomes,plateau,0,haut);
  deplacer_fantome_plateau(fantomes,plateau,0,gauche);
  deplacer_fantome_plateau(fantomes,plateau,0,haut);
  deplacer_fantome_plateau(fantomes,plateau,0,haut);
}
