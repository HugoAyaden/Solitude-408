/**
 * \file ia_monstre_n1.c
 * \brief Création et initialisation de l'IA du monstre a la nuit 1
 * \author Ayaden Hugo
 * \version 1.1
 * \date 16/02/2026
 * 
 */

#include <ia_monstre.h>

/**
 * \brief Parmis les endroits ou le monstre peut spawn on en choisin un (soit 0 soit 2) puisque 1 est la case du mimic.
 * 
 * 
 */


 /* TODO: INITIALISER DES TIMESTAMPS ET LES COMPARER POUR GARDER LE MONSTRE SUR PLACE
    EX: TIMESTAMP ACTUEL 9 WHILE TIMESTAMP != 15 check timestamp;
 */
int timer_monstre(){

}

void placement_monstre(carte_t *carte, case_t *monstre){
    int x = rand() % START_MONSTRE_X;
    int y = DEPART_Y;
    while(x == 1){
        printf("monstre x = %d\n", x);
        x = rand() % START_MONSTRE_X;
    }
    printf("monstre x = %d\n", x);
    *monstre = carte->cases[x][y];
}


 /* FIN DE PARTIE */
booleen_t fin(carte_t *carte, case_t *monstre){
    if (monstre->num_camera == carte->cases[X_JOUEUR][Y_JOUEUR].num_camera){
        printf("Le monstre a atteint le joueur !\n");
        return VRAI;
    }
    return FAUX;
}

/* DEPLACEMENT DU MIMIC AU LONG DE LA PARTIE */
    

/* 
 * le monstre choisi aleatoirement un des 4 chemins possibles
 * si il est accessible il se deplace 
 * sinon il en reprend une jusqu a ce qu il soit arrive au joueur
 */


int movement_opportunity(carte_t *carte, case_t *monstre, int y, int x){
    int direction = 0;
    direction = rand() % 4; // 0: haut, 1: droite, 2: bas, 3: gauche

    switch (direction){

        case HAUT: 
        if(monstre->voisin_haut != NULL){ 
            *monstre = *monstre->voisin_haut;
            monstre->habite = VRAI;
            return VRAI; 
        } 
        else
            movement_opportunity(carte, monstre, y, x);
        break; 

        case DROITE: 
        if(monstre->voisin_droit != NULL){ 
            *monstre = *monstre->voisin_droit; 
            monstre->habite = VRAI;
            return VRAI; 
        } 
        else
            movement_opportunity(carte, monstre, y, x);
        break; 

        case BAS: 
        if(monstre->voisin_bas != NULL){ 
            *monstre = *monstre->voisin_bas; 
            monstre->habite = VRAI;
            return VRAI; 
        } 
        else
            movement_opportunity(carte, monstre, y, x);
        break; 

        case GAUCHE: 
        if(monstre->voisin_gauche != NULL){
            *monstre = *monstre->voisin_gauche; 
            monstre->habite = VRAI;
            return VRAI; 
        } 
        else
            movement_opportunity(carte, monstre, y, x);
        break; 
        default: 
            break; 
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
    case_t joueur;
    init_joueur(&joueur, carte);
    placement_monstre(carte, &monstre);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    while(!fin(carte, &monstre)){
        sleep(2);
        movement_opportunity(carte, &monstre, monstre.num_camera % FIN_Y, monstre.num_camera / FIN_Y);
        printf("Le monstre se déplace sur la caméra %d\n", monstre.num_camera);
    }
    detruire_carte(carte);
}
*/