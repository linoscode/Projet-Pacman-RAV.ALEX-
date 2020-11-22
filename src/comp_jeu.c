#include "./comp_jeu.h"

/* Definition des vecteurs de directions en tant que variables globales */
const Pos haut    = {-1,0};
const Pos bas     = { 1,0};
const Pos gauche  = {0,-1};
const Pos droite  = {0, 1};
const Pos def = {0, 0};

/*Regroupe toutes les fonctions et démarre le jeu */
int demarrer_partie(Partie p )
{
  /* On affiche le plateau sur la fenêtre */
  dessiner_plateau(p, p.plateau);
  actualiser();

  // Algorithme du jeu :

  /* Déclaration des variables*/
  int touche; //Stock la touche préssée
  p.tours_bonus=40; // Stock le nombre de tour restant en mode bonus
  p.gameov=0; //Variable pour savoir s'il y'a gameover ou pas

  Pos dir_pacman = def;//On initialise la direction de pacman à immobile

  while(touche != SDLK_ESCAPE && !p.gameov)
  {

    touche = evenement_touche(touche);
    //On converti la touche pressée en vecteur de direction
    dir_pacman = touche2pos(touche);

    //Si pacman n'est pas en mode bonus alors
    if ( p.tours_bonus == 0 ) {
      //On vérifie si il a mangé un bonus
      p.tours_bonus = isbonus(p,dir_pacman);

      /*On assigne les cible de chaque fantome pour qu'ils essaient de manger
      pacman */
      modeChasse(p,p.target,dir_pacman);
      /* On vérifie si pacman s'est fait mangé */
      p.gameov = game_over(p);
      /*On déplace tous les fantomes suivant les cibles précédemment définies*/
      p=deplacer_fantome(p);
    }
    else
    {
      /*Pacman a est en mode bonus alors, les fantôme se déplacent
      aléatoirement*/
      deplacements_aleatoire(p,p.target);
      /*On vérifie regarde si ils ont été mangé */
      estMange(p, p.isMange);
      /*On déplace tous les fantomes suivant les cibles précédemment définies*/
      p=deplacer_fantome(p);
      /*On enlève un tour de bonus*/
      p.tours_bonus--;
    }

    /* On raffraichit l'affichage des pacmangommes présents sur le plateau */
    p.nbpacgommes=rafraichir(p);
    p.pacman = deplacements_visuels(p, p.plateau, dir_pacman);


    /*Si tous les pacgommes ont été mangé alors on sort de la boucle*/
    if(p.nbpacgommes==0)
      break;
  }
  return p.gameov;
}

/***********************************/
/* Fonctions visuelles             */
/***********************************/

/*Permet d'afficher le splash screen */
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


/* On actualise visuellement la position des personnages avec un effet
de déplacement fluide et non case par case*/
Pos deplacements_visuels(Partie p, char **plateau, Pos direction)
{
  Couleur fantomes[4]= {rouge,pink,bleu,jaune};

  int pdone = 0; //variable pour savoir si le déplacement visuel de pacman est terminé
  int fdone = 0; //variable pour savoir si le déplacement des fantomes est terminé

	Point pacman; //coordonnées de pacman actuelle
	Point pacman_cible; //coordonnées de là où il va se déplacer

  //Calcul des coordonnées de pacman sur la fenêtre
  pacman = pos2centre(p.pacman,CASE);

  //Calcul de la prochaine position sur le plateau de pacman
  p.pacman = deplacer_pacman_plateau(p,plateau,direction);

  /*Conversion des coordonnées de la prochaine position sur le plateau de pacman
  en coordonnées sur la fênetre*/
  pacman_cible = pos2centre(p.pacman,CASE);

  /*Déclaration des variables qui stockeront les coordonnées des fantomes sur la
  fenêtre pour leur position actuelle et leur cible */
  Point p_fant[NBFANTOMES];
  Point p_fant_cible[NBFANTOMES];

  for(int i=0; i<NBFANTOMES;i++)
  {
    /*Conversion des des coordonnées des fantomessur le plateau en coordonnées
    sur la fenêtre pour leur position actuelle et leur cible */
    p_fant_cible[i] = pos2coin(p.fantomes[i],CASE);
    p_fant[i] = p_fant_cible[i];
    /*On détermine la postion actuelle en fesant le chemin inverse en utilisant
    la dernière direction prise qui est stockée en mémoire */
    p_fant[i].x -= p.dir_fant[i].c*CASE;
    p_fant[i].y -= p.dir_fant[i].l*CASE;
  }


  /* On effectue les déplacement visuels tant que tout le monden'a pas atteint
   * les coordonnées de la case suivante */
  while (!pdone || !fdone)
  {
    for(int i=0; i<NBFANTOMES;i++) {
      /* Si le fantôme n'a pas atteint sa cible alors */
      if (p_fant[i].x != p_fant_cible[i].x || p_fant[i].y != p_fant_cible[i].y) {
        /*Le déplacement visuel des fantomes n'est pas terminé */
        fdone = 0;
        /* On efface le fantome à sa position précédente */
        dessiner_rectangle(p_fant[i], TFANTOME , TFANTOME, noir);
        /* On déplace le fantome visuellement selon le vecteur de direction
         * du fantome */
        p_fant[i].x += p.dir_fant[i].c;
        p_fant[i].y += p.dir_fant[i].l;

        /*S'il y'a un qui fait effet bonus, ils prennent la couleur bleu*/
        if(p.tours_bonus!=0) {
          dessiner_rectangle(p_fant[i], TFANTOME , TFANTOME, aquamarine);
        }
        /*Sinon ils prennent leur couleur normale*/
        else {
          dessiner_rectangle(p_fant[i], TFANTOME , TFANTOME, fantomes[i]);
        }
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
  /*On récupères les nouvelles coordonnées de pacman */
  return p.pacman;

}

/*Permet de réafficher tous les bonus et pacgommes et compte le nombre de ceux-ci*/
int rafraichir(Partie p) {
  int n=0;
  for(int i=0; i<p.L;i++)
  {
    for(int j=0;j<p.C;j++)
    {
      if (p.plateau[i][j] == '.') // GUM = POINT BLANC
      {
          Pos gum = {i, j};
          changer_pixel(pos2centre(gum,CASE), blanc);
          n++;
      }
      if (p.plateau[i][j] == 'B') // BONUS = DISQUE ROUGE
      {
          Pos bonus = {i, j};
          dessiner_disque(pos2centre(bonus,CASE), TPACMAN, rouge);
          n++;
      }
    }
  }
  /*On retourne le nombre d'élements sur le plateau*/
  return n;
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
                dessiner_rectangle(pos2coin(fantome, CASE), TFANTOME, TFANTOME, pink);
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

/*Récupère la dernière touche pressée */

int evenement_touche(int touche) {
  reinitialiser_evenements();
  traiter_evenements();
  if(touche_a_ete_pressee(SDLK_UP))
    { touche = SDLK_UP; }
  else if(touche_a_ete_pressee(SDLK_DOWN))
    { touche = SDLK_DOWN; }
  else if(touche_a_ete_pressee(SDLK_LEFT))
    { touche = SDLK_LEFT; }
  else if(touche_a_ete_pressee(SDLK_RIGHT))
    { touche = SDLK_RIGHT; }
  else {
    touche = touche;
  }
  return touche;
}

/*Définie les cibles des fantomes aléatoirement */
void deplacements_aleatoire(Partie p,Pos *target) {
  for(int i = 0; i<NBFANTOMES;i++) {
    target[i].c=entier_aleatoire(p.C);
    target[i].l=entier_aleatoire(p.L);
  }
}
void estMange(Partie p, int *isMange) {
  for(int i = 0; i<NBFANTOMES;i++) {
    if(areEqual(p.pacman,p.fantomes[i])) {
      isMange[i]=1;
    } else {
      isMange[i]=0;
    }
  }
}

/*Assigne toutes les targets qui modélise le comportement
de chaque fantome*/
void modeChasse(Partie p,Pos * target,Pos dir_pacman) {
  target[0]=target_pacman(p);
  target[1]=target_devant_pacman(p, dir_pacman);
  target[2]=target_oppose(p, dir_pacman, 0);
  target[3]=target_pacman_clyde(p,3);
}
/* Vérifie si la partie est perdue */
int game_over(Partie p)
{
  int perdu;
    for(int i_fant = 0 ; i_fant < NBFANTOMES ; i_fant++)
    {
      perdu = areEqual(p.pacman, p.fantomes[i_fant]);
      if(perdu) //si t'as perdu
          return 1; //game over = 1 (est vrai)
    }
    return 0; // t'as pas perdu
}



/*Permet de déplacer tous les fantomes*/
Partie deplacer_fantome(Partie p)
{
  for(int i = 0; i<NBFANTOMES  ;i++)
  {
    /* On vérifie les direction possible que peut prendre chaque fantome */
    direction_possibles(p, i, p.dir_prec, p.dir_pos);
    /* On détermine la meilleure direction pour se rapprocher de leurs cibles */
    p.dir_fant[i] = plus_court_chemin(p.fantomes[i], p.target[i], i,
                                        p.dir_pos, p.dir_prec);
    /*Ensuite on déplace les fantomes suivant les directions choisies précédemment*/
    deplacer_fantome_plateau(p, p.fantomes, i, p.dir_fant[i]);
  }

  return p;
}

/*Permet de cibler la case qui est à l'opposé d'un autre fantome*/
Pos target_oppose(Partie p, Pos dir,int i_fant)
{
    Pos cible;
    //Combien de LIGNES séparent fantomes[i_fant] et pacman.
    int dist_lignes = p.fantomes[i_fant].l - p.pacman.l ;
    if ( dist_lignes < 0 )
        dist_lignes *= -1; //prcq une distance est positive.
    //Combien de COLONNES séparent fantomes[i_fant] et pacman.
    int dist_colonnes = p.fantomes[i_fant].c - p.pacman.c ;
    if ( dist_colonnes < 0 )
        dist_colonnes *= -1;

    /*Si le fantôme est AU DESSUS de pacman :        */
    if( p.fantomes[i_fant].l < p.pacman.l )
        //alors cible en dessous pacman :
        cible.l = ( p.pacman.l + dist_lignes )%p.L;
    else
        //SINON cible au dessus de pacman
        cible.l = ( p.pacman.l - dist_lignes )%p.L;

    /*Si le fantôme est A GAUCHE de pacman :        */
    if(p.fantomes[i_fant].c < p.pacman.c)
        //alors cible à droite de pacman
        cible.c = ( p.pacman.c + dist_colonnes )%p.C;
    else
        //SINON cible à gauche de pacman
        cible.c = ( p.pacman.c - dist_colonnes )%p.C;

    return cible;
}

/* Permet de définir la cible comme la case ou se trouve pacman */
Pos target_pacman(Partie p)
{
    Pos cible = { p.pacman.l , p.pacman.c } ;
    return cible ;
}

/*Modélise la cible et le comportement de Clyde*/
Pos target_pacman_clyde(Partie p,int i_fant) {
  Pos cible = { p.pacman.l , p.pacman.c } ;
  /*Si Clyde se trouve à moins de 8 case de pacman alors
  il cible son coin du plateau (scatter mode)            */
  if(distance(p.pacman, p.fantomes[i_fant])<8) {
    cible.c = 1;
    cible.l = p.L-1;
  }
  return cible ;
}

/* Permet de définir la cible comme 2 cases devant la case où se trouve pacman */
Pos target_devant_pacman(Partie p, Pos dir)
{
    Pos cible = { p.pacman.l + 2*dir.l , p.pacman.c + 2*dir.l };
    return cible;
}

/*Permet de vérifier si la case sur laquelle pacman va se déplacer est un bonus*/
int isbonus(Partie p, Pos dir)
{
  if(p.plateau[p.pacman.l+dir.l][p.pacman.c+dir.c]=='B')
  {
    return 20;
  }
  return 0;
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

/* Gère les déplacements des fantomes en fonction de la direction choisie */
void deplacer_fantome_plateau(Partie p,Pos fantomes[], int i_fant, Pos direction)
{
  if (p.isMange[i_fant]==1) {
    fantomes[i_fant].l=13;
    fantomes[i_fant].c=10;
  }
  else if(fantomes[i_fant].c == p.C)
  {
    fantomes[i_fant].c=1;
  }
  else if(fantomes[i_fant].c == 0 )
  {
    fantomes[i_fant].c=p.C-1;
  }
  else
  {
    fantomes[i_fant].c += direction.c;
    fantomes[i_fant].l += direction.l;
  }
}

//Fonction qui permet de compter le nombre de pacgommes sur le plateau
int nbpacgommes(Partie p) {
	for(int i=0; i<p.L;i++)
		for(int j=0;j<p.C;j++)
			if(p.plateau[i][j]=='.') {
				p.nbpacgommes++;
      }
	return p.nbpacgommes;
}




void direction_possibles(Partie p,int i_fant, Pos dir_prec[], Pos dir_pos[][4])
{
  /*Si vérifie si il y'a un mur ou on se trouve aux limites du plateau pour valider
  ou invalider chaque direction */
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
  /*On enlève la direction précédente des directions possibles*/
  dir_pos[i_fant][i2dir(dir_prec[i_fant])]=def;

}

/******************************************/
/* Fonctions de calculs                   */
/******************************************/

/* Vérifie si les positions sont égales */
int areEqual(Pos p1, Pos p2) {
  if(p1.c==p2.c && p2.l==p1.l) {
    return 1;
  }
  return 0;
}

/*Permet de récupérer l'indice du tableau dir_pos qui correspond
à une directions une direction donnée*/
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


/* Converti les coordonnées sur le plateau en coordonnées sur la fenêtre*/
Point pos2point(Pos p,int taille)
{
    Point point = {p.c*taille , p.l*taille};
    return point;
}

/*Permet de récupérer le coin haut gauche pour dessiner les rectangles
représentants les fantomes                                             */
Point pos2coin(Pos p,int taille) {
  Point point = {p.c*taille + TFANTOME/2 , p.l*taille + TFANTOME/2};
  return point;
}

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
  /* On détermine les coordonnées des cases voisines de la source */
	Pos voisin_haut = {source.l-1, source.c};
	Pos voisin_bas = {source.l+1, source.c};
	Pos voisin_gauche = {source.l, source.c-1};
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
  /* Boucle pour déterminer quelle direction est associée à la plus petite
   * distance                                                             */
  for(int i = 0; i<4;i++) {
    if(!areEqual(dir_pos[i_fant][i],def) && lpc == directions[i]) {
      dir_prec[i_fant]=opposite(dir_pos[i_fant][i]);
      return dir_pos[i_fant][i];
    }
  }
  return def;
}

/* Fonction pour avoir le vecteur de direction opposé d'un autre vecteur
 * de direction                                                         */
Pos opposite(Pos d) {
  if(areEqual(d,haut)) {
    return bas;
  }
  else if(areEqual(d,bas)) {
    return haut;
  }
  else if(areEqual(d,gauche))
  {
    return droite;
  }
  else if(areEqual(d,droite))
  {
    return gauche;
  }
  else if(areEqual(d,def))
  {
    return def;
  }
  return def;
}

/*récupère le vecteur direction correspondant à chaque touche directionnelle */
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
