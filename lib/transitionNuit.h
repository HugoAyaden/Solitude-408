#ifndef TRANSITION_NUIT_H
#define TRANSITION_NUIT_H

#include <SDL2/SDL.h>

/**
 * \file transitionNuit.h
 * \brief Animation de transition entre deux nuits (effet roue de compteur)
<<<<<<< HEAD
 * \author Bastien LEFEVRE TAUGOURDEAU
=======
 * \author Bastien L
 * EFEVRE TAUGOURDEAU
>>>>>>> origin/dev
 * \version 1.0
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
void transitionNuit(SDL_Renderer *renderer, SDL_Window *window, int nuitActuelle);

#endif