#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("FNAF",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *fontBattery = TTF_OpenFont("./assets/VCR.ttf", 32);
    TTF_Font *fontButtons = TTF_OpenFont("./assets/VCR.ttf", 20);

    if (!fontBattery || !fontButtons)
    {
        printf("Erreur chargement police\n");
        return 1;
    }

    game_init();

    int running = 1;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            game_handleEvent(&event, window);
        }

        game_update(deltaTime);

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        game_render(renderer, fontBattery, fontButtons, window);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(fontBattery);
    TTF_CloseFont(fontButtons);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}