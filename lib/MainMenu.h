/**
 * \file MainMenu.h
 * \brief Header for the Main Menu structure
 * \author Amara Louay
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#ifndef GAME_H
#define GAME_H

#define NEW_GAME 0
#define LOAD_GAME 1
#define SETTINGS 2
#define CREDITS 3
#define EXIT_GAME 4

#include "game_core.h"

/**
 * \brief Initializes the main menu assets and textures.
 *
 * Loads the background image and creates textures for the title and
 * all menu buttons using the provided fonts. Prevents double initialization.
 *
 * \param renderer SDL renderer used for texture creation.
 * \param mainFont Font used for button labels.
 * \param titleFont Font used for the game title.
 */

void init_menu(SDL_Renderer* renderer, TTF_Font* vcrSmall, TTF_Font* vcrLarge);
/**
 * \brief Renders the main menu screen.
 *
 * Draws the background, centered title with dynamic underline, and interactive
 * buttons with hover effects. Button positions and sizes scale with window resolution.
 *
 * \param renderer SDL renderer used for drawing.
 */

void render_menu(SDL_Renderer* renderer);
/**
 * \brief Checks if a mouse click occurred on any menu button.
 *
 * Iterates through all buttons to see if the click position intersects
 * with any button's rectangle. Returns the index of the clicked button
 * or -1 if no button was clicked.
 *
 * \param mousePos The position of the mouse click.
 * \return Index of the clicked button (0-4) or -1 if none.
 */

int check_menu_click(SDL_Point mousePos);
/**
 * \brief Frees all menu-related resources.
 *
 * Destroys textures for buttons, title, and background to prevent memory leaks.
 */

void cleanup_menu();

#endif
