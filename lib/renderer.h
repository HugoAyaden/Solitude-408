/**
 * \file renderer.h
 * \brief Header for every in game render.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#ifndef BUTTON_H
#define BUTTON_H


#include "game_core.h"

int render_credits(SDL_Renderer *renderer, 
                   SDL_Window *window);

void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH,
                    int img_stretchedW_game_res);
void camera_buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);
void renderCameraMap(SDL_Renderer *renderer);
void battery_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);
void render_game(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window,
                 int img_stretchedW_game_res);
void affichage(camera_type*camera_type);

extern SDL_Rect btnPorteGauche; 


#endif