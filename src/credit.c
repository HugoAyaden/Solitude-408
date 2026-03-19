#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


void afficher_credits(SDL_Renderer *renderer, SDL_Window *window)
{
    TTF_Font *fontTitre = TTF_OpenFont("./assets/font/VCR.ttf", 100);
    TTF_Font *fontSousTitre = TTF_OpenFont("./assets/font/VCR.ttf", 40);
    TTF_Font *fontTexte = TTF_OpenFont("./assets/font/VCR.ttf", 28);
    if (!fontTexte || !fontTitre || !fontSousTitre)
    {
        printf("Erreur police\n");
        return ;
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
        "Projet de L2 informatique 2025-2026",
        " ",
        " ",
        "Developpeur :",
        " ",
        "Louay AMARA",
        "Hugo AYADEN",
        "Mathis DOS SANTOS",
        "Bastien LEFEVRE TAUGOURDEAU",
        " ",
        " ",
        "Outils utilisés :",
        " ",
        "SDL2 (fenêtre du jeu)",
        "SDL2_image",
        "SDL2_ttf",
        "Compilateur GCC",
        "Langage C",
        "Gimp (images)",
        "Audacity (sons)",
        " ",
        " ",
        "Musique :",
        "A definir",
        " ",
        "Merci d'avoir joue !",
        NULL};

    SDL_Color color = {147, 112, 219, 255}; //purple pour respecter la DA 

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
            if (strcmp(credits[i], "Developpeur :") == 0)
                currentFont = fontSousTitre;
            if (strcmp(credits[i],  "Outils utilisés :") == 0)
                currentFont = fontSousTitre;
            if (strcmp(credits[i],  "Projet de L2 informatique 2025-2026") == 0)
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

// ==========================
// MAIN DE TEST
// ==========================
int main()
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
}