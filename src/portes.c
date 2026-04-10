/**
 * \file portes.c
 * \brief File for in-game doors.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#include "portes.h"



void fermeture_portes_droite(case_t *joueur, carte_t *map){ 
    Mix_PlayChannel(-1, door_close, 0);
    map->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = NULL;

}

void fermeture_portes_gauche(case_t *joueur, carte_t *map){ 
    Mix_PlayChannel(-1, door_close, 0);
    map->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = NULL;

}

void ouverture_porte_droite(carte_t *map, case_t *joueur){ 
    // Mix_PlayChannel(-1, door_close, 0);
    /* rétablir les voisins du joueur */
    map->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = joueur;

}

void ouverture_porte_gauche(carte_t *map, case_t *joueur){ 
    // Mix_PlayChannel(-1, door_close, 0);
    /* rétablir les voisins du joueur */
    map->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = joueur;
}


void attaquer_joueur_echec(carte_t *map, case_t *monster, case_t *joueur){
    Mix_PlayChannel(-1, doorKnocking, 0);
    placing_monster(map, monster);
}





    /*
int main(){

    carte_t *map = malloc(sizeof(carte_t));
    case_t *joueur = malloc(sizeof(case_t));
    if (!map || !joueur) {
        free(map);
        free(joueur);
        return 0;
    }
    init_carte(map);
    init_joueur(joueur, map);
    map->cases[X_JOUEUR][Y_JOUEUR] = *joueur;
    case_t monster;
    case_t mimic;
    placement_mimic(map, &mimic);
    placing_monster(map, &monster);
    printf("Le monster est sur la caméra %d\n", monster.num_camera);
    while(!fin(map, &monster) && !attaque_mimic(*map, &mimic, joueur)){
        if(chance_deplacement() < 5 )
            move_monster(map, &monster, joueur);
        else{
            movement_opportunity(map, &monster, monster.num_camera % END_Y, monster.num_camera / END_Y);
            printf("Le monster se déplace vers la caméra %d\n", monster.num_camera);
        }
        sleep(1); // Attendre 1 seconde avant le prochain déplacement
        if(monster.num_camera == PORTE_HAUT || monster.num_camera == PORTE_BAS){
            if(joueur->acess == FAUX){
                printf("Le monster attaque le joueur à la porte mais échoue !\n");
                attaquer_joueur_echec(map, &monster, joueur);
            }
            else{
                if(joueur->acess == VRAI){
                    attaquer_joueur(map, &monster, joueur);
                    fin(map, &monster);
                }
            }
        }
    }
    free(map);
    free(joueur);
    joueur = NULL;
    return 0;
}
    */
