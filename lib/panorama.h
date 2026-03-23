#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bfs.h>

void panoramic_game(int screen_width, int imgW, SDL_Rect* dst);
void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst, direction_t* direction);
void panorama_init();