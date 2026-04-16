#ifndef TRANSITION_NUIT_H
#define TRANSITION_NUIT_H

#include "constantes.h"

/**
 * \file transitionNuit.h
 * \brief Animation between two nights and winning screen transition
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.2
 * \date 23/03/2026
 */

/**
 * \brief Affiche une animation de transition entre deux nuits.
 *
 * Cette fonction affiche un texte "Nuit X" centré à l'écran.
 *
 * \param renderer Le renderer SDL utilisé pour l'affichage.
 * \param window La fenêtre SDL (utilisée pour récupérer la taille écran).
 * \param nuitActuelle Numéro de la nuit à afficher.
 *
 * \pre SDL et SDL_ttf doivent être initialisés.
 * \post Une animation est affichée à l'écran.
 */
int transitionNuit(SDL_Renderer *renderer, SDL_Window *window, int nuitActuelle);

/**
 * \brief Displays victory screen with "YOU WIN" fade animation.
 *
 * Complete sequence: fade in -> hold 2s -> fade out.
 *
 * \param renderer SDL renderer.
 * \param window SDL window for sizing.
 * \return 1 on success, negative error codes on failure.
 */
int transitionWin(SDL_Renderer *renderer, SDL_Window *window);

/**
 * \brief Creates fade-in animation for "NIGHT X" text.
 *
 * Gradually increases alpha from 0 to 255 for both text and night number.
 *
 * \param renderer SDL renderer.
 * \param text "NIGHT" texture.
 * \param chiffre Current night number texture.
 * \return 1 on success, -1 if quit event detected.
 */
int fade_in_chiffre_nuit(SDL_Renderer *renderer, SDL_Texture *text, SDL_Texture *chiffre);

/**
 * \brief Fades in the next night number.
 *
 * Keeps current "NIGHT X" visible while fading in next night number.
 *
 * \param renderer SDL renderer.
 * \param chiffreNext Next night number texture.
 * \return 1 on success, -1 if quit event detected.
 */
int fade_in_next(SDL_Renderer *renderer, SDL_Texture *chiffreNext);

/**
 * \brief Fades out current night number.
 *
 * Keeps "NIGHT" and next night number visible while fading out current.
 *
 * \param renderer SDL renderer.
 * \param chiffre Current night number texture.
 * \return 1 on success, -1 if quit event detected.
 */
int fade_out_chiffre(SDL_Renderer *renderer, SDL_Texture *chiffre);

/**
 * \brief Fades out "NIGHT" text and next night number together.
 *
 * \param renderer SDL renderer.
 * \param text "NIGHT" texture.
 * \param chiffre Next night number texture.
 * \return 1 on success, -1 if quit event detected.
 */
int fade_out(SDL_Renderer *renderer, SDL_Texture *text, SDL_Texture *chiffre);

#endif
