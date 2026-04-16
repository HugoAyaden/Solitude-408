/**
 * \file ia_monstre_n1.c
 * \brief Creation and initialisation of the monster's AI for night 1
 * \author Ayaden Hugo
 * \version 1.2
 * \date 16/02/2026
 * 
 */

#include "../lib/ia_monstre.h"


void play_gif(IMG_Animation *anim, SDL_Renderer *renderer, int windowW, int windowH, Mix_Chunk *sound, int amount ) {
    if (!anim || anim->count <= 0) return;

    SDL_Texture **textures = malloc(anim->count * sizeof(SDL_Texture *));
    if (!textures) return;

    //creates textures for each frame of the animation
    for (int i = 0; i < anim->count; i++) {
        textures[i] = SDL_CreateTextureFromSurface(renderer, anim->frames[i]);
        if (!textures[i]) {
            for (int j = 0; j < i; j++) SDL_DestroyTexture(textures[j]);
            free(textures);
            return;
        }
    }

    int currentFrame = 0;
    Uint32 lastFrameTime = SDL_GetTicks();

    SDL_Event e;

        Mix_VolumeChunk(sound, (masterVol));
        Mix_PlayChannel(-1, sound, 0);
    int i = 0;
    while(i< amount) {
        //If the player presses escampe the animation ends immediately
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) 
                i = amount;
        }

        Uint32 now = SDL_GetTicks();

        // Main displaying loop
        if (now - lastFrameTime >= (Uint32)anim->delays[currentFrame]) {
            currentFrame = (currentFrame + 1)%anim->count;
            if((currentFrame +1 )%anim->count == 0){
                i++;
            }
            lastFrameTime = now;
        }

        SDL_RenderClear(renderer);
        // Render the current frame of the animation centered on the screen
        SDL_Rect dst = { 0, 0, windowW, windowH };
        SDL_RenderCopy(renderer, textures[currentFrame], NULL, &dst);
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    //cleanup
    for (int i = 0; i < anim->count; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    free(textures);
}

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


booleen_t fin(carte_t *map, case_t *monster){
    if (monster->num_camera == map->cases[X_JOUEUR][Y_JOUEUR].num_camera){
        printf("Le monster a atteint le joueur !\n");
        if(!monster_death){
            printf("Failed to load monster_death animation.\n");
            return -1;
        }
        if(!mimic_death){
            printf("Failed to load mimic_death animation.\n");
            return -2;
        }
        return VRAI;
     }
    return FAUX;
}

/* DEPLACEMENT DU MIMIC AU LONG DE LA PARTIE */
    

int movement_opportunity(carte_t *map, case_t *monster){
    int direction = 0;
    direction = rand() % 4; // 0: haut, 1: droite, 2: bas, 3: gauche

    switch (direction){

        case HAUT: 
        if(monster->voisin_haut != NULL){ 
            *monster = *monster->voisin_haut;
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster);
        break; 

        case DROITE: 
        if(monster->voisin_droit != NULL){ 
            *monster = *monster->voisin_droit; 
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster);
        break; 

        case BAS: 
        if(monster->voisin_bas != NULL){ 
            *monster = *monster->voisin_bas; 
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster);
        break; 

        case GAUCHE: 
        if(monster->voisin_gauche != NULL){
            *monster = *monster->voisin_gauche; 
            return VRAI; 
        } 
        else
            movement_opportunity(map, monster);
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
