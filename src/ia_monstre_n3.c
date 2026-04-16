/**
 * \file ia_monstre_n3.c
 * \brief Creation and initialisation of the mimic's AI for night 3
 * \author Ayaden Hugo
 * \version 1.1
 * \date 09/03/2026
 * 
 */

#include "../lib/bfs.h"


 void placement_mimic(carte_t *map, case_t *mimic){
    *mimic = map->cases[START_MIMIC_X][DEPART_Y];
 }



/* DEPLACEMENT DU MIMIC AU LONG DE LA PARTIE */

void mouvement_mimic(carte_t *map, case_t *mimic){
    
    if(mimic->num_camera == map->cases[X_JOUEUR-1][Y_JOUEUR].num_camera ||  mimic->num_camera == map->cases[X_JOUEUR+1][Y_JOUEUR].num_camera){
            attaque_mimic(*map, mimic, joueur);
    }
    else{
        if(chance_deplacement() < PERCENT_MOVE_MIMIC){
                int x = rand() % END_X;
                int y = rand() % END_Y;
                *mimic = map->cases[x][y];
            while(mimic->num_camera == joueur->num_camera){
                printf("mimic x = %d\n", x);
                x = rand() % END_X;
                y = rand() % END_Y;
                *mimic = map->cases[x][y];
            }
            printf("Mimic move to %d th camera\n", mimic->num_camera);
            //Plays a sound to warn the player it moved
            Mix_VolumeChunk(mimicMove, (masterVol));
            Mix_PlayChannel(-1, mimicMove, 0);
        }
        else{
            printf("Mimic don't move\n");
        }
    }
}


int attaque_mimic(carte_t map, case_t *mimic, case_t *joueur){
        if(joueur->lumiere == VRAI){
            printf("Mimic attacks and kills !\n");
            mimic->num_camera = map.cases[X_JOUEUR][Y_JOUEUR].num_camera;
            fin(&map, mimic);
            return VRAI;
        }
        else{
            printf("Mimic attacks but fails and respawn !\n");
            Mix_VolumeChunk(sad_mimic, (masterVol));
            Mix_PlayChannel(-1, sad_mimic, 0);
            placement_mimic(&map, mimic);
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
    case_t mimic;
    case_t joueur;
    init_joueur(&joueur, map);
    placing_monster(map, &monster);
    placement_mimic(map, &mimic);
    printf("Le monster est sur la caméra %d\n", monster.num_camera);
    printf("Le mimic est sur la caméra %d\n", mimic.num_camera);
    while(!fin(map, &monster) && !attaque_mimic(*map, &mimic, &joueur)){
        sleep(2);
        if(chance_deplacement() < 3){ // 30% de chance de se déplacer de facon optimisee (hint)
            move_monster(map, &monster, &joueur);
        }
        else{
            movement_opportunity(map, &monster, monster.num_camera % END_Y, monster.num_camera / END_Y);
            printf("Le monster se déplace vers la caméra %d\n", monster.num_camera);
    }
        mouvement_mimic(map, &mimic);
    }
    detruire_carte(map);
}
*/
