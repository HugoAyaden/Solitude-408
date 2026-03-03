#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "afficher_batterie.h"
#include "batterie.h"
#include "boutons.h"

void game_init()
{
    battery_init();
    buttons_init();
}

void game_handleEvent(SDL_Event *event, SDL_Window *window)
{
    buttons_handleEvent(event, window);
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