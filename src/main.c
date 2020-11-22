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
/* Déclaration des variables*/
int game_over;
// Démarrage du jeu.
    ouvrir_fenetre(800,600);
    demarrage();

    // Affichage du plateau.
    game_over = demarrer_partie(p);
    if (game_over) {
      printf("Vous avez perdu !\n");
      fermer_fenetre();
    }
    // Fermeture du jeu.
    attendre_clic();
    fermer_fenetre();
    return 0;
    }
