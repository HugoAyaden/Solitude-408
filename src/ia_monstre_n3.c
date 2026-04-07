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
    
    if(chance_deplacement() < 1){
            int x = rand() % END_X;
            int y = rand() % END_Y;
            *mimic = map->cases[x][y];
        while(mimic->num_camera == map->cases[X_JOUEUR][Y_JOUEUR].num_camera){
            printf("mimic x = %d\n", x);
            x = rand() % END_X;
            y = rand() % END_Y;
            *mimic = map->cases[x][y];
        }
        printf("Mimic move to %d th camera\n", mimic->num_camera);
    }
    else{
        printf("Mimic don't move\n");
    }
}



int attaque_mimic(carte_t map, case_t *mimic, case_t *joueur){
    if(mimic->num_camera == map.cases[X_JOUEUR-1][Y_JOUEUR].num_camera ||  mimic->num_camera == map.cases[X_JOUEUR+1][Y_JOUEUR].num_camera){
        if(joueur->lumiere == VRAI){
            printf("Mimic attacks and kills !\n");
            return VRAI;
        }
        else{
            printf("Mimic attacks but fails and respawn !\n");
            placement_mimic(&map, mimic);
        }
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
    placement_monstre(map, &monster);
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