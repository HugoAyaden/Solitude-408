/**
 * \file MainMenu.h
 * \brief Header for the Main Menu structure -> transition -> settings.
 * \author Amara Louay
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#ifndef GAME_H
#define GAME_H

#define NEW_GAME 0
#define LOAD_GAME 1
#define SETTINGS 2
#define CREDITS 3
#define EXIT_GAME 4

#include "game_core.h"

void init_menu(SDL_Renderer* renderer, TTF_Font* vcrSmall, TTF_Font* vcrLarge);
void render_menu(SDL_Renderer* renderer);
int check_menu_click(SDL_Point mousePos);
void cleanup_menu();

void run_transition(SDL_Renderer* ren, SDL_Texture* staticTex, float progress);
SDL_Texture* CreateStaticTexture(SDL_Renderer* renderer);

#endif