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

#define MUR_5_Y 4
#define MUR_5_X 0

#define MUR_15_Y 4
#define MUR_15_X 2

/*
CARTE DE JEU
                              ->mur lié au chiffre       –|_          – = mur haut/ | mur gauche ou droit / _ mur bas
                              ->chiffre                   4
    ___________________
   | 1   2   3   4   5 |        0---y--->
   |________           |        |-1    +1
   | M |  7  8 | 9  | J|        x
   |-––      ––        |        |+1
   | 11  12  13  14  15|        v
   |___________________| 

*/

void init_joueur(case_t *joueur, carte_t *carte){
    joueur->habite = VRAI;
    joueur->num_camera = carte->cases[X_JOUEUR][Y_JOUEUR].num_camera;
    joueur->utilise = FAUX;
    joueur->acess = VRAI;
    joueur->voisin_haut = &carte->cases[X_JOUEUR-1][Y_JOUEUR];
    joueur->voisin_bas = &carte->cases[X_JOUEUR+1][Y_JOUEUR];
    joueur->voisin_gauche = NULL;
    joueur->voisin_droit = NULL;
}


void init_carte(carte_t *carte_init){
    int y = 0, x = 0;
    int num = 1;

    for (x = 0; x < X; ++x) {
        for (y = 0; y < Y; ++y) {
            carte_init->cases[x][y].voisin_haut = NULL;
            carte_init->cases[x][y].voisin_bas = NULL;
            carte_init->cases[x][y].voisin_droit = NULL;
            carte_init->cases[x][y].voisin_gauche = NULL;


            /* initialise la case (y,x) */
            carte_init->cases[x][y].habite = FAUX;
            carte_init->cases[x][y].num_camera = num++;
            carte_init->cases[x][y].utilise = FAUX;
            carte_init->cases[x][y].acess = VRAI;

            /* voisin haut */
            if(accessible(x-1, y)){
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
                    carte_init->cases[x][y].voisin_haut = &carte_init->cases[x-1][y];
                    carte_init->cases[x-1][y].voisin_bas = &carte_init->cases[x][y];
                }
            }

            /* voisin gauche */
            if(accessible(x, y-1)){
                if(y == MUR_7_Y && x == MUR_7_X){
                        carte_init->cases[x][y].voisin_gauche = NULL;
                        carte_init->cases[x][y-1].voisin_droit = NULL;
                }
                else if(y == MUR_9_Y && x == MUR_9_X){
                        carte_init->cases[x][y].voisin_gauche = NULL;
                        carte_init->cases[x][y-1].voisin_droit = NULL;
                }
                else if(y == Y_JOUEUR && x == X_JOUEUR){
                        carte_init->cases[x][y].voisin_gauche = NULL;
                        carte_init->cases[x][y-1].voisin_droit = NULL;
                }
                /* Pour le mur 5 et 15, le monstre arrive et ne peut pas repartir ( obligé d'attaquer le joueur )*/
                else if(y == MUR_5_Y && x == MUR_5_X){
                        carte_init->cases[x][y].voisin_gauche = NULL;
                        carte_init->cases[x][y-1].voisin_droit = &carte_init->cases[x][y];
                }
                else if(y == MUR_15_Y && x == MUR_15_X){
                        carte_init->cases[x][y].voisin_gauche = NULL;
                        carte_init->cases[x][y-1].voisin_droit = &carte_init->cases[x][y];
                }
                else if(carte_init->cases[x][y].voisin_gauche == NULL){
                    carte_init->cases[x][y].voisin_gauche = &carte_init->cases[x][y-1];
                    carte_init->cases[x][y-1].voisin_droit = &carte_init->cases[x][y];
                }
            }
        }
    }
}


booleen_t accessible(int x, int y){
    if (y < 0 || y >= Y || x < 0 || x >= X )
        return FAUX;

    return VRAI;
}

void detruire_carte(carte_t *carte){ 
    free(carte); 
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
            if (carte->cases[x][y].voisin_droit == NULL)
                printf("|%d ", carte->cases[x][y].num_camera);
            else 
                printf("%d ", carte->cases[x][y].num_camera); 
        }
        printf("\n\n");
    }
    detruire_carte(carte);
    return 0;
    
}
    */