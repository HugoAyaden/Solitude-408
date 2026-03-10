#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

/**
 * \file systeme_batterie.c
 * \brief Affichage et gestion d'énergie de la batterie
 * \author Bastien LEFEVRE TAUGOURDEAU
 * \version 1.0
 * \date 10/03/2026
 *
 */

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static int porteGaucheActive = 0;
static int porteDroiteActive = 0;
static int lumiereGaucheActive = 0;
static int lumiereDroiteActive = 0;

/**
 * \brief Dessine un bouton interactif avec un texte.
 *
 * Cette fonction dessine un rectangle représentant un bouton,
 * applique une couleur différente selon son état actif ou non,
 * puis affiche un texte centré à l'intérieur.
 *
 * \param renderer Le renderer SDL utilisé pour dessiner.
 * \param font La police utilisée pour afficher le texte.
 * \param rect Rectangle définissant la position et la taille du bouton.
 * \param active Indique si le bouton est actif (1) ou non (0).
 * \param label Texte affiché sur le bouton.
 */

static void drawButton(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label)
{
    if (active)
        SDL_SetRenderDrawColor(renderer, 200, 40, 40, 255);
    else
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);

    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, label, textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect;
    textRect.w = surface->w;
    textRect.h = surface->h;
    textRect.x = rect.x + (rect.w - textRect.w) / 2;
    textRect.y = rect.y + (rect.h - textRect.h) / 2;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * \brief Initialise l'état des boutons.
 *
 * Tous les boutons (portes et lumières) sont désactivés
 * au lancement du jeu.
 */
void buttons_init()
{
    porteGaucheActive = 0;
    porteDroiteActive = 0;
    lumiereGaucheActive = 0;
    lumiereDroiteActive = 0;
}
/**
 * \brief Gère les événements liés aux boutons.
 *
 * Cette fonction détecte les clics de souris et active
 * ou désactive les boutons correspondants (portes et lumières).
 *
 * \param event Événement SDL reçu.
 * \param window Fenêtre SDL utilisée pour récupérer la taille.
 */
void buttons_handleEvent(SDL_Event *event, SDL_Window *window)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    int buttonW = 60;
    int buttonH = 60;
    int spacing = 20;

    SDL_Rect btnPorteGauche = {spacing, h / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing, h / 2 + 10, buttonW, buttonH};

    SDL_Rect btnPorteDroite = {w - buttonW - spacing, h / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {w - buttonW - spacing, h / 2 + 10, buttonW, buttonH};

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};

    if (SDL_PointInRect(&p, &btnPorteGauche))
        porteGaucheActive = !porteGaucheActive;

    if (SDL_PointInRect(&p, &btnPorteDroite))
        porteDroiteActive = !porteDroiteActive;

    if (SDL_PointInRect(&p, &btnLumiereGauche))
        lumiereGaucheActive = !lumiereGaucheActive;

    if (SDL_PointInRect(&p, &btnLumiereDroite))
        lumiereDroiteActive = !lumiereDroiteActive;
}
/**
 * \brief Affiche tous les boutons de contrôle.
 *
 * Dessine les boutons des portes et des lumières
 * sur les côtés gauche et droit de l'écran.
 *
 * \param renderer Renderer SDL utilisé pour le dessin.
 * \param font Police utilisée pour les labels des boutons.
 * \param windowW Largeur de la fenêtre.
 * \param windowH Hauteur de la fenêtre.
 */
void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{
    int buttonW = 60;
    int buttonH = 60;
    int spacing = 20;

    SDL_Rect btnPorteGauche = {spacing, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing, windowH / 2 + 10, buttonW, buttonH};

    SDL_Rect btnPorteDroite = {windowW - buttonW - spacing, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {windowW - buttonW - spacing, windowH / 2 + 10, buttonW, buttonH};

    drawButton(renderer, font, btnPorteGauche, porteGaucheActive, "DOOR");
    drawButton(renderer, font, btnPorteDroite, porteDroiteActive, "DOOR");
    drawButton(renderer, font, btnLumiereGauche, lumiereGaucheActive, "LIGHT");
    drawButton(renderer, font, btnLumiereDroite, lumiereDroiteActive, "LIGHT");
}
/**
 * \brief Retourne le nombre de portes activées.
 *
 * \return Nombre de portes actuellement fermées.
 */
int buttons_getDoorCount()
{
    return porteGaucheActive + porteDroiteActive;
}

/**
 * \brief Retourne le nombre de lumières activées.
 *
 * \return Nombre de lumières actuellement allumées.
 */
int buttons_getLightCount()
{
    return lumiereGaucheActive + lumiereDroiteActive;
}

/**
 * \brief Gestion globale des événements du jeu.
 *
 * Transmet les événements SDL aux systèmes
 * concernés (ici les boutons).
 *
 * \param event Événement SDL reçu.
 * \param window Fenêtre SDL utilisée.
 */
void game_handleEvent(SDL_Event *event, SDL_Window *window)
{
    buttons_handleEvent(event, window);
}

#define BATTERY_DURATION 420.0f

static float battery = 100.0f;
/**
 * \brief Initialise la batterie du joueur.
 *
 * La batterie commence toujours à 100%.
 */
void battery_init()
{
    battery = 100.0f;
}
/**
 * \brief Initialise les systèmes principaux du jeu.
 *
 * Initialise la batterie et les boutons.
 */
void game_init()
{
    battery_init();
    buttons_init();
}

/**
 * \brief Met à jour le niveau de batterie.
 *
 * La consommation dépend du nombre de portes fermées
 * et de lumières activées.
 *
 * \param deltaTime Temps écoulé depuis la dernière frame.
 * \param doorCount Nombre de portes fermées.
 * \param lightCount Nombre de lumières allumées.
 */
void battery_update(float deltaTime, int doorCount, int lightCount)
{
    float drainRate = 100.0f / BATTERY_DURATION;

    if (doorCount == 2)
        drainRate *= 4.0f;
    else if (doorCount == 1)
        drainRate *= 2.0f;

    if (lightCount > 0)
        drainRate *= (1.0f + lightCount);

    battery -= drainRate * deltaTime;

    if (battery < 0)
        battery = 0;
}

/**
 * \brief Met à jour la logique du jeu.
 *
 * Met à jour l'état de la batterie en fonction
 * de l'utilisation des portes et lumières.
 *
 * \param deltaTime Temps écoulé depuis la dernière frame.
 */
void game_update(float deltaTime)
{
    int doorCount = buttons_getDoorCount();
    int lightCount = buttons_getLightCount();

    battery_update(deltaTime, doorCount, lightCount);
}

/**
 * \brief Affiche la barre de batterie à l'écran.
 *
 * Dessine une barre de batterie avec une couleur
 * variant du vert au rouge selon le niveau restant.
 *
 * \param renderer Renderer SDL utilisé pour dessiner.
 * \param font Police utilisée pour afficher le pourcentage.
 * \param windowW Largeur de la fenêtre.
 * \param windowH Hauteur de la fenêtre.
 */
void battery_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{
    const int batteryWidth = 150;
    const int batteryHeight = 40;
    const int capWidth = 10;
    const int margin = 20;

    int x = margin;
    int y = windowH - batteryHeight - margin;

    SDL_Rect batteryOutline = {x, y, batteryWidth, batteryHeight};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &batteryOutline);

    SDL_Rect batteryCap = {x + batteryWidth,
                           y + batteryHeight / 4,
                           capWidth,
                           batteryHeight / 2};
    SDL_RenderFillRect(renderer, &batteryCap);

    SDL_Rect batteryBar = {x, y,
                           (int)(batteryWidth * (battery / 100.0f)),
                           batteryHeight};

    SDL_Color batteryColor;

    if (battery > 50)
    {
        batteryColor.r = 0;
        batteryColor.g = 255;
        batteryColor.b = 0;
    }
    else
    {
        float ratio = battery / 50.0f;
        batteryColor.r = (Uint8)(255 * (1.0f - ratio));
        batteryColor.g = (Uint8)(255 * ratio);
        batteryColor.b = 0;
    }

    SDL_SetRenderDrawColor(renderer,
                           batteryColor.r,
                           batteryColor.g,
                           batteryColor.b,
                           255);

    SDL_RenderFillRect(renderer, &batteryBar);

    char text[20];
    sprintf(text, "%.0f%%", battery);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = {
        x + batteryWidth / 2 - surface->w / 2,
        y - surface->h - 5,
        surface->w,
        surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * \brief Affiche tous les éléments du jeu.
 *
 * Cette fonction affiche la batterie et les boutons
 * de contrôle dans la fenêtre.
 *
 * \param renderer Renderer SDL.
 * \param fontBattery Police utilisée pour la batterie.
 * \param fontButtons Police utilisée pour les boutons.
 * \param window Fenêtre SDL.
 */
void game_render(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    battery_render(renderer, fontBattery, w, h);
    buttons_render(renderer, fontButtons, w, h);
}

/**
 * \brief Fonction principale du programme.
 *
 * Initialise SDL, charge les ressources,
 * lance la boucle principale du jeu
 * et gère le rendu et les événements.
 *
 * \return Code de retour du programme.
 */
int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("FNAF",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *DOORS_OFF_L_OFF = IMG_LoadTexture(renderer, "./assets/img/INgame/DOORS_OFF_L_OFF.png");
    SDL_Texture *DOORS_OFF_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/DOORS_OFF_L_ON.png");
    if (!DOORS_OFF_L_OFF || !DOORS_OFF_L_ON)
    {
        printf("Erreur chargement background : %s\n", IMG_GetError());
    }
    TTF_Font *fontBattery = TTF_OpenFont("./assets/font/VCR.ttf", 32);
    TTF_Font *fontButtons = TTF_OpenFont("./assets/font/VCR.ttf", 20);

    if (!fontBattery || !fontButtons)
    {
        printf("Erreur chargement police\n");
        return 1;
    }

    game_init();

    int running = 1;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            game_handleEvent(&event, window);
        }

        game_update(deltaTime);

        SDL_RenderClear(renderer);
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        SDL_Rect bgRect = {0, 0, w, h};
        int lightCount = buttons_getLightCount();

        SDL_Texture *background;

        if (lightCount >= 2)
            background = DOORS_OFF_L_ON;
        else
            background = DOORS_OFF_L_OFF;

        SDL_RenderCopy(renderer, background, NULL, &bgRect);

        game_render(renderer, fontBattery, fontButtons, window);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(fontBattery);
    TTF_CloseFont(fontButtons);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(DOORS_OFF_L_OFF);
    SDL_DestroyTexture(DOORS_OFF_L_ON);
    TTF_Quit();
    SDL_Quit();
}
