#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>


// 1. Define a Button structure
typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    const char* text; // If using SDL_ttf later
    bool hovered;
} Button;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Solitude 408", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // 2. Load your background image
    SDL_Texture* background = IMG_LoadTexture(renderer, "background.jpeg"); 

    // 3. Initialize Menu Buttons (Matching your screenshot)
    const char* labels[] = {"NEW GAME", "LOAD GAME", "OPTIONS", "VIEW CREDITS", "EXIT GAME"};
    int numButtons = 5;
    Button menuButtons[5];

    for (int i = 0; i < numButtons; i++) {
        menuButtons[i].rect = (SDL_Rect){ .x = 100, .y = 300 + (i * 50), .w = 200, .h = 40 };
        menuButtons[i].hovered = false;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        SDL_Point mousePos = {mx, my};

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                for (int i = 0; i < numButtons; i++) {
                    if (SDL_PointInRect(&mousePos, &menuButtons[i].rect)) {
                        printf("Clicked: %s\n", labels[i]);
                        if (i == 4) running = false; // Exit Game logic
                    }
                }
            }
        }

        // --- Rendering ---
        SDL_RenderClear(renderer);

        // Draw Background
        SDL_RenderCopy(renderer, background, NULL, NULL);

        // Draw Buttons
        for (int i = 0; i < numButtons; i++) {
            // Check Hover
            if (SDL_PointInRect(&mousePos, &menuButtons[i].rect)) {
                SDL_SetRenderDrawColor(renderer, 255, 100, 0, 100); // Orange hover tint
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50); // Faint white outline
            }
            
            // For now, drawing rectangles. Later, you'll use SDL_ttf for the text!
            SDL_RenderDrawRect(renderer, &menuButtons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}