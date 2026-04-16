/**
 * \file credits.c
 * \brief Credits rendering function
 * \author Bastien LEFEVRE TAUGOURDEAU
 * \version 1.1
 * \date 19/03/2026
 *
 */

#include "../lib/constantes.h"

int render_credits(SDL_Renderer *renderer, SDL_Window *window)
{
    TTF_Font *fontTitre = TTF_OpenFont("./assets/font/VCR.ttf", 100);
    TTF_Font *fontSousTitre = TTF_OpenFont("./assets/font/VCR.ttf", 40);
    TTF_Font *fontTexte = TTF_OpenFont("./assets/font/VCR.ttf", 28);
    
    if (!fontTexte || !fontTitre || !fontSousTitre)
    {
        printf("Erreur police\n");
        return 0; // Failure
    }

    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    SDL_Surface *bgSurface = IMG_Load("./assets/img/background/credits.jpg");
    if (!bgSurface)
    {
        printf("Erreur chargement image\n");
        return 0;
    }
    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    const char *credits[] = {
        "Solitude 408", " ", " ",
        "L2 Computer Science Project 2025-2026", " ", " ",
        "Developers:", " ",
        "Louay AMARA", "Hugo AYADEN", "Mathis DOS SANTOS", "Bastien LEFEVRE TAUGOURDEAU",
        " ", " ",
        "Tools Used:", " ",
        "SDL2 (game window)", "SDL2_image (rendering)", "SDL2_ttf (text)", "SDL2_mixer (audio)", "GCC Compiler",
        "C Language", "GIMP (images)", "Audacity (sounds)", "Blender (3D)",
        " ", " ",
        "Music:", "A.C","BloodPixelHero"," ",
        "Thanks for playing!",
        NULL};

    SDL_Color color = {147, 112, 219, 255};

    int y = height;
    int quit = 0;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            // If user clicks the X button, shut down the whole program
            if (event.type == SDL_QUIT)
                exit(0); 

            // Allow skipping with ESC or Mouse Click
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
                quit = 1;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        int currentY = y;

        for (int i = 0; credits[i] != NULL; i++)
        {
            TTF_Font *currentFont = fontTexte;

            if (strcmp(credits[i], "Solitude408") == 0)
                currentFont = fontTitre;
            else if (strcmp(credits[i], "Developers:") == 0 || 
                     strcmp(credits[i], "Tools Used:") == 0 ||
                     strcmp(credits[i], "L2 Computer Science Project 2025-2026") == 0)
                currentFont = fontSousTitre;

            SDL_Surface *surface = TTF_RenderText_Solid(currentFont, credits[i], color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_Rect rect;
            rect.w = surface->w;
            rect.h = surface->h;
            rect.x = (width - rect.w) / 2;
            rect.y = currentY;

            SDL_RenderCopy(renderer, texture, NULL, &rect);

            currentY += 50; 
            
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        y -= 1; // Scroll speed

        // If the last line of credits has passed the top of the screen, stop
        if (currentY < 0) 
            quit = 1;

        SDL_Delay(16); 
    }

    // Cleanup before returning
    SDL_DestroyTexture(background);
    TTF_CloseFont(fontTexte);
    TTF_CloseFont(fontSousTitre);
    TTF_CloseFont(fontTitre);

    return 1; // Success
}