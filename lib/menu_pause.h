#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef enum {
    MENU_CONTINUE,
    MENU_SETTINGS,
    MENU_CREDITS,
    MENU_EXIT,
    MENU_NONE
} menu_pause_result_t;

// Affiche le menu pause et retourne le choix de l'utilisateur
menu_pause_result_t menu_pause(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *titleFont);

#endif