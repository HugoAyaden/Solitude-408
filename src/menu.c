#include <game.h>

// Static variables keep assets in memory for this module only
static SDL_Texture* bgTexture = NULL;
static SDL_Texture* titleText = NULL;
static SDL_Rect titleRect;
static MenuButton buttons[4];
static bool assetsLoaded = false;

void init_menu(SDL_Renderer* renderer, TTF_Font* mainFont, TTF_Font* titleFont) {
    if (assetsLoaded) return;

    // Load Background 
    bgTexture = IMG_LoadTexture(renderer, "assets/background.png");    
    SDL_Color white  = {255, 255, 255, 255};
    SDL_Color purple = {147, 112, 219, 255};

    // 1. Title Setup - Only size; position in render_menu
    SDL_Surface* titleSurf = TTF_RenderText_Blended(titleFont, "SOLITUDE 408", purple);
    titleText = SDL_CreateTextureFromSurface(renderer, titleSurf);
    titleRect.w = titleSurf->w;
    titleRect.h = titleSurf->h;
    SDL_FreeSurface(titleSurf);

    // 2. Buttons Setup - Only size; coordinates in render_menu
    const char* labels[] = {"NEW GAME", "LOAD GAME", "SETTINGS", "EXIT GAME"};

    for (int i = 0; i < 4; i++) {
        SDL_Surface* surf = TTF_RenderText_Blended(mainFont, labels[i], white);
        buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surf);
        buttons[i].label = labels[i];
        buttons[i].rect.w = surf->w;
        buttons[i].rect.h = surf->h;
        SDL_FreeSurface(surf);
    }

    assetsLoaded = true;
}

void render_menu(SDL_Renderer* renderer) {
    // Ensure symmetry after resolution changes
    int sw, sh;
    SDL_GetRendererOutputSize(renderer, &sw, &sh);

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    SDL_Point mousePos = {mx, my};
    SDL_Color purple = {147, 112, 219, 255};

    // 1. Background - Scales to fill screen
    if (bgTexture) {
        SDL_SetTextureColorMod(bgTexture, 180, 150, 200);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    }

    // 2. Dynamic Title and Decoration
    titleRect.x = (sw / 2) - (titleRect.w / 2);     // Center horizontally
    titleRect.y = sh / 12;                          // 1/12th down from top
    SDL_RenderCopy(renderer, titleText, NULL, &titleRect);
    
    SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, 80);
    // Underline follows the centered title dynamically
    SDL_RenderDrawLine(renderer, titleRect.x - 20, titleRect.y + titleRect.h + 5, 
                                 titleRect.x + titleRect.w + 20, titleRect.y + titleRect.h + 5);


    // 3. Dynamic Interactive Buttons
    int buttonColumnX = sw / 15; //// Calculate column position 
    int startY = sh / 2 - 50;    // Centered vertically in the lower half
    int spacingY = sh / 14;      // Spacing scales with screen height

    for (int i = 0; i < 4; i++) {
        // Update button hitboxes every frame to match current resolution
        buttons[i].rect.x = buttonColumnX;
        buttons[i].rect.y = startY + (i * spacingY);

        if (SDL_PointInRect(&mousePos, &buttons[i].rect)) {
            // Hover: Purple color & underline
            SDL_SetTextureColorMod(buttons[i].texture, purple.r, purple.g, purple.b);
            
            SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, 255);
            SDL_RenderDrawLine(renderer, 
                buttons[i].rect.x, buttons[i].rect.y + buttons[i].rect.h + 2, 
                buttons[i].rect.x + buttons[i].rect.w, buttons[i].rect.y + buttons[i].rect.h + 2);

        } else {
            // Normal: White text
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