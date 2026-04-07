/**
 * \file buttons.h
 * \brief Header pour la structure du menu principal -> transition -> settings.
 * \author Amara Louay
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#ifndef BUTTON_H
#define BUTTON_H


#include <game_core.h>

void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);
void camera_buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);
void renderCameraMap(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);
void battery_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);
void render_game(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window);
void affichage(int*in_camera);


#endif