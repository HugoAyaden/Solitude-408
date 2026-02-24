#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void game_init();
void game_handleEvent(SDL_Event *event, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *fontBattery, TTF_Font *fontButtons);
void game_update(float deltaTime);
void game_render(SDL_Renderer *renderer, TTF_Font *fontBattery, TTF_Font *fontButtons, SDL_Window *window);

#endif