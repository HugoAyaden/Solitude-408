#include "game.h"
#include "batterie.h"
#include "boutons.h"
#include "menu_pause.h"

void game_init()
{
    battery_init();
    buttons_init();
}

void game_handleEvent(SDL_Event *event, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *fontBattery, TTF_Font *fontButtons)
{
    buttons_handleEvent(event, window);

    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE) {
        menu_pause_result_t result = menu_pause(renderer, fontBattery, fontButtons);

        switch(result) {
            case MENU_CONTINUE:
                // Reprendre le jeu
                break;
            case MENU_SETTINGS:
                // Ouvrir ton menu settings si tu l'as
                break;
            case MENU_CREDITS:
                // Ouvrir ton menu crédits si tu l'as
                break;
            case MENU_EXIT:
                SDL_Event quitEvent;
                quitEvent.type = SDL_QUIT;
                SDL_PushEvent(&quitEvent);
                break;
            default:
                break;
        }
    }
}

void game_update(float deltaTime)
{
    int doorCount = buttons_getDoorCount();
    int lightCount = buttons_getLightCount();

    battery_update(deltaTime, doorCount, lightCount);
}

void game_render(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    battery_render(renderer, fontBattery, w, h);
    buttons_render(renderer, fontButtons, w, h);
}