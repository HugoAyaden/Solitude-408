#include "menu_pause.h"
#include <stdio.h>

#define MENU_ITEM_COUNT 4

menu_pause_result_t menu_pause(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *titleFont) {
    const char *menu_items[MENU_ITEM_COUNT] = { "Reprendre", "Settings", "Credits", "Exit" };
    int selected = 0;
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return MENU_EXIT;

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return MENU_CONTINUE;
                    case SDLK_UP:
                        selected--;
                        if (selected < 0) selected = MENU_ITEM_COUNT - 1;
                        break;
                    case SDLK_DOWN:
                        selected++;
                        if (selected >= MENU_ITEM_COUNT) selected = 0;
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        running = 0;
                        break;
                }
            }
        }

        // Fond semi-transparent
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_RenderFillRect(renderer, NULL);

        // Dessiner le menu
        for (int i = 0; i < MENU_ITEM_COUNT; i++) {
            SDL_Color color = (i == selected) ? (SDL_Color){255, 0, 0, 255} : (SDL_Color){255, 255, 255, 255};
            SDL_Surface *surface = TTF_RenderText_Solid(font, menu_items[i], color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            int w, h;
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);
            SDL_Rect rect = {400 - w/2, 200 + i * 60, w, h};
            SDL_RenderCopy(renderer, texture, NULL, &rect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    // Retour du choix
    switch (selected) {
        case 0: return MENU_CONTINUE;
        case 1: return MENU_SETTINGS;
        case 2: return MENU_CREDITS;
        case 3: return MENU_EXIT;
    }
    return MENU_NONE;
}