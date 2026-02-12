#include <stdio.h>
#include <ia_monstre_n1.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

void fermeture_portes(carte_t *carte, case_t *joueur){ 
    carte->cases[X_JOUEUR][Y_JOUEUR].voisin_haut = NULL; 
    carte->cases[X_JOUEUR][Y_JOUEUR].voisin_bas = NULL;
    carte->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = NULL; 
    carte->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = NULL;
    printf("Porte fermée\n"); 

}

void ouverture_portes(carte_t *carte, case_t *joueur){ 
    carte->cases[X_JOUEUR][Y_JOUEUR].voisin_haut = &carte->cases[X_JOUEUR-1][Y_JOUEUR]; 
    carte->cases[X_JOUEUR][Y_JOUEUR].voisin_bas = &carte->cases[X_JOUEUR+1][Y_JOUEUR]; 
    carte->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = &carte->cases[X_JOUEUR][Y_JOUEUR]; 
    carte->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = &carte->cases[X_JOUEUR][Y_JOUEUR]; 
    printf("Porte ouverte\n"); }

int main(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
    fprintf(stderr, "Erreur SDL: %s\n", SDL_GetError());
    return -1;
}

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
    free(carte);
    TTF_Quit(); 
    IMG_Quit(); 
    SDL_Quit(); 
    return 0;
}