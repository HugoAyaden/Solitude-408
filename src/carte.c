/**
 * \file carte.c
 * \brief Création et initialisation de la carte du jeu.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */


#include <stdio.h>
#include <carte.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


/* MURS DANS LES CARTES */
#define MUR_8_Y 2
#define MUR_8_X 1

#define MUR_9_Y 3
#define MUR_9_X 1

#define MUR_11_Y 0
#define MUR_11_X 2

#define MUR_13_Y 2
#define MUR_13_X 2

#define MUR_7_Y 1
#define MUR_7_X 1

#define MUR_M_Y 0
#define MUR_M_X 1

/*
CARTE DE JEU
                              ->mur lié au chiffre       –|_          – = mur haut/ | mur gauche ou droit / _ mur bas
                              ->chiffre                   4
    ___________________
   | 1   2   3   4   5 |        0---y--->
   | ______            |        |-1    +1
   | M |  7  8 | 9  | J|        x
   | ––      ––        |        |+1
   | 11  12  13  14  15|        v
   |___________________| 

*/



void init_carte(carte_t *carte_init){
    int y = 0, x = 0;
    int num = 1;

    for (x = 0; x < X; ++x) {
        for (y = 0; y < Y; ++y) {

            /* initialise la case (y,x) */
            carte_init->cases[x][y].habite = FAUX;
            carte_init->cases[x][y].num_camera = num++;
            carte_init->cases[x][y].utilise = FAUX;

            /* voisin haut */
            if(accessible(y, x-1)){
                /* Si le pointeur pointe sur la case  alors qu'elle est coté mur alors la case n'affecte pas le pointeur */
                if (x == MUR_M_X && y == MUR_M_Y){
                    carte_init->cases[x][y].voisin_haut = NULL;
                /* Et de même en retour */
                    carte_init->cases[x-1][y].voisin_bas = NULL;
                }
                else if (x == MUR_7_X && y == MUR_7_Y){
                    carte_init->cases[x][y].voisin_haut = NULL;
                    carte_init->cases[x-1][y].voisin_bas = NULL;
                }
                else if (x == MUR_11_X && y == MUR_11_Y){
                    carte_init->cases[x][y].voisin_haut = NULL;
                    carte_init->cases[x-1][y].voisin_bas = NULL;
                }
                else if (x == MUR_13_X && y == MUR_13_Y){
                    carte_init->cases[x][y].voisin_haut = NULL;
                    carte_init->cases[x-1][y].voisin_bas = NULL;
                }
                else{
                    carte_init->cases[x][y].voisin_haut = &carte_init->cases[x][y-1];
                    carte_init->cases[x-1][y].voisin_bas = &carte_init->cases[x][y];
                }
            }


            /* voisin droit */
            if (accessible(y+1, x)){
                if(y == MUR_8_Y && x == MUR_8_X){
                    carte_init->cases[x][y].voisin_droit = NULL;
                    carte_init->cases[x][y+1].voisin_gauche = NULL;
            }
            else if (y == MUR_M_Y && x == MUR_M_X){
                    carte_init->cases[x][y].voisin_droit = NULL;
                    carte_init->cases[x][y+1].voisin_gauche = NULL;
            }
            else if (y == MUR_9_Y && x == MUR_9_X){
                    carte_init->cases[x][y].voisin_droit = NULL;
                    carte_init->cases[x][y+1].voisin_gauche = NULL;
            }
            else{
                carte_init->cases[x][y].voisin_droit = &carte_init->cases[x][y+1];
                carte_init->cases[x][y+1].voisin_gauche = &carte_init->cases[x][y];
            }
        }

            /* accès interdit pour la case du joueur (y,x) */
            if (y == Y_JOUEUR && x == X_JOUEUR)
                carte_init->cases[x][y].acess = FAUX;
            else
                carte_init->cases[x][y].acess = VRAI;
        }
    }
}


booleen_t accessible(int y, int x){
    if (y < 0 || y >= Y || x < 0 || x >= X )
        return FAUX;

    return VRAI;
}



/* TEST DE LA CARTE 
int main(){
    carte_t *carte = malloc(sizeof(carte_t));
    if (!carte) return 1;
    init_carte(carte);

    int y, x;
    for (x = 0; x < X; x++) {
        for (y = 0; y < Y; y++) {
            if (y == MUR_M_Y && x == MUR_M_X)
                printf("M ");
            if (y == Y_JOUEUR && x == X_JOUEUR)
                    printf("J ");
            if (carte->cases[x][y].voisin_bas == NULL)
                printf("|%d ", carte->cases[x][y].num_camera);
            else 
                printf("%d ", carte->cases[x][y].num_camera); 
        }
        printf("\n\n");
    }

    free(carte);
    return 0;
    
}
    */