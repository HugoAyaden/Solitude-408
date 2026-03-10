/**
 * \file ia_monstre_n3.c
 * \brief Création et initialisation de l'IA du mimic
 * \author Ayaden Hugo
 * \version 1.0
 * \date 09/03/2026
 * 
 */

#include <ia_monstre.h>

/* DEPART DU MIMIC */

 void placement_mimic(carte_t *carte, case_t *mimic){
    *mimic = carte->cases[START_MIMIC_X][DEPART_Y];
 }


/* DEPLACEMENT DU MIMIC AU LONG DE LA PARTIE */

void mouvement_mimic(carte_t *carte, case_t *mimic){
    
   /* Le mimic se déplace de manière aléatoire sur la carte.
    * Il a une chance sur 5 de se déplacer à chaque tour.
    * S'il se trouve à côté du joueur, il attaque.
    * Sinon, il continue à errer.
    * Si le joueur a la lumière allumée, le mimic le tue, sinon il échoue et retourne à son spawn.
    */
    
    int action = rand() %5;
    if(action == 2){
            int x = rand() % FIN_X;
            int y = rand() % FIN_Y;
            *mimic = carte->cases[x][y];
        while(mimic->num_camera == carte->cases[X_JOUEUR][Y_JOUEUR].num_camera){
            printf("mimic x = %d\n", x);
            x = rand() % FIN_X;
            y = rand() % FIN_Y;
            *mimic = carte->cases[x][y];
        }
        printf("Le mimic se déplace vers la caméra %d\n", mimic->num_camera);
        *mimic = carte->cases[x][y];
    }
    else{
        printf("Le mimic ne bouge pas\n");
    }
}



int attaque_mimic(carte_t carte, case_t *mimic, case_t *joueur){
    if(mimic->num_camera == carte.cases[X_JOUEUR-1][Y_JOUEUR].num_camera ||  mimic->num_camera == carte.cases[X_JOUEUR+1][Y_JOUEUR].num_camera){
        if(joueur->lumiere == VRAI){
            printf("Le mimic attaque le joueur et le tue !\n");
            return VRAI;
        }
        else{
            printf("Le mimic attaque le joueur mais il échoue et retourne à son spawn !\n");
            placement_mimic(&carte, mimic);
        }
    }
    return FAUX;
}





/* TEST DU SPAWN L'IA MONSTRE ET DE SON DEPLACEMENT (sans le systeme de portes donc le joueur perd a chaque fois)
int main(){
    carte_t *carte = malloc(sizeof(carte_t));
    if (!carte) 
        return 0;
    srand(time(NULL));
    init_carte(carte);
    case_t monstre;
    case_t mimic;
    case_t joueur;
    init_joueur(&joueur, carte);
    placement_monstre(carte, &monstre);
    placement_mimic(carte, &mimic);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    printf("Le mimic est sur la caméra %d\n", mimic.num_camera);
    while(!fin(carte, &monstre) && !attaque_mimic(*carte, &mimic, &joueur)){
        sleep(2);
        movement_opportunity(carte, &monstre, monstre.num_camera % FIN_Y, monstre.num_camera / FIN_Y);
        mouvement_mimic(carte, &mimic);
            printf("Le monstre se déplace vers la caméra %d\n", monstre.num_camera);
    }
    detruire_carte(carte);
}
*/
