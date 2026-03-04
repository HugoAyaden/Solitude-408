#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


static int porteGaucheActive = 0;
static int porteDroiteActive = 0;
static int lumiereGaucheActive = 0;
static int lumiereDroiteActive = 0;

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

void buttons_init()
{
    porteGaucheActive = 0;
    porteDroiteActive = 0;
    lumiereGaucheActive = 0;
    lumiereDroiteActive = 0;
}

void buttons_handleEvent(SDL_Event *event, SDL_Window *window)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    int buttonW = 60;
    int buttonH = 60;
    int spacing = 20;

    SDL_Rect btnPorteGauche = {spacing, h/2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing, h/2 + 10, buttonW, buttonH};

    SDL_Rect btnPorteDroite = {w - buttonW - spacing, h/2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {w - buttonW - spacing, h/2 + 10, buttonW, buttonH};

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

void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{
    int buttonW = 60;
    int buttonH = 60;
    int spacing = 20;

    SDL_Rect btnPorteGauche = {spacing, windowH/2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing, windowH/2 + 10, buttonW, buttonH};

    SDL_Rect btnPorteDroite = {windowW - buttonW - spacing, windowH/2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {windowW - buttonW - spacing, windowH/2 + 10, buttonW, buttonH};

    drawButton(renderer, font, btnPorteGauche, porteGaucheActive, "DOOR");
    drawButton(renderer, font, btnPorteDroite, porteDroiteActive, "DOOR");
    drawButton(renderer, font, btnLumiereGauche, lumiereGaucheActive, "LIGHT");
    drawButton(renderer, font, btnLumiereDroite, lumiereDroiteActive, "LIGHT");
}

int buttons_getDoorCount()
{
    return porteGaucheActive + porteDroiteActive;
}

int buttons_getLightCount()
{
    return lumiereGaucheActive + lumiereDroiteActive;
}



void game_handleEvent(SDL_Event *event, SDL_Window *window)
{
    buttons_handleEvent(event, window);
}





#define BATTERY_DURATION 420.0f

static float battery = 100.0f;

void battery_init()
{
    battery = 100.0f;
}

void game_init()
{
    battery_init();
    buttons_init();
}

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
void game_update(float deltaTime)
{
    int doorCount = buttons_getDoorCount();
    int lightCount = buttons_getLightCount();

    battery_update(deltaTime, doorCount, lightCount);
}

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
        surface->h
    };

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

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
/*
int main(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("FNAF",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        game_render(renderer, fontBattery, fontButtons, window);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(fontBattery);
    TTF_CloseFont(fontButtons);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
*/