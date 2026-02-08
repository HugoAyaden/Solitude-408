#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct { SDL_Rect rect; SDL_Texture* texture; const char* label; } MenuButton;
typedef enum { STATE_MENU, STATE_SETTINGS } GameState;

// Global Settings Variables from save.cfg
extern int masterVol;
extern int musicVol;
extern int brightness;
extern int mouseSens;

void load_settings();
void save_settings();
void draw_brightness_overlay(SDL_Renderer* ren, int sw, int sh);
int render_settings(SDL_Renderer* ren, TTF_Font* font); 
void cleanup_settings();

void init_menu(SDL_Renderer* renderer, TTF_Font* vcrSmall, TTF_Font* vcrLarge);
void render_menu(SDL_Renderer* renderer);
int check_menu_click(SDL_Point mousePos);
void cleanup_menu();

void draw_settings_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y);
void draw_centered_text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Rect btnRect);

void run_transition(SDL_Renderer* ren, SDL_Texture* staticTex, float progress);
SDL_Texture* CreateStaticTexture(SDL_Renderer* renderer);

#endif