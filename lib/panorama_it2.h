#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef enum direction_s
{
    LEFT,
    RIGHT
} direction_t;

float get_camera_angle(int screen_width);
void render_perspective(SDL_Renderer* r, SDL_Texture* tex,
    int screen_w, int screen_h,
    float angle, SDL_Rect* dst);
void panoramic_game(int screen_width, int imgW, SDL_Rect* dst);
void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst, direction_t* direction);
void panorama_init();