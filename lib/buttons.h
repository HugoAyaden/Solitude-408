/**
 * \file buttons.h
 * \brief Header for the buttons structure
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.2
 * \date 11/02/2026
 * 
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "constantes.h"

void buttons_init();
int cameraButton();
void drawButton(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label);
void buttons_handleEvent(SDL_Event *event, SDL_Window *window,int img_stretchedW_game_res);
void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window);
void drawCamera(SDL_Renderer *renderer,
                       SDL_Rect rect);


#endif