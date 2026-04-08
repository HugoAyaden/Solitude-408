/**
 * \file transitionNuit.c
 * \brief Implémentation de l'animation de transition entre les nuits
 * \author Bastien LEFEVRE TAUGOURDEAU
 * \version 1.0
 * \date 23/03/2026
 *
 * 
 * Une animation qui permet d'afficher le changement de nuit
 * pour comprendre qu'on passe à la nuit suivante (on a donc gagné la nuit -1)
 */


#include "constantes.h"

int transitionNuit(SDL_Renderer *renderer, SDL_Window *window, int nuitActuelle)
{
    TTF_Font *font = TTF_OpenFont("./assets/font/VCR.ttf", 60);
    if (!font)
    {
        printf("Erreur police\n");
        return-1;
    }

    SDL_Color colorFont = {147, 112, 219, 255};
    char texte[50];
    sprintf(texte, "NIGHT %d", nuitActuelle);

    SDL_Surface *surface = TTF_RenderText_Solid(font, texte, colorFont);
    if (!surface)
    {
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        TTF_CloseFont(font);
        return -1;
    }

    int largeur, hauteur;
    SDL_GetWindowSize(window, &largeur, &hauteur);

    SDL_Rect rect;
    rect.w = 0;
    rect.h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    rect.x = (largeur - rect.w) / 2;
    rect.y = (hauteur - rect.h) / 2;

    SDL_Event event;

    // Fade in
    for (int alpha = 0; alpha <= 255; alpha += 5)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_Delay(1500);

    // Fade out
    for (int alpha = 255; alpha >= 0; alpha -= 5)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    return 1;
}
