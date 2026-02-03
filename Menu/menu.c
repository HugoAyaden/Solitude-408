#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

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

    // Fullscreen Desktop mode
    SDL_Window* window = SDL_CreateWindow("Solitude 408", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // --- 2. ASSETS ---
    SDL_Texture* bgTexture = IMG_LoadTexture(renderer, "background.jpeg");
    
    // Using the larger font sizes
    TTF_Font* mainFont = TTF_OpenFont("PF.otf", 36); 
    TTF_Font* titleFont = TTF_OpenFont("PF.otf", 90); 
    if (!mainFont || !titleFont) {
        printf("Font error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color white  = {255, 255, 255, 255};
    SDL_Color purple = {147, 112, 219, 255}; 
    SDL_Color darkPurple = {25, 10, 40, 255}; 

    // Title
    SDL_Surface* titleSurf = TTF_RenderText_Blended(titleFont, "SOLITUDE 408", purple);
    SDL_Texture* titleText = SDL_CreateTextureFromSurface(renderer, titleSurf);
    SDL_Rect titleRect = { 80, 60, titleSurf->w, titleSurf->h };
    SDL_FreeSurface(titleSurf);

    const char* labels[] = {"NEW GAME", "LOAD GAME", "OPTIONS", "VIEW CREDITS", "EXIT GAME"};
    MenuButton buttons[NUM_BUTTONS];

    for (int i = 0; i < NUM_BUTTONS; i++) {
        SDL_Surface* surf = TTF_RenderText_Blended(mainFont, labels[i], white);
        buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surf);
        buttons[i].label = labels[i];
        
        buttons[i].rect.x = 100;
        buttons[i].rect.y = (h / 2) + (i * 75); // Vertical spacing for larger text
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
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) running = false;
            
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                for (int i = 0; i < NUM_BUTTONS; i++) {
                    if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                        printf("Action: %s\n", buttons[i].label);
                        if (i == 4) running = false; 
                    }
                }
            }
        }

        // --- RENDERING ---
        // Background color
        SDL_SetRenderDrawColor(renderer, darkPurple.r, darkPurple.g, darkPurple.b, 255);
        SDL_RenderClear(renderer);

        if (bgTexture) {
            SDL_SetTextureColorMod(bgTexture, 180, 150, 200); 
            SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
        }

        SDL_RenderCopy(renderer, titleText, NULL, &titleRect);
        
        // Static decorative underline for Title
        SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, 80); 
        SDL_RenderDrawLine(renderer, 80, 170, 550, 170);

        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
                // HOVER STATE
                SDL_SetTextureColorMod(buttons[i].texture, purple.r, purple.g, purple.b);
                
                // Draw Triangle
                SDL_Point triangle[] = {
                    {buttons[i].rect.x - 45, buttons[i].rect.y + 15},
                    {buttons[i].rect.x - 25, buttons[i].rect.y + (buttons[i].rect.h / 2)},
                    {buttons[i].rect.x - 45, buttons[i].rect.y + buttons[i].rect.h - 15},
                    {buttons[i].rect.x - 45, buttons[i].rect.y + 15}
                };
                SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, 255);
                SDL_RenderDrawLines(renderer, triangle, 4);

                // DRAW UNDERLINE
                SDL_RenderDrawLine(renderer, 
                    buttons[i].rect.x, buttons[i].rect.y + buttons[i].rect.h + 2, 
                    buttons[i].rect.x + buttons[i].rect.w, buttons[i].rect.y + buttons[i].rect.h + 2);

            } else {
                // NORMAL STATE
                SDL_SetTextureColorMod(buttons[i].texture, 255, 255, 255);
            }
            SDL_RenderCopy(renderer, buttons[i].texture, NULL, &buttons[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    // --- 4. CLEANUP ---
    for (int i = 0; i < NUM_BUTTONS; i++) SDL_DestroyTexture(buttons[i].texture);
    SDL_DestroyTexture(titleText);
    if (bgTexture) SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(mainFont);
    TTF_CloseFont(titleFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}