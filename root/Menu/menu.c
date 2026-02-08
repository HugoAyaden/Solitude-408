#include "../game.h"

// Static variables keep assets in memory for this module only
static SDL_Texture* bgTexture = NULL;
static SDL_Texture* titleText = NULL;
static SDL_Rect titleRect;
static MenuButton buttons[4];
static bool assetsLoaded = false;

void init_menu(SDL_Renderer* renderer, TTF_Font* mainFont, TTF_Font* titleFont) {
    if (assetsLoaded) return;

    // Load Background relative to ROOT folder
    bgTexture = IMG_LoadTexture(renderer, "Menu/background.png");
    
    SDL_Color white  = {255, 255, 255, 255};
    SDL_Color purple = {147, 112, 219, 255};

    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    // 1. Centered Title Setup - Pushed down from the top edge
    SDL_Surface* titleSurf = TTF_RenderText_Blended(titleFont, "SOLITUDE 408", purple);
    titleText = SDL_CreateTextureFromSurface(renderer, titleSurf);
    // X is centered, Y is pushed to 100 to avoid sticking to the window frame
    titleRect = (SDL_Rect){ (w / 2) - (titleSurf->w / 2), 100, titleSurf->w, titleSurf->h };
    SDL_FreeSurface(titleSurf);

    // 2. Buttons Setup - Positioned in the middle-left window area
    const char* labels[] = {"NEW GAME", "LOAD GAME", "SETTINGS", "EXIT GAME"};

    for (int i = 0; i < 4; i++) {
        SDL_Surface* surf = TTF_RenderText_Blended(mainFont, labels[i], white);
        buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surf);
        buttons[i].label = labels[i];
        
        // Aligned to the left side of the inner window
        buttons[i].rect.x = 100; 
        // Shifted up to be vertically centered in the left half
        buttons[i].rect.y = (h / 2) - 100 + (i * 75); 
        buttons[i].rect.w = surf->w;
        buttons[i].rect.h = surf->h;
        SDL_FreeSurface(surf);
    }

    assetsLoaded = true;
}

void render_menu(SDL_Renderer* renderer) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    SDL_Point mousePos = {mx, my};
    SDL_Color purple = {147, 112, 219, 255};

    // 1. Background
    if (bgTexture) {
        SDL_SetTextureColorMod(bgTexture, 180, 150, 200);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    }

    // 2. Title and Decoration
    SDL_RenderCopy(renderer, titleText, NULL, &titleRect);
    SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, 80);
    // Underline follows the centered title
    SDL_RenderDrawLine(renderer, titleRect.x - 20, titleRect.y + titleRect.h + 5, 
                                 titleRect.x + titleRect.w + 20, titleRect.y + titleRect.h + 5);

    // 3. Interactive Buttons
    for (int i = 0; i < 4; i++) {
        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
            // Hover state: Apply purple color mod and draw underline
            SDL_SetTextureColorMod(buttons[i].texture, purple.r, purple.g, purple.b);
            
            SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, 255);
            SDL_RenderDrawLine(renderer, 
                buttons[i].rect.x, buttons[i].rect.y + buttons[i].rect.h + 2, 
                buttons[i].rect.x + buttons[i].rect.w, buttons[i].rect.y + buttons[i].rect.h + 2);

        } else {
            // Normal state: Reset to white text
            SDL_SetTextureColorMod(buttons[i].texture, 255, 255, 255);
        }
        SDL_RenderCopy(renderer, buttons[i].texture, NULL, &buttons[i].rect);
    }
}

int check_menu_click(SDL_Point mousePos) {
    for (int i = 0; i < 4; i++) {
        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
            return i;
        }
    }
    return -1;
}

void cleanup_menu() {
    for (int i = 0; i < 4; i++) {
        if (buttons[i].texture) SDL_DestroyTexture(buttons[i].texture);
    }
    if (titleText) SDL_DestroyTexture(titleText);
    if (bgTexture) SDL_DestroyTexture(bgTexture);
}