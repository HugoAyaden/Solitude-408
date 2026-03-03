#include "credits.h"

void show_credits(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *titleFont) {

    SDL_Event event;
    int running = 1;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Ici affichages des textes avec SDL_ttf
        // comme dans le menu pause

        SDL_RenderPresent(renderer);
    }
}