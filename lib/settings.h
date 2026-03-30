#ifndef SETTINGS_H
#define SETTINGS_H

#include <MainMenu.h>


// Global Settings Variables from save.cfg
int masterVol = 80, musicVol = 60, brightness = 50, mouseSens = 40;
int screenModeIndex = 1; 
int resIndex = 2; 
int night = -1;
static int overBack = 0;

// Local Settings Variables
static Mix_Chunk* sGlitch = NULL;

// Background Textures
static SDL_Texture* settingsStaticTex = NULL;
static SDL_Texture* settingsBG = NULL; 
static Uint32 saveNotificationTimer = 0; 

typedef enum screen_t {WINDOWED,FULLSCREEN};
// Interface Options
const char* screenModes[] = {"WINDOWED", "FULLSCREEN", "BORDERLESS"};
const char* resolutions[] = {"3840x2160", "2560x1440", "1920x1080", "1440x900"};

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