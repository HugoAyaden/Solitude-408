/**
 * \file renderer.h
 * \brief Header for every in game render.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "game_core.h"

/**
 * \brief Displays the game credits with vertical scrolling.
 *
 * This function displays a credits screen with a text scrolling effect from
 * bottom to top, similar to movie credits. The background image is displayed
 * behind the text, and certain lines can be highlighted with different font
 * sizes.
 *
 * The display stops when all credits have scrolled off the screen.
 *
 * \param renderer SDL renderer used for graphical rendering.
 * \param window SDL window used to retrieve display dimensions.
 */
int render_credits(SDL_Renderer *renderer,
                   SDL_Window *window);

/**
 * \brief Renders all control buttons on screen.
 *
 * Draws door and light buttons on left/right sides of the screen, plus the
 * camera monitor toggle. Button positions scale with stretched game image
 * resolution.
 *
 * \param renderer SDL renderer used for drawing.
 * \param font Font used for button labels.
 * \param windowW Window width.
 * \param windowH Window height.
 * \param img_stretchedW_game_res Stretched game image width for button positioning.
 */
void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH,
                    int img_stretchedW_game_res);

/**
 * \brief Renders the individual camera selection buttons.
 *
 * Draws 9 camera toggle buttons plus the camera monitor toggle in fixed
 * positions on the right side of the screen.
 *
 * \param renderer SDL renderer used for drawing.
 * \param font Font parameter (unused).
 * \param windowW Window width.
 * \param windowH Window height.
 */
void camera_buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);

/**
 * \brief Renders the camera map overlay.
 *
 * Displays the static camera map image when the monitor is active.
 *
 * \param renderer SDL renderer used for drawing.
 */
void renderCameraMap(SDL_Renderer *renderer);

/**
 * \brief Renders the battery bar UI element.
 *
 * Draws a battery outline with a fill bar that changes from green to red
 * based on remaining battery percentage, plus a text label showing %.
 *
 * \param renderer SDL renderer used for drawing.
 * \param font Font used for percentage text.
 * \param windowW Window width.
 * \param windowH Window height.
 */
void battery_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH);

/**
 * \brief Renders all game UI elements.
 *
 * Displays the battery bar and either standard control buttons or camera
 * buttons depending on whether the camera monitor is active.
 *
 * \param renderer SDL renderer.
 * \param fontBattery Font for battery display.
 * \param fontButtons Font for button labels.
 * \param window SDL window for size retrieval.
 * \param img_stretchedW_game_res Stretched game image width.
 */
void render_game(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window,
                 int img_stretchedW_game_res);

/**
 * \brief Selects appropriate background texture based on game state.
 *
 * Chooses from preloaded textures based on battery state, door states,
 * light states, and monster proximity. Sets the camera type to GAME or
 * delegates to change_camera() when the monitor is active.
 *
 * \param camera_type Pointer to current camera display mode.
 */
void affichage(camera_type*camera_type);

extern SDL_Rect btnPorteGauche;

#endif
