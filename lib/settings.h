/**
 * \file settings.h
 * \brief Header for the settings.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include "constantes.h"

/**
 * \brief Loads settings from config file.
 *
 * Parses `config/save.cfg` and applies volume/brightness settings to SDL_Mixer.
 * Uses default values if file is missing or corrupted.
 */

void load_settings();
/**
 * \brief Saves current settings to config file.
 *
 * Writes master volume, music volume, brightness, mouse sensitivity,
 * screen mode, and resolution to `config/save.cfg`.
 */

void save_settings();
/**
 * \brief Loads current night progress.
 *
 * Reads night number from `config/night.cfg`.
 */

void load_night();
/**
 * \brief Saves current night progress.
 *
 * Writes night number to `config/night.cfg`.
 *
 * \param night Current night number to save.
 */

void save_night(int night);
/**
 * \brief Applies global brightness overlay.
 *
 * Darkens screen based on brightness setting (0-100%) using blend mode.
 *
 * \param ren SDL renderer.
 * \param sw Screen width.
 * \param sh Screen height.
 */

void draw_brightness_overlay(SDL_Renderer* ren, int sw, int sh);
/**
 * \brief Renders VHS-style green save notification.
 *
 * Displays ">>TAPE SAVED" message in bottom-left corner.
 *
 * \param ren SDL renderer.
 * \param font Font for rendering.
 * \param text Notification text.
 * \param sw Screen width.
 * \param sh Screen height.
 */

void draw_vhs_save_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int sw, int sh);
/**
 * \brief Renders centered purple text inside a button rect.
 *
 * \param ren SDL renderer.
 * \param font Font for rendering.
 * \param text Button text.
 * \param btnRect Button rectangle bounds.
 */

void draw_centered_text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Rect btnRect);
/**
 * \brief Renders purple settings label text.
 *
 * \param ren SDL renderer.
 * \param font Font for rendering.
 * \param text Label text.
 * \param x X position.
 * \param y Y position.
 */

void draw_settings_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
/**
 * \brief Renders white text.
 *
 * \param ren SDL renderer.
 * \param font Font for rendering.
 * \param text Text content.
 * \param x X position.
 * \param y Y position.
 */

void draw_white_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
/**
 * \brief Renders red warning text.
 *
 * \param ren SDL renderer.
 * \param font Font for rendering.
 * \param text Warning text.
 * \param x X position.
 * \param y Y position.
 */

void draw_red_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
/**
 * \brief Renders small scaled HUD text.
 *
 * Scales text to 70% size for HUD elements.
 *
 * \param ren SDL renderer.
 * \param font Font for rendering.
 * \param text HUD text.
 * \param x X position.
 * \param y Y position.
 * \param col Text color.
 */

void draw_small_hud_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y, SDL_Color col);
/**
 * \brief Renders VHS-style HUD icons (battery/quality).
 *
 * Shows battery level and video quality with glitch effects when active.
 *
 * \param ren SDL renderer.
 * \param font Font for icons.
 * \param sw Screen width.
 * \param sh Screen height.
 * \param jX Horizontal jitter offset.
 * \param jY Vertical jitter offset.
 * \param visible Visibility flag.
 * \param targetY Base Y position.
 * \param glitchActive Glitch effect flag.
 */

void draw_hud_icons(SDL_Renderer* ren, TTF_Font* font, int sw, int sh, int jX, int jY, int visible, int targetY, int glitchActive);
/**
 * \brief Renders HUD corner decorations.
 *
 * Draws L-shaped borders in screen corners during VHS effect.
 *
 * \param ren SDL renderer.
 * \param sw Screen width.
 * \param sh Screen height.
 * \param jX Horizontal jitter.
 * \param jY Vertical jitter.
 * \param visible Visibility flag.
 */

void draw_hud_corners(SDL_Renderer* ren, int sw, int sh, int jX, int jY, int visible);
/**
 * \brief Renders the complete settings screen.
 *
 * Displays sliders for volume/brightness/sensitivity, toggle buttons for
 * screen mode/resolution, VHS glitch effects, HUD elements, and save/back buttons.
 * Handles mouse input for interactive controls and returns BACK (1) when back clicked.
 *
 * \param ren SDL renderer.
 * \param font Primary font.
 * \return 1 if BACK button clicked, 0 otherwise.
 */

int render_settings(SDL_Renderer* ren, TTF_Font* font);
/**
 * \brief Cleans up settings screen resources.
 *
 * Frees static texture and background.
 */

void cleanup_settings();

#endif
