#ifndef BOUTONS_H
#define BOUTONS_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void buttons_init();
void buttons_handleEvent(SDL_Event *event, SDL_Window *window);
void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);

int buttons_getDoorCount();
int buttons_getLightCount();

#endif