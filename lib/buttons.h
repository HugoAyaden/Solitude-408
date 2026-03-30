/**
 * \file buttons.h
 * \brief Header pour la structure du menu principal -> transition -> settings.
 * \author Amara Louay
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <MainMenu.h>

void buttons_init();
int cameraButton();
static void drawButton(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label);
void buttons_handleEvent(SDL_Event *event, SDL_Window *window);
void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window);
static void drawCamera(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label);


#endif