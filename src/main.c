/******************************************************************************/
/* MAIN.c                                                                     */
/******************************************************************************/
#include "./main.h"

#define TAILLE_CASE 10

/******************************************************************************/
/* MAIN                                                                       */
/******************************************************************************/
int main(int argc, char **argv)
/* argc indique le nombre d'arguments,
   argv est un tableau de mots contenant ces arguments. */
    {
    Partie  p;      // la structure contenant les données d'une partie
    int i,j;

    /** Traitement des arguments **************************************************/
    if(argc!=2) // Si le nombre d'arguments est différent de 2
        {
        printf("Usage: %s fichier_plan\n", argv[0]); // mode d'emploi et sortie
        return 0;
        }
    /******************************************************************************/

    /* Chargement du plan à partir du fichier fourni en paramètre                 */
    printf("Chargement du plan...\n");
    p = charge_plan(argv[1]);
    /* Si problème lors du chargement du plan...                                  */
    if(p.plateau == NULL)
        return 1;

#if DEBUG==1 //Ceci est un drapeau à activer/désactiver dans main.h
    /* Affichage du plan lu                                                       */
    printf("Affichage du plan...\n");
    for(i=0;i!=p.L;i++)
        {
        for(j=0;j!=p.C;j++)
            printf("%c",p.plateau[i][j]);
        printf("\n");
        }
#endif

/******************************************************************************/
/* A PARTIR D'ICI...C'EST A VOUS DE JOUER!                                    */
/******************************************************************************/
// Démarrage du jeu.
    ouvrir_fenetre(800,600);
    demarrage();

    // Affichage du plateau.
    dessiner_plateau(p, p.plateau);
    actualiser();

    // Algorithme du jeu :
    int touche;
    int dir;

    while(touche != SDLK_ESCAPE)
    {
      touche = attendre_touche_duree(1);
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
      }
      p.pacman = deplacer_pacman_visuel(p, p.plateau, dir, MUR);
    }

    // Fermeture du jeu.
    attendre_clic();
    fermer_fenetre();
    return 0;
    }
