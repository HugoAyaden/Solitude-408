#ifndef GAME_CORE_H
#define GAME_CORE_H

#include <constantes.h>
#include <buttons.h>
#include <settings.h>
#include <portes.h>
#include <renderer.h>


void change_camera(case_t * camera, case_t * monstre);
int buttons_getDoorCount();
int buttons_getLightCount();
void game_handleEvent(SDL_Event *event, SDL_Window *window);
void battery_init();
void game_initialise();
void battery_update(float deltaTime, int doorCount, int lightCount);
void game_update(float deltaTime);
void difficulte(int night);
void update();
void game_init(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* fontBattery, TTF_Font* fontButtons);
void game_final_cleanup();

#endif