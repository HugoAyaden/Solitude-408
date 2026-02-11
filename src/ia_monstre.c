#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <carte.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

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


booleen_t deplacement(carte_t * carte, case_t * monstre, int y, int x){


    if (carte->cases[y][x].acess == VRAI) {
        *monstre = carte->cases[y][x];
        return VRAI;
    }
    return FAUX;
}


/* TEST DE L'IA MONSTRE 
void main(){
    carte_t *carte = malloc(sizeof(carte_t));
    if (!carte) return;
    init_carte(carte);
    case_t monstre;
    placement_monstre(carte, &monstre);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    free(carte);
}
    */