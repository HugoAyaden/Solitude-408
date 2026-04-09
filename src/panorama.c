#include <panorama.h>
/**
  * \file panorama.c
  * \brief Fournie les fonctions pour le déplacement de camera de jeu
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/

/**
  * \fn void panoramic_game(int screen_width, int imgW, SDL_Rect* dst)
  * \brief Déplacement gauche-droite de la camera avec la souris, principalement pour la salle principal.
  * \param screen_width Entier, longeur de l'ecran
  * \param imgW Entier, longeur de l'image
  * \param imgRect SDL_Rect, rectangle de rendu
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/
void panoramic_game(int screen_width, int imgW, SDL_Rect* imgRect) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    int move_zone_left = (int)screen_width * res_percentage;        //position par rapport a l'ecran ou la camera commence à bouger - gauche
    int move_zone_right = (int)screen_width * (1 - res_percentage); //position par rapport a l'ecran ou la camera commence à bouger - droit
    int img_limit_right = -imgW + screen_width;                     //limite de position de l'image a droite


    // Déplacer l'image horizontalement
    if (mouseX >= move_zone_left && imgRect->x > img_limit_right) {

        if ((imgRect->x - pixel_offset_game) <= img_limit_right) {
            imgRect->x = img_limit_right;

        }
        else {
            imgRect->x -= pixel_offset_game;
        }

        camera_offset_x = imgRect->x;
    }
    else if (mouseX <= move_zone_right && imgRect->x < img_limit_left) {
        if ((imgRect->x + pixel_offset_game) >= img_limit_left)
        {
            imgRect->x = img_limit_left;
        }
        else {
            imgRect->x += pixel_offset_game;
        }
        camera_offset_x = imgRect->x;
    }
}

/**
  * \fn void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst)
  * \brief Déplacement gauche-droite de la camera automatique, principalement pour les cameras.
  * \param screen_width int, longeur de l'ecran
  * \param imgW int, longeur de l'image
  * \param imgRect SDL_Rect*, rectangle de rendu
  * \param direction Direction*, direction de deplacement
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/
void panoramic_camera(int screen_width, int imgW, SDL_Rect* imgRect, direction_t* direction) {
    int img_limit_right = -imgW + screen_width; //limite de position de l'image a droite

    // Déplacer l'image horizontalement camera automatiquement
    if (*direction == GAUCHE)
    {
        if ((imgRect->x + pixel_offset_cam) >= img_limit_left)
        {
            imgRect->x = img_limit_left;
            *direction = DROITE;
        }
        else
        {
            imgRect->x += pixel_offset_cam;
        }
    }
    if (*direction == DROITE)
    {
        if ((imgRect->x - pixel_offset_cam) <= img_limit_right)
        {
            imgRect->x = img_limit_right;
            *direction = GAUCHE;
        }
        else
        {
            imgRect->x -= pixel_offset_cam;
        }
    }
}