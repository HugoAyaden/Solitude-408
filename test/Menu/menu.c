#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NUM_BUTTONS 5

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    const char* label;
} MenuButton;

int main(int argc, char* argv[]) {
    // --- 1. INITIALIZATION ---
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    if (TTF_Init() == -1) return 1;
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) return 1;
    SDL_Window* window2 = NULL;
    SDL_Window* window = SDL_CreateWindow("Solitude 408", 
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_FULLSCREEN);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED);

    // --- 2. ASSETS ---
    // Background - replace "background.jpg" with your actual space station image filename
    SDL_Texture* bgTexture = IMG_LoadTexture(renderer, "background.jpeg");
    
    // Font setup
    TTF_Font* mainFont = TTF_OpenFont("PF.otf", 28);
    TTF_Font* titleFont = TTF_OpenFont("PF.otf", 72);
    if (!mainFont || !titleFont) {
        printf("Font error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color white = {0, 255, 255, 255};
    SDL_Color orange = {255, 140, 0, 255};

    // Create Title Texture
    SDL_Surface* titleSurf = TTF_RenderText_Blended(titleFont, "SOLITUDE 408", orange);
    SDL_Texture* titleText = SDL_CreateTextureFromSurface(renderer, titleSurf);
    SDL_Rect titleRect = { 80, 60, titleSurf->w, titleSurf->h };
    SDL_FreeSurface(titleSurf);

    // Create Menu Buttons
    const char* labels[] = {"NEW GAME", "LOAD GAME", "OPTIONS", "VIEW CREDITS", "EXIT GAME"};
    MenuButton buttons[NUM_BUTTONS];

    for (int i = 0; i < NUM_BUTTONS; i++) {
        SDL_Surface* surf = TTF_RenderText_Blended(mainFont, labels[i], white);
        buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surf);
        buttons[i].label = labels[i];
        
        // Positioning buttons on the left, vertically stacked
        buttons[i].rect.x = 100;
        buttons[i].rect.y = 320 + (i * 60);
        buttons[i].rect.w = surf->w;
        buttons[i].rect.h = surf->h;
        SDL_FreeSurface(surf);
    }

    // --- 3. MAIN LOOP ---
    bool running = true;
    SDL_Event event;

    while (running) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        SDL_Point mousePos = {mx, my};

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                for (int i = 0; i < NUM_BUTTONS; i++) {
                    if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                        if (i == 0) window2 = SDL_CreateWindow("NEW GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);
                        if (i == 4) running = false; // Exit Game
                    }
                }
            }
        }

        // --- RENDERING ---
        SDL_RenderClear(renderer);

        // Draw Background (fills screen)
        if (bgTexture) SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Draw Title and underline
        SDL_RenderCopy(renderer, titleText, NULL, &titleRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50); // Faint line
        SDL_RenderDrawLine(renderer, 80, 160, 450, 160);

        // Draw Buttons
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                // Hover State: Orange Text + Selection Triangle
                SDL_SetTextureColorMod(buttons[i].texture, orange.r, orange.g, orange.b);
                
                SDL_Point triangle[] = {
                    {buttons[i].rect.x - 35, buttons[i].rect.y + 10},
                    {buttons[i].rect.x - 20, buttons[i].rect.y + (buttons[i].rect.h / 2)},
                    {buttons[i].rect.x - 35, buttons[i].rect.y + buttons[i].rect.h - 10},
                    {buttons[i].rect.x - 35, buttons[i].rect.y + 10}
                };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLines(renderer, triangle, 4);
            } else {
                // Normal State: White Text
                SDL_SetTextureColorMod(buttons[i].texture, 255, 255, 255);
            }
            SDL_RenderCopy(renderer, buttons[i].texture, NULL, &buttons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    // --- 4. CLEANUP ---
    for (int i = 0; i < NUM_BUTTONS; i++) SDL_DestroyTexture(buttons[i].texture);
    SDL_DestroyTexture(titleText);
    SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(mainFont);
    TTF_CloseFont(titleFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}