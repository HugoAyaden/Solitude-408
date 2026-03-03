#include "menu_pause.h"
#include <stdio.h>

#define MENU_ITEM_COUNT 4
#define ITEM_SPACING 70

menu_pause_result_t menu_pause(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *titleFont)
{
    const char *menu_items[MENU_ITEM_COUNT] = {
        "Reprendre",
        "Settings",
        "Credits",
        "Exit"
    };

    SDL_Rect itemRects[MENU_ITEM_COUNT];
    int selected = -1; // -1 = rien sélectionné (souris)
    SDL_Event event;
    int running = 1;

    int windowW, windowH;
    SDL_GetRendererOutputSize(renderer, &windowW, &windowH);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return MENU_EXIT;

            // === CLAVIER ===
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return MENU_CONTINUE;

                    case SDLK_UP:
                        if (selected < 0) selected = 0;
                        selected--;
                        if (selected < 0) selected = MENU_ITEM_COUNT - 1;
                        break;

                    case SDLK_DOWN:
                        if (selected < 0) selected = 0;
                        selected++;
                        if (selected >= MENU_ITEM_COUNT) selected = 0;
                        break;

                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        if (selected >= 0)
                            running = 0;
                        break;
                }
            }

            // === SOURIS - SURVOL ===
            if (event.type == SDL_MOUSEMOTION)
            {
                int mx = event.motion.x;
                int my = event.motion.y;

                selected = -1;
                for (int i = 0; i < MENU_ITEM_COUNT; i++)
                {
                    if (SDL_PointInRect(&(SDL_Point){mx, my}, &itemRects[i]))
                    {
                        selected = i;
                        break;
                    }
                }
            }

            // === SOURIS - CLIC ===
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT && selected >= 0)
                {
                    running = 0;
                }
            }
        }

        // =========================
        // RENDER
        // =========================

        // Fond semi-transparent
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_RenderFillRect(renderer, NULL);

        // Calcul du point de départ vertical (centré)
        int totalHeight = MENU_ITEM_COUNT * ITEM_SPACING;
        int startY = (windowH / 2) - (totalHeight / 2);

        for (int i = 0; i < MENU_ITEM_COUNT; i++)
        {
            SDL_Color color = (i == selected)
                ? (SDL_Color){255, 0, 0, 255}
                : (SDL_Color){255, 255, 255, 255};

            SDL_Surface *surface = TTF_RenderText_Solid(font, menu_items[i], color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            int w, h;
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);

            SDL_Rect rect = {
                (windowW / 2) - (w / 2),
                startY + i * ITEM_SPACING,
                w,
                h
            };

            itemRects[i] = rect;

            SDL_RenderCopy(renderer, texture, NULL, &rect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Retour résultat
    switch (selected)
    {
        case 0: return MENU_CONTINUE;
        case 1: return MENU_SETTINGS;
        case 2: return MENU_CREDITS;
        case 3: return MENU_EXIT;
    }

    return MENU_NONE;
}