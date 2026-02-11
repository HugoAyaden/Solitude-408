#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BATTERY_DURATION 10.0f // 360.0 pour 6 minutes en secondes

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("FNAF Battery",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 32);

    if (!font)
    {
        printf("Erreur chargement police\n");
        return 1;
    }

    int running = 1;
    SDL_Event event;

    Uint32 startTime = SDL_GetTicks();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        Uint32 currentTime = SDL_GetTicks();
        float elapsedSeconds = (currentTime - startTime) / 1000.0f;

        float battery = 100.0f - (elapsedSeconds / BATTERY_DURATION) * 100.0f;
        if (battery < 0)
            battery = 0;

        if (battery <= 0)
            running = 0;

        // Clear écran
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        // Couleur batterie (vert -> rouge)
        if (battery > 30)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Barre batterie
        SDL_Rect batteryBar = {
            250,
            250,
            (int)(300 * (battery / 100.0f)),
            50};

        SDL_RenderFillRect(renderer, &batteryBar);

        // Texte %
        char text[20];
        sprintf(text, "Battery: %.0f%%", battery);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, text, white);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect textRect = {
            300,
            180,
            surface->w,
            surface->h};

        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
