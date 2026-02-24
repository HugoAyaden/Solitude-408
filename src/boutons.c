#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "boutons.h"

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