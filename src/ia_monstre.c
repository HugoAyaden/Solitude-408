#include <stdio.h>
#include <ia_monstre_n1.h>

#define START_MONSTRE_X 3
#define DEPART 0

void placement_monstre(carte_t *carte, case_t *monstre){
    srand(time(NULL));
    int x = rand() % START_MONSTRE_X;
    int y = DEPART;
    while(x == 1){
        printf("x = %d\n", x);
        x = rand() % START_MONSTRE_X;
    }
    printf("x = %d\n", x);
    *monstre = carte->cases[x][y];
}

booleen_t fin(carte_t *carte, case_t *monstre){
    if (monstre->num_camera == carte->cases[X_JOUEUR][Y_JOUEUR].num_camera)
        return VRAI;
    return FAUX;
}
    

/* 
 * le monstre choisi aleatoirement un des 4 chemins possibles
 * si il est accessible il se deplace 
 * sinon il en reprend une jusqu a ce qu il soit arrive au joueur
 */

int movement_opportunity(carte_t *carte, case_t *monstre, int y, int x){
    int direction = 0;
    direction = rand() % 4; // 0: haut, 1: droite, 2: bas, 3: gauche

    switch (direction){
        case 0: 
        if(monstre->voisin_haut != NULL){ 
            *monstre = *monstre->voisin_haut;
            monstre->habite = VRAI;
            return VRAI; 
        } 
        break; 
        case 1: 
        if(monstre->voisin_droit != NULL){ 
            *monstre = *monstre->voisin_droit; 
            monstre->habite = VRAI;
            return VRAI; 
        } 
        break; 
        case 2: 
        if(monstre->voisin_bas != NULL){ 
            *monstre = *monstre->voisin_bas; 
            monstre->habite = VRAI;
            return VRAI; 
        } 
        break; 
        case 3: 
        if(monstre->voisin_gauche != NULL){
            *monstre = *monstre->voisin_gauche; 
            monstre->habite = VRAI;
            return VRAI; 
        } 
        break; 
        default: 
            break; 
    } 
    return FAUX;
}




/* TEST DU SPAWN L'IA MONSTRE ET DE SON DEPLACEMENT 
int main(){
    carte_t *carte = malloc(sizeof(carte_t));
    if (!carte) 
        return 0;
    init_carte(carte);
    case_t monstre;
    placement_monstre(carte, &monstre);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    while(!fin(carte, &monstre)){
        if(movement_opportunity(carte, &monstre, monstre.num_camera % Y, monstre.num_camera / Y)){
            printf("Le monstre se déplace vers la caméra %d\n", monstre.num_camera);
            sleep(1); // Attendre 5 seconde avant le prochain déplacement
        }
    }
    detruire_carte(carte);
}

*/