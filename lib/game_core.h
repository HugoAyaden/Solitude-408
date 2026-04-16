/**
 * \file game_core.h
 * \brief Heador for the main game loop
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.4
 * \date 10/03/2026
 *
 */

#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "constantes.h"
#include "buttons.h"
#include "settings.h"
#include "portes.h"
#include "renderer.h"
#include "transitionNuit.h"
#include "panorama.h"


typedef struct {
    int camera_id;
    int enabled;
    SDL_Texture *base;
    SDL_Texture *monster;
    SDL_Texture *mimic;
    SDL_Texture *both;
} CameraAssetSet;

/**
 * \brief Updates the displayed camera view.
 *
 * The camera numbers follow the layout defined in "map.c",
 * not the in-game numbering, for realism purposes.
 *
 * \param camera Pointer to the currently selected camera.
 * \param monster Pointer to the monster position.
 * \param camera_type Pointer to the current camera display mode.
 */

void change_camera(case_t * camera, case_t * monstre, camera_type* camera_type);
/**
 * \brief Returns the number of active doors.
 *
 * \return Number of currently active doors.
 */

int buttons_getDoorCount();
/**
 * \brief Returns the number of active lights.
 *
 * \return Number of currently active lights.
 */

int buttons_getLightCount();
/**
 * \brief Handles global game events.
 *
 * Dispatches SDL events to the appropriate subsystem,
 * such as the standard buttons or the camera buttons.
 *
 * \param event SDL event received.
 * \param window SDL window used by the UI.
 * \param img_stretchedW_game_res Width of the stretched game image.
 */

void game_handleEvent(SDL_Event *event, SDL_Window *window,int img_stretchedW_game_res);
/**
 * \brief Initializes the player's battery.
 */

void battery_init();
/**
 * \brief Initializes the main game systems.
 *
 * This includes the battery and all button states.
 */

void game_initialise();
/**
 * \brief Updates the battery level.
 *
 * Battery consumption depends on the number of closed doors
 * and the number of active lights.
 *
 * \param deltaTime Time elapsed since the last frame.
 * \param doorCount Number of closed doors.
 * \param lightCount Number of active lights.
 */

void battery_update(float deltaTime, int doorCount, int lightCount);
/**
 * \brief Updates the main game logic.
 *
 * Currently updates battery consumption based on door and light usage.
 *
 * \param deltaTime Time elapsed since the last frame.
 */

void game_update(float deltaTime);
/**
 * \brief Adjusts the game difficulty according to the current night.
 *
 * Depending on the night, the monster may move more or less often,
 * and the mimic becomes active starting from night 2.
 *
 * \param night Current night number.
 */

void difficulte(int night);
/**
 * \brief Updates the monster and door logic for the current frame.
 *
 * Handles door-triggered attacks, applies AI difficulty behavior,
 * and updates the remaining time for the current night.
 */

void update();
/**
 * \brief Initializes the game and starts the main gameplay loop.
 *
 * Allocates game objects, loads saved progress and settings,
 * initializes the map, player, cameras, and monster, then runs
 * the main rendering and event loop.
 *
 * \param renderer SDL renderer used for drawing.
 * \param window SDL window used for sizing and rendering setup.
 * \param fontBattery Font used for battery display.
 * \param fontButtons Font used for button labels.
 */

void game_init(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* fontBattery, TTF_Font* fontButtons);
/**
 * \brief Frees all game resources and clears allocated memory.
 *
 * Releases map data, dynamically allocated entities, and loaded audio assets.
 */

void game_final_cleanup();

/**
 * \brief Preloads all game assets.
 *
 * Loads textures, animations, and sounds needed during gameplay.
 *
 * \param renderer SDL renderer used for texture creation.
 */

void preload_assets_1(SDL_Renderer* renderer);
void preload_assets_2(SDL_Renderer* renderer);
void preload_assets_3(SDL_Renderer* renderer);
void preload_assets_4(SDL_Renderer* renderer);

#endif
