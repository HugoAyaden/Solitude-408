/**
 * \file panorama.h
 * \brief Header de panaorama
 * \author Dos Santos Mathis
 * \version 1.0
 * \date 19/03/2026
 * 
 */
#include <constantes.h>

void panoramic_game(int screen_width, int imgW, SDL_Rect* dst);
void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst, direction_t* direction);
void panoramic_buttons(int screen_width, int imgW, SDL_Rect* imgRect);
void panorama_init();