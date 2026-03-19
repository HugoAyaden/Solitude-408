#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// ==========================
// Fonction des crédits
// ==========================
void afficher_credits(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font)
{
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    SDL_Surface *bgSurface = IMG_Load("background.png");
    if (!bgSurface) {
        printf("Erreur chargement image\n");
        return;
    }
    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);


    const char *credits[] = {
        " ",
        "Solitude408",
        " ",
        "Developpeur :",
        "Louay AMARA",
        "Hugo AYADEN",
        "Mathis DOS SANTOS",
        "Bastien LEFEVRE TAUGOURDEAU",
        " ",
        "Graphismes :",
        "A definir",
        " ",
        "Musique :",
        "A definir",
        " ",
        "Merci d'avoir joue !",
        NULL
    };

    SDL_Color color = {255, 255, 0, 255}; // jaune style Star Wars

    int y = WINDOW_HEIGHT; // départ en bas
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
            SDL_Surface *surface = TTF_RenderText_Solid(font, credits[i], color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_Rect rect;
            rect.w = surface->w;
            rect.h = surface->h;
            rect.x = (WINDOW_WIDTH - rect.w) / 2;
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
        SDL_DestroyTexture(background);
    }
}


// ==========================
// MAIN DE TEST
// ==========================
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    if (TTF_Init() == -1)
        return 1;

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("Credits",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800,
                                          600,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("./assets/font/VCR.ttf", 28);
    if (!font)
    {
        printf("Erreur police\n");
        return 1;
    }

    afficher_credits(renderer, window, font);

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}