/**
 * \file ia_monstre_n3.c
 * \brief Creation and initialisation of the monster's AI for night 3
 * \author Ayaden Hugo
 * \version 1.1
 * \date 09/03/2026
 * 
 */

#include "bfs.h"


/**
 * \brief Mimic's spawnpoint
 * \param map
 * \param mimic
 *
 */

 void placement_mimic(carte_t *map, case_t *mimic){
    *mimic = map->cases[START_MIMIC_X][DEPART_Y];
 }


/* DEPLACEMENT DU MIMIC AU LONG DE LA PARTIE */

void mouvement_mimic(carte_t *map, case_t *mimic){
    
   /* Le mimic se déplace de manière aléatoire sur la map.
    * Il a une chance sur 5 de se déplacer à chaque tour.
    * S'il se trouve à côté du joueur, il attaque.
    * Sinon, il continue à errer.
    * Si le joueur a la lumière allumée, le mimic le tue, sinon il échoue et retourne à son spawn.
    */

    //IF mimic ends screamer mimiuc if monster ends screamer monster if time next night
    if(mimic->num_camera == map->cases[X_JOUEUR-1][Y_JOUEUR].num_camera ||  mimic->num_camera == map->cases[X_JOUEUR+1][Y_JOUEUR].num_camera){
            attaque_mimic(*map, mimic, joueur);
    }
    else{
        if(chance_deplacement() < 10){
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
            return VRAI;
        }
        else{
            printf("Mimic attacks but fails and respawn !\n");
            placement_mimic(&map, mimic);
        }
    return FAUX;
}





