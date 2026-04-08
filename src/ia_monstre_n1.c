/**
 * \file ia_monstre_n1.c
 * \brief Creation and initialisation of the monster's AI for night 1
 * \author Ayaden Hugo
 * \version 1.1
 * \date 16/02/2026
 * 
 */

#include "ia_monstre.h"

/**
 * \brief Choose from each place where the monster can spawn (either 0 or 2) since 1 is is mimic's spawn.
 * 
 * 
 */



void placing_monster(carte_t *map, case_t *monster){
    int x = rand() % START_MONSTRE_X;
    int y = DEPART_Y;
    while(x == 1){
        printf("monster x = %d\n", x);
        x = rand() % START_MONSTRE_X;
    }
    printf("monster x = %d\n", x);
    *monster = map->cases[x][y];
    Mix_VolumeChunk(monsterSpawn, (masterVol));
    Mix_PlayChannel(-1, monsterSpawn, 0);
    
}


 /* END DE PARTIE */
booleen_t fin(carte_t *map, case_t *monster){
    if (monster->num_camera == map->cases[X_JOUEUR][Y_JOUEUR].num_camera){
        printf("Le monster a atteint le joueur !\n");
        return VRAI;
    }
    return FAUX;
}

/* DEPLACEMENT DU MIMIC AU LONG DE LA PARTIE */
    

/* 
 * le monster choisi aleatoirement un des 4 chemins possibles
 * si il est accessible il se deplace 
 * sinon il en reprend une jusqu a ce qu il soit arrive au joueur
 */


int movement_opportunity(carte_t *map, case_t *monster, int y, int x){
    int direction = 0;
    direction = rand() % 4; // 0: haut, 1: droite, 2: bas, 3: gauche

    switch (direction){

        case HAUT: 
        if(monster->voisin_haut != NULL){ 
            *monster = *monster->voisin_haut;
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster, y, x);
        break; 

        case DROITE: 
        if(monster->voisin_droit != NULL){ 
            *monster = *monster->voisin_droit; 
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster, y, x);
        break; 

        case BAS: 
        if(monster->voisin_bas != NULL){ 
            *monster = *monster->voisin_bas; 
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster, y, x);
        break; 

        case GAUCHE: 
        if(monster->voisin_gauche != NULL){
            *monster = *monster->voisin_gauche; 
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster, y, x);
        break; 
        default: 
            break; 
    } 
    return FAUX;
}




/* TEST DU SPAWN L'IA MONSTRE ET DE SON DEPLACEMENT (sans le systeme de portes donc le joueur perd a chaque fois)
int main(){
    carte_t *map = malloc(sizeof(carte_t));
    if (!map) 
        return 0;
    srand(time(NULL));
    init_carte(map);
    case_t monster;
    case_t joueur;
    init_joueur(&joueur, map);
    placing_monster(map, &monster);
    printf("Le monster est sur la caméra %d\n", monster.num_camera);
    while(!fin(map, &monster)){
        timer();
        movement_opportunity(map, &monster, monster.num_camera % END_Y, monster.num_camera / END_Y);
        printf("Le monster se déplace sur la caméra %d\n", monster.num_camera);
    }
    detruire_carte(map);
}
*/