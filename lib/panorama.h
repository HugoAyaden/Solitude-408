/**
 * \file panorama.h
 * \brief Header de panaorama
 * \author Dos Santos Mathis
 * \version 1.0
 * \date 19/03/2026
 * 
 */
#include "constantes.h"

/**
 * \brief Déplacement gauche-droite de la camera avec la souris, principalement pour la salle principal.
 *
 * \param screen_width Entier, longueur de l'écran.
 * \param imgW Entier, longueur de l'image.
 * \param imgRect SDL_Rect, rectangle de rendu.
 */
void panoramic_game(int screen_width, int imgW, SDL_Rect* imgRect);

/**
 * \brief Déplacement gauche-droite de la camera automatique, principalement pour les cameras.
 *
 * \param screen_width int, longueur de l'écran.
 * \param imgW int, longueur de l'image.
 * \param imgRect SDL_Rect*, rectangle de rendu.
 * \param direction Direction*, direction de deplacement.
 */
void panoramic_camera(int screen_width, int imgW, SDL_Rect* imgRect, direction_t* direction);

void panorama_init();
