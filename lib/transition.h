#ifndef TRANSITION_H
#define TRANSITION_H

#include <SDL2/SDL.h>

void run_transition(SDL_Renderer* ren, SDL_Texture* staticTex, float progress);
SDL_Texture* CreateStaticTexture(SDL_Renderer* renderer);

#endif