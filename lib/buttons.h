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

#include "constantes.h"

/* --- Dimensions des boutons principaux (portes / lumières) --- */
#define BTN_MAIN_W        60   /* largeur en pixels  */
#define BTN_MAIN_H        60   /* hauteur en pixels  */
#define BTN_MAIN_SPACING  20   /* marge depuis le bord de la fenêtre */

/* --- Dimensions des petits boutons de sélection de caméra --- */
#define BTN_CAM_W         44
#define BTN_CAM_H         27

/* --- Barre de basculement "CAMERAS" en bas de l'écran --- */
#define BTN_TOGGLE_X      500  /* position X fixe (supposée résolution ≥ 1360px) */
#define BTN_TOGGLE_W      860
#define BTN_TOGGLE_H      60

void buttons_init(void);
int  cameraButton(void);

/* Désactive toutes les caméras d'un coup (cameras_on[0..8] = 0).
 * Appelé avant d'en activer une nouvelle pour garantir l'exclusivité. */
void reset_all_cameras(void);

/* Calcule les SDL_Rect des 9 boutons caméra en fonction de la taille de fenêtre.
 * Source unique de vérité : modifier ici suffit pour les deux fonctions
 * camera_buttons_handleEvent() et camera_buttons_render(). */
void build_camera_rects(SDL_Rect rects[9], int windowW, int windowH);

void drawButton(SDL_Renderer *renderer, TTF_Font *font,
                SDL_Rect rect, int active, const char *label);
void buttons_handleEvent(SDL_Event *event, SDL_Window *window);
void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window);

/* Affiche l'image de la carte des caméras. Ne dessine ni texte ni état actif. */
void drawCamera(SDL_Renderer *renderer, SDL_Rect rect);


#endif