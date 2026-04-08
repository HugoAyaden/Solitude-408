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
    map->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = NULL;

}

void fermeture_portes_gauche(case_t *joueur, carte_t *map){ 
    map->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = NULL;

}

void ouverture_porte_droite(carte_t *map, case_t *joueur){ 
    /* rétablir les voisins du joueur */
    map->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = joueur;

}

void ouverture_porte_gauche(carte_t *map, case_t *joueur){ 
    /* rétablir les voisins du joueur */
    map->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = joueur;
}


void attaquer_joueur_echec(carte_t *map, case_t *monster, case_t *joueur){
    Mix_PlayChannel(-1, doorKnocking, 0);
    placing_monster(map, monster);
}





