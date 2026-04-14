/**
 * \file map.c
 * \brief Création and initialisation of game's map.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */


#include "map.h"


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


/**
 * \brief Initializes the player entity.
 *
 * Sets the player position to the predefined spawn point (X_JOUEUR, Y_JOUEUR),
 * enables the light by default, and connects neighbors (except left/right walls).
 *
 * \param joueur Pointer to the player structure.
 * \param map Pointer to the initialized map.
 */
void init_joueur(case_t *joueur, carte_t *map){
    joueur->num_camera = map->cases[X_JOUEUR][Y_JOUEUR].num_camera;
    joueur->lumiere = VRAI;
    joueur->acess = VRAI;
    joueur->voisin_haut = &map->cases[X_JOUEUR-1][Y_JOUEUR];
    joueur->voisin_bas = &map->cases[X_JOUEUR+1][Y_JOUEUR];
    joueur->voisin_gauche = NULL;
    joueur->voisin_droit = NULL;
}

/**
 * \brief Initializes the camera entity.
 *
 * Sets camera to position 10 with default properties and no neighbors.
 *
 * \param camera Pointer to the camera structure.
 * \param map Pointer to the initialized map.
 */
void init_camera(case_t *camera, carte_t *map){
    camera->num_camera = 10;
    camera->lumiere = VRAI;
    camera->acess = VRAI;
    camera->voisin_haut = NULL;
    camera->voisin_bas = NULL;
    camera->voisin_gauche = NULL;
    camera->voisin_droit = NULL;
}

/**
 * \brief Initializes the complete game map.
 *
 * Creates a 5x3 grid of interconnected camera rooms with specific walls
 * blocking certain movements according to the predefined map layout.
 * Numbers cameras sequentially from 1 to 15, sets all accessible by default.
 *
 * \param carte_init Pointer to the carte_t structure to initialize.
 */
void init_carte(carte_t *carte_init){
    int y = 0, x = 0;
    int num = 1;

    for (x = 0; x < FIN_X; ++x) {
        for (y = 0; y < FIN_Y; ++y) {
            carte_init->cases[x][y].voisin_haut = NULL;
            carte_init->cases[x][y].voisin_bas = NULL;
            carte_init->cases[x][y].voisin_droit = NULL;
            carte_init->cases[x][y].voisin_gauche = NULL;


            /* Init each case (y,x) */
            carte_init->cases[x][y].lumiere = FAUX;
            carte_init->cases[x][y].num_camera = num++;
            carte_init->cases[x][y].acess = VRAI;

            /* Upwards neighbor and Downwards neighbor */
            if(accessible(x-1, y)){
                /* If the case is adjacent to a wall */
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
                // If there is no wall then it connects
                else{
                    carte_init->cases[x][y].voisin_haut = &carte_init->cases[x-1][y];
                    carte_init->cases[x-1][y].voisin_bas = &carte_init->cases[x][y];
                }
            }

            /* Left neighbor and Right neighbor */
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
                /* Pour le mur 5 et 15, le monster arrive et ne peut pas repartir ( obligé d'attaquer le joueur )*/
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


/**
 * \brief Checks if a position on the map is accessible.
 *
 * Verifies that the coordinates (x, y) are within the valid map boundaries.
 *
 * \param x X-coordinate to check.
 * \param y Y-coordinate to check.
 * \return VRAI if accessible, FAUX otherwise.
 */
booleen_t accessible(int x, int y){
    if (y < 0 || y >= FIN_Y || x < 0 || x >= FIN_X )
        return FAUX;

    return VRAI;
}

/**
 * \brief Frees the map structure.
 *
 * \param map Pointer to the carte_t structure to destroy.
 */
void detruire_carte(carte_t *map){ 
    free(map); 
}


/* TEST DE LA CARTE 
int main(){
    carte_t *map = malloc(sizeof(carte_t));
    if (!map) return 1;
    init_carte(map);

    int y, x;
    for (x = 0; x < X; x++) {
        for (y = 0; y < Y; y++) {
            if (y == MUR_M_Y && x == MUR_M_X)
                printf("M ");
            if (y == Y_JOUEUR && x == X_JOUEUR)
                    printf("J ");
            if (map->cases[x][y].voisin_droit == NULL)
                printf("|%d ", map->cases[x][y].num_camera);
            else 
                printf("%d ", map->cases[x][y].num_camera); 
        }
        printf("\n\n");
    }
    detruire_carte(map);
    return 0;
    
}
    */