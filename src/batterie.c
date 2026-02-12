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

    TTF_Font *font = TTF_OpenFont("./src/VCR.ttf", 32);

    if (!font)
    {
        printf("Erreur chargement police\n");
        return 1;
    }

    int running = 1;
    SDL_Event event;

    Uint32 startTime = SDL_GetTicks();

    const int batteryWidth = 150; // largeur barre
    const int batteryHeight = 40; // hauteur barre
    const int capWidth = 10;      // largeur “cap” de batterie
    const int margin = 20;        // marge par rapport aux bords

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        Uint32 currentTime = SDL_GetTicks();
        float elapsedSeconds = (currentTime - startTime) / 1000.0f;

        static Uint32 lastTime = 0;
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        float drainRate = 100.0f / BATTERY_DURATION; // % par seconde

        if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_G]){
            drainRate *= 2.0f; // consomme 2x plus vite
        }

        float battery = 100.0f - (elapsedSeconds / BATTERY_DURATION) * 100.0f;
        battery -= drainRate * deltaTime;
        if (battery < 0)
            battery = 0;

        if (battery <= 0)
            running = 0;

        // Clear écran
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        // Position batterie bas gauche
        int x = margin;
        int y = WINDOW_HEIGHT - batteryHeight - margin;

        // Bordure batterie (rectangle blanc)
        SDL_Rect batteryOutline = {x, y, batteryWidth, batteryHeight};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &batteryOutline);

        // “Cap” de la batterie
        SDL_Rect batteryCap = {x + batteryWidth, y + batteryHeight / 4, capWidth, batteryHeight / 2};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &batteryCap);

        // Barre intérieure (vert -> rouge)
        SDL_Rect batteryBar = {x, y, (int)(batteryWidth * (battery / 100.0f)), batteryHeight};
        // Couleur batterie avec dégradé
        SDL_Color batteryColor;
        if (battery > 50)
        {
            // Vert plein si >30%
            batteryColor.r = 0;
            batteryColor.g = 255;
            batteryColor.b = 0;
        }
        else
        {
            // Dégradé rouge-vert si <=30%
            // battery = 0 → rouge pur (255,0,0)
            // battery = 50 → vert pur (0,255,0)
            float ratio = battery / 50.0f;                  // 1 à 0
            batteryColor.r = (Uint8)(255 * (1.0f - ratio)); // R augmente quand battery diminue
            batteryColor.g = (Uint8)(255 * ratio);          // G diminue quand battery diminue
            batteryColor.b = 0;
        }

        SDL_SetRenderDrawColor(renderer, batteryColor.r, batteryColor.g, batteryColor.b, 255);
        SDL_RenderFillRect(renderer, &batteryBar);

        // Texte %
        char text[20];
        sprintf(text, "%.0f%%", battery);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, text, white);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect textRect = {x + batteryWidth / 2 - surface->w / 2, y - surface->h - 5, surface->w, surface->h};
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