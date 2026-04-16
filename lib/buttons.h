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


/**
 * \brief Initializes the state of all buttons.
 *
 * All buttons (doors, lights, and cameras) are deactivated at game startup.
 */
void buttons_init();

/**
 * \brief Returns the total number of active camera buttons.
 * \return Sum of all camera button states (0-9).
 */
int cameraButton();

/**
 * \brief Draws an interactive button with centered text.
 *
 * Draws a rectangular button with different colors for active/inactive states
 * and displays centered text inside using the provided font.
 *
 * \param renderer SDL renderer used for drawing.
 * \param font Font used to render the button text.
 * \param rect Rectangle defining button position and size.
 * \param active Button state (1 = active/red, 0 = inactive/gray).
 * \param label Text displayed on the button.
 */
void drawButton(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label);

/**
 * \brief Handles mouse events for door and light buttons.
 *
 * Detects mouse clicks and toggles corresponding buttons (doors, lights, general light,
 * and camera monitor) based on predefined screen regions.
 *
 * \param event SDL event received.
 * \param window SDL window used to retrieve display size.
 * \param img_stretchedW_game_res Stretched image width for button positioning.
 */
void buttons_handleEvent(SDL_Event *event, SDL_Window *window,int img_stretchedW_game_res);

/**
 * \brief Handles mouse events for individual camera buttons.
 *
 * Toggles specific camera buttons (1-9) and updates the active camera view.
 * Only one camera can be active at a time, also handles camera monitor toggle.
 *
 * \param event SDL event received.
 * \param window SDL window used to retrieve display size.
 */
void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window);

/**
 * \brief Draws the camera map overlay on screen.
 *
 * Loads and renders the camera map image positioned at the right side of the screen.
 *
 * \param renderer SDL renderer used for drawing.
 * \param rect Rectangle where you place the image.
 */
void drawCamera(SDL_Renderer *renderer,
                       SDL_Rect rect);


#endif