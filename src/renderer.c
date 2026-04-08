/**
 * \file renderer.c
 * \brief File for every in game render.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#include "renderer.h"

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
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;


    SDL_Rect btnCameras = {spacingcamera, windowH -50, buttonWcamera, buttonHcamera};
    SDL_Rect btnPorteGauche = {spacing, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing, windowH / 2 + 10, buttonW, buttonH};
    SDL_Rect btnLumiereGeneral = {spacing, windowH / 2 + 160, buttonW, buttonH};

    SDL_Rect btnPorteDroite = {windowW - buttonW - spacing, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {windowW - buttonW - spacing, windowH / 2 + 10, buttonW, buttonH};

    drawButton(renderer, font, btnPorteGauche, porteGaucheActive, "DOOR");
    drawButton(renderer, font, btnPorteDroite, porteDroiteActive, "DOOR");
    drawButton(renderer, font, btnLumiereGauche, lumiereGaucheActive, "LIGHT");
    drawButton(renderer, font, btnLumiereDroite, lumiereDroiteActive, "LIGHT");
    drawButton(renderer, font, btnLumiereGeneral, boutonLumieres, "LIGHT_G");
    drawButton(renderer, font, btnCameras, moniteurCameras, "CAMERAS");
}

/**
 * \brief Permet l'affichage des boutons de la camera
 * 
 * \param renderer Renderer SDL utilisé pour le dessin.
 * \param font Police utilisée pour les labels des boutons (inutile ici)
 * \param windowW Largeur de la fenêtre.
 * \param windowH Hauteur de la fenêtre.
 */
void camera_buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{

    int buttonW = 44;
    int buttonH = 27;

    /* PLACEMENT DES BOUTTONS DES CAMERAS (fastidieux) */

    //camera 3
    int buttonX3 = windowW-274;
    int buttonY3 = windowH/2 + 2;

    //camera 4
    int buttonX4 = windowW-339;
    int buttonY4 = windowH/2+11;

    //camera 5
    int buttonX5 = windowW-470;
    int buttonY5 = windowH/2+57;

    //camera 6
    int buttonX6 = windowW-470;
    int buttonY6 = windowH/2-53;

    //camera 7
    int buttonX7 = windowW-276;
    int buttonY7= windowH/2-176;

    //camera 8
    int buttonX8 = windowW-450;
    int buttonY8 = windowH/2-176;

    //camera 9
    int buttonX9 = windowW-339;
    int buttonY9 = windowH/2+145;

    //toggle camera   
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;


    SDL_Rect btnCameras = {spacingcamera, windowH -50, buttonWcamera, buttonHcamera};
    SDL_Rect btnCamera3 = {buttonX3, buttonY3, buttonW, buttonH};
    SDL_Rect btnCamera4 = {buttonX4, buttonY4, buttonW, buttonH};
    SDL_Rect btnCamera5 = {buttonX5, buttonY5, buttonW, buttonH};
    SDL_Rect btnCamera6 = {buttonX6, buttonY6, buttonW, buttonH};
    SDL_Rect btnCamera7 = {buttonX7, buttonY7, buttonW, buttonH};
    SDL_Rect btnCamera8 = {buttonX8, buttonY8, buttonW, buttonH};
    SDL_Rect btnCamera9 = {buttonX9, buttonY9, buttonW, buttonH};

    drawButton(renderer, font, btnCamera3, camera3on, " ");
    drawButton(renderer, font, btnCamera4, camera4on, " ");
    drawButton(renderer, font, btnCamera5, camera5on, " ");
    drawButton(renderer, font, btnCamera6, camera6on, " ");
    drawButton(renderer, font, btnCamera7, camera7on, " ");
    drawButton(renderer, font, btnCamera8, camera8on, " ");
    drawButton(renderer, font, btnCamera9, camera9on, " ");
    drawButton(renderer, font, btnCameras, moniteurCameras, "CAMERAS");
}

/**
 * \brief Rend le rectangle affiché précedemment
 *
 */
void renderCameraMap(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;


    SDL_Rect mapCamera = {spacingcamera, windowH/2, buttonWcamera, buttonHcamera};

    drawCamera(renderer, font, mapCamera, cameraMap, "");
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
void render_game(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window)
{
    SDL_GetWindowSize(window, &windowW, &windowH);

    battery_render(renderer, fontBattery, windowW, windowH);
    if(moniteurCameras == 0)
        buttons_render(renderer, fontButtons, windowW, windowH);
    else{
        camera_buttons_render(renderer, fontButtons, windowW, windowH);
        renderCameraMap(renderer, fontButtons,windowW,windowH);
    }
}

/**
 * \brief Affiche les différents écrans en fonction des états du jeu
 *
 * Chaque action du joueur et du monster sont affichée
 * en temps réel lorsque la fonction le permet
 *
 * \param change Vrai les boutons peuvent etre actionnés sinon Faux
 * \param porteDroiteActive Vrai si la porte droite est fermée sinon faux
 * \param porteGaucheActive Vrai si la porte gauche est fermée sinon faux
 * \param lumièreDroiteActive Vrai si la lumiere droite est allumee sinon faux
 * \param lumièreGaucheActive Vrai si la lumiere gauche est allumee sinon faux
 */
void affichage(){
    if(moniteurCameras == 0){
        if(battery <= 0){
            background = BLACKOUT;
            change = FAUX;
            porteDroiteActive = FAUX;
            porteGaucheActive = FAUX;
            lumiereDroiteActive = FAUX;
            lumiereGaucheActive = FAUX;
            ouverture_porte_gauche(map, joueur);
            ouverture_porte_droite(map, joueur);
        }
        else if(battery > 0 && boutonLumieres){
            background = BLACKOUT;
            change = FAUX;
            porteDroiteActive = FAUX;
            porteGaucheActive = FAUX;
            lumiereDroiteActive = FAUX;
            lumiereGaucheActive = FAUX;
            ouverture_porte_gauche(map, joueur);
            ouverture_porte_droite(map, joueur);
        }
        else if(lumiereDroiteActive && !porteDroiteActive){
            if(monster->num_camera == PORTE_HAUT-1){
                background = MONSTER_R_DOOR_O;
            }
        else if(monster->num_camera == PORTE_HAUT){
                background = MONSTER_R_DOOR_O_A;
            }
            else
                background = R_DOOR_OFF_L_ON;
        }
        else if(lumiereGaucheActive && !porteGaucheActive){
            if(monster->num_camera == PORTE_BAS-1){
                background = MONSTER_L_DOOR_O;
            }
            else if(monster->num_camera == PORTE_BAS){
                background = MONSTER_L_DOOR_O_A;
            }
            else 
                background = L_DOOR_OFF_L_ON;
        }
        else if(porteGaucheActive && !lumiereGaucheActive){
            background = L_DOOR_ON_L_OFF;
        }
        else if(porteDroiteActive && !lumiereDroiteActive){
            background = R_DOOR_ON_L_OFF;
        }
        else if(porteGaucheActive && lumiereGaucheActive){
            background = L_DOOR_ON_L_ON;
        }
        else if(porteDroiteActive && lumiereDroiteActive){
            background = R_DOOR_ON_L_ON;
        }
        else
            background = DOORS_OFF_L_OFF;
    }
    //If the monitor is on we display the camera backgrounds
    else{
        change_camera(camera, monster);
    }
}