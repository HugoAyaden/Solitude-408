#ifndef TRANSITION_NUIT_H
#define TRANSITION_NUIT_H

#include "constantes.h"

/**
 * \file transitionNuit.h
 * \brief Animation between two nights and winning screen
 * \author Bastien L, Hugo AYADEN
 * EFEVRE TAUGOURDEAU
 * \version 1.2
 * \date 23/03/2026
 */

/**
 * \brief Affiche une animation de transition entre deux nuits.
 *
 * Cette fonction affiche un texte "Nuit X" centré à l'écran.
 *
 * \param renderer Le renderer SDL utilisé pour l'affichage
 * \param window La fenêtre SDL (utilisée pour récupérer la taille écran)
 * \param nuitActuelle Numéro de la nuit à afficher
 *
 * \pre SDL et SDL_ttf doivent être initialisés
 * \post Une animation est affichée à l'écran
 */
int transitionNuit(SDL_Renderer *renderer, SDL_Window *window, int nuitActuelle);
int transitionWin(SDL_Renderer *renderer, SDL_Window *window);
int fade_in_chiffre_nuit(SDL_Renderer *renderer, SDL_Texture *text, SDL_Texture *chiffre);
int fade_in_next(SDL_Renderer *renderer, SDL_Texture *chiffreNext);
int fade_out_chiffre(SDL_Renderer *renderer, SDL_Texture *chiffre);
int fade_out(SDL_Renderer *renderer, SDL_Texture *text, SDL_Texture *chiffre);

#endif