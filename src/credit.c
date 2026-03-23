#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

/**
 * \file credit.c
 * \brief Affichage des credits
 * \author Bastien LEFEVRE TAUGOURDEAU
 * \version 1.0
 * \date 19/03/2026
 *
 */

/**
 * \brief Affiche les crédits du jeu avec un défilement vertical.
 *
 * Cette fonction affiche un écran de crédits avec un effet de
 * défilement du texte du bas vers le haut, similaire à celui
 * des films (style Star Wars). Un fond d'écran est affiché en
 * arrière-plan et certaines lignes peuvent être mises en valeur
 * avec une taille de police différente.
 *
 * L'affichage s'arrête lorsque tous les crédits sont sortis de
 * l'écran.
 *
 * \param renderer Le renderer SDL utilisé pour le rendu graphique.
 * \param window La fenêtre SDL utilisée pour récupérer la taille d'affichage.
 */
void afficher_credits(SDL_Renderer *renderer, SDL_Window *window)
{
    TTF_Font *fontTitre = TTF_OpenFont("./assets/font/VCR.ttf", 100);
    TTF_Font *fontSousTitre = TTF_OpenFont("./assets/font/VCR.ttf", 40);
    TTF_Font *fontTexte = TTF_OpenFont("./assets/font/VCR.ttf", 28);
    if (!fontTexte || !fontTitre || !fontSousTitre)
    {
        printf("Erreur police\n");
        return;
    }
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    SDL_Surface *bgSurface = IMG_Load("./assets/img/background/background.png");
    if (!bgSurface)
    {
        printf("Erreur chargement image\n");
        return;
    }
    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    const char *credits[] = {
        "Solitude408",
        " ",
        " ",
        "L2 Computer Science Project 2025-2026",
        " ",
        " ",
        "Developers:",
        " ",
        "Louay AMARA",
        "Hugo AYADEN",
        "Mathis DOS SANTOS",
        "Bastien LEFEVRE TAUGOURDEAU",
        " ",
        " ",
        "Tools Used:",
        " ",
        "SDL2 (game window)",
        "SDL2_image",
        "SDL2_ttf",
        "GCC Compiler",
        "C Language",
        "GIMP (images)",
        "Audacity (sounds)",
        "Blender (3D)",
        " ",
        " ",
        "Music:",
        "To be defined",
        " ",
        "Thanks for playing!",
        NULL};

    SDL_Color color = {147, 112, 219, 255}; // purple pour respecter la DA

    int y = height;
    int quit = 0;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
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
            if (strcmp(credits[i], "Developers:") == 0)
                currentFont = fontSousTitre;
            if (strcmp(credits[i], "Tools Used:") == 0)
                currentFont = fontSousTitre;
            if (strcmp(credits[i], "L2 Computer Science Project 2025-2026") == 0)
                currentFont = fontSousTitre;

            SDL_Surface *surface = TTF_RenderText_Solid(currentFont, credits[i], color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_Rect rect;
            rect.w = surface->w;
            rect.h = surface->h;
            rect.x = (width - rect.w) / 2;
            rect.y = currentY;

            SDL_RenderCopy(renderer, texture, NULL, &rect);

            currentY += 50; // espace entre lignes

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        y -= 1; // vitesse de défilement

        if (currentY < 0) // quand tout est sorti de l'écran
            quit = 1;

        SDL_Delay(16); // ~60 FPS
    }
    SDL_DestroyTexture(background);
    TTF_CloseFont(fontTexte);
    TTF_CloseFont(fontSousTitre);
    TTF_CloseFont(fontTitre);
}

/*int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    if (TTF_Init() == -1)
        return 1;

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("Credits",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          0,
                                          0,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    afficher_credits(renderer, window); // la fonction à appeller

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}*/