/**
 * \file transitionNuit.c
 * \brief Between nights and winning screen transition animation
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.1
 * \date 23/03/2026
 *
 * 
 * Une animation qui permet d'afficher le changement de nuit
 * pour comprendre qu'on passe à la nuit suivante (on a donc gagné la nuit -1)
 */


#include "../lib/constantes.h"

SDL_Event event;
SDL_Texture *text = NULL;
SDL_Texture *chiffre = NULL;
SDL_Texture *chiffreNext = NULL;
TTF_Font *font = NULL;
SDL_Rect rect;
SDL_Rect rect2;
SDL_Rect rect3;
SDL_Rect winRect;


static int fade_in_chiffre_nuit(SDL_Renderer *renderer, SDL_Texture *text, SDL_Texture *chiffre){
    for (int alpha = 0; alpha <= 255; alpha += 5)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(text, alpha);
        SDL_SetTextureAlphaMod(chiffre, alpha);
        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_RenderCopy(renderer, chiffre, NULL, &rect2);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 1;
}

static int fade_in_next(SDL_Renderer *renderer, SDL_Texture *chiffreNext){
    for (int alpha = 0; alpha <= 255; alpha += 5)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(text, 255);
        SDL_SetTextureAlphaMod(chiffre, 255);
        SDL_SetTextureAlphaMod(chiffreNext, alpha);
        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_RenderCopy(renderer, chiffre, NULL, &rect2);
        SDL_RenderCopy(renderer, chiffreNext, NULL, &rect3);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 1;
    
}

static int fade_out_chiffre(SDL_Renderer *renderer,SDL_Texture *chiffre){
    for (int alpha = 255; alpha >= 0; alpha -= 5)
    {
         while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(text, 255);
        SDL_SetTextureAlphaMod(chiffre, alpha);
        SDL_SetTextureAlphaMod(chiffreNext, 255);
        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_RenderCopy(renderer, chiffre, NULL, &rect2);
        SDL_RenderCopy(renderer, chiffreNext, NULL, &rect3);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 1;
}

static int fade_out(SDL_Renderer *renderer, SDL_Texture *text, SDL_Texture *chiffre){
    for (int alpha = 255; alpha >= 0; alpha -= 5)
    {
         while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(text, alpha);
        SDL_SetTextureAlphaMod(chiffreNext, alpha);
        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_RenderCopy(renderer, chiffreNext, NULL, &rect3);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 1;
}

/**
 * \brief Fades in victory text.
 *
 * \param renderer SDL renderer.
 * \param winText "YOU WIN" texture.
 * \return 1 on success, -1 if quit event detected.
 */
static int fade_in_text(SDL_Renderer *renderer, SDL_Texture *winText)
{
    for (int alpha = 0; alpha <= 255; alpha += 5)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(winText, alpha);
        SDL_RenderCopy(renderer, winText, NULL, &winRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 1;
}

/**
 * \brief Fades out victory text.
 *
 * \param renderer SDL renderer.
 * \param winText "YOU WIN" texture.
 * \return 1 on success, -1 if quit event detected.
 */
static int fade_out_text(SDL_Renderer *renderer, SDL_Texture *winText)
{
    for (int alpha = 255; alpha >= 0; alpha -= 5)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return -1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(winText, alpha);
        SDL_RenderCopy(renderer, winText, NULL, &winRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 1;
}

int transitionWin(SDL_Renderer *renderer, SDL_Window *window){
    font = TTF_OpenFont("./assets/font/VCR.ttf", 60);
    if (!font)
    {
        printf("Erreur police\n");
        return-1;
    }
    SDL_Color colorFont = {147, 112, 219, 255};
    char texte[50];
    sprintf(texte, "YOU WIN");

    SDL_Surface *surface = TTF_RenderText_Solid(font, texte, colorFont);
    if (!surface)
    {
        TTF_CloseFont(font);
        return -2;
    }

    SDL_Texture *winText = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!winText)
    {
        TTF_CloseFont(font);
        return -3;
    }

    int largeur, hauteur;
    SDL_GetWindowSize(window, &largeur, &hauteur);
    winRect.w = 0;
    winRect.h = 0;
    SDL_QueryTexture(winText, NULL, NULL, &winRect.w, &winRect.h);
    winRect.x = (largeur - winRect.w) / 2;
    winRect.y = (hauteur - winRect.h) / 2;

    // Fade in
    fade_in_text(renderer, winText);
    
    SDL_Delay(2000); // Hold the "YOU WIN" message for a moment

    // Fade out
    fade_out_text(renderer, winText);

    SDL_DestroyTexture(winText);
    TTF_CloseFont(font);
    return 1;
}

int transitionNuit(SDL_Renderer *renderer, SDL_Window *window, int nuitActuelle)
{
    font = TTF_OpenFont("./assets/font/VCR.ttf", 60);
    if (!font)
    {
        printf("Erreur police\n");
        return-1;
    }

    SDL_Color colorFont = {147, 112, 219, 255};
    int following_night = nuitActuelle + 1;
    char texte[50];
    char nightTexte[10];
    char nextNight[30];
    sprintf(texte, "NIGHT ");
    sprintf(nightTexte, "%d", nuitActuelle);
    sprintf(nextNight, "%d", following_night);

    SDL_Surface *surface = TTF_RenderText_Solid(font, texte, colorFont);
    SDL_Surface *surface2 = TTF_RenderText_Solid(font, nightTexte, colorFont);
    SDL_Surface *surface3 = TTF_RenderText_Solid(font, nextNight, colorFont);
    if (!surface)
    {
        TTF_CloseFont(font);
        return -1;
    }

    text = SDL_CreateTextureFromSurface(renderer, surface);
    chiffre = SDL_CreateTextureFromSurface(renderer, surface2);
    chiffreNext = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_FreeSurface(surface);

    if (!text || !chiffre)
    {
        TTF_CloseFont(font);
        return -1;
    }

    int largeur, hauteur;
    SDL_GetWindowSize(window, &largeur, &hauteur);

    rect.w = 0;
    rect.h = 0;
    rect2.w = 0;
    rect2.h = 0;
    rect3.w = 0;
    rect3.h = 0;
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    SDL_QueryTexture(chiffre, NULL, NULL, &rect2.w, &rect2.h);
    SDL_QueryTexture(chiffreNext, NULL, NULL, &rect3.w, &rect3.h);

    rect.x = (largeur - rect.w) / 2;
    rect.y = (hauteur - rect.h) / 2;
    rect2.x = (largeur - rect.w) / 2 + rect.w + 10;
    rect2.y = (hauteur - rect.h) / 2;
    rect3.x = (largeur - rect.w) / 2 + rect.w + 10;
    rect3.y = (hauteur - rect.h) / 2 + 100;

    // Fade in
    fade_in_chiffre_nuit(renderer, text, chiffre);
    fade_in_next(renderer, chiffreNext);

    SDL_Delay(1000);

    //scroll up
    for (int i = 0; i < 100; i++)
    {
        rect2.y = (hauteur - rect2.h) / 2 - i;
        rect3.y = (hauteur - rect3.h) / 2 + 100 - i;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetTextureAlphaMod(text, 255);
        SDL_SetTextureAlphaMod(chiffre, 255);
        SDL_SetTextureAlphaMod(chiffreNext, 255);
        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_RenderCopy(renderer, chiffre, NULL, &rect2);
        SDL_RenderCopy(renderer, chiffreNext, NULL, &rect3);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
     }
     SDL_Delay(1000);
        

    // Fade out
    fade_out_chiffre(renderer, chiffre);
    fade_out(renderer, text, chiffreNext);

    SDL_DestroyTexture(text);
    SDL_DestroyTexture(chiffre);
    SDL_DestroyTexture(chiffreNext);
    TTF_CloseFont(font);
    return 1;
}


/*
int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    if (TTF_Init() == -1)
        return 1;

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("transition",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          0,
                                          0,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    transitionNuit(renderer, window, 2);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}*/
