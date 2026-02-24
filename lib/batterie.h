#ifndef BATTERIE_H
#define BATTERIE_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void battery_init();
void battery_update(float deltaTime, int doorCount, int lightCount);
void battery_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);

#endif