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

#include <constantes.h>

void load_settings();
void save_settings();
void load_night();
void save_night(int night);
void draw_brightness_overlay(SDL_Renderer* ren, int sw, int sh);
void draw_vhs_save_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int sw, int sh);
void draw_centered_text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Rect btnRect);
void draw_settings_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
void draw_white_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
void draw_red_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
void draw_small_hud_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y, SDL_Color col);
void draw_hud_icons(SDL_Renderer* ren, TTF_Font* font, int sw, int sh, int jX, int jY, int visible, int targetY, int glitchActive);
void draw_hud_corners(SDL_Renderer* ren, int sw, int sh, int jX, int jY, int visible);
int render_settings(SDL_Renderer* ren, TTF_Font* font);
void cleanup_settings();

#endif