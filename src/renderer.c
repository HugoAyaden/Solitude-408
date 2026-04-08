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
    SDL_Rect btnToggle      = {BTN_TOGGLE_X, windowH - 50, BTN_TOGGLE_W, BTN_TOGGLE_H};
    SDL_Rect btnPorteGauche  = {BTN_MAIN_SPACING, windowH/2 - BTN_MAIN_H - 10, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnLumiereGauche = {BTN_MAIN_SPACING, windowH/2 + 10, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnLumiereGeneral = {BTN_MAIN_SPACING, windowH/2 + 160, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnPorteDroite  = {windowW - BTN_MAIN_W - BTN_MAIN_SPACING, windowH/2 - BTN_MAIN_H - 10, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnLumiereDroite = {windowW - BTN_MAIN_W - BTN_MAIN_SPACING, windowH/2 + 10, BTN_MAIN_W, BTN_MAIN_H};

    drawButton(renderer, font, btnPorteGauche,   panneau.porte_gauche,  "DOOR");
    drawButton(renderer, font, btnPorteDroite,   panneau.porte_droite,  "DOOR");
    drawButton(renderer, font, btnLumiereGauche, panneau.lumiere_gauche, "LIGHT");
    drawButton(renderer, font, btnLumiereDroite, panneau.lumiere_droite, "LIGHT");
    drawButton(renderer, font, btnLumiereGeneral, panneau.lumieres,     "LIGHT_G");
    drawButton(renderer, font, btnToggle,        panneau.moniteur,      "CAMERAS");
}

/**
 * \brief Affiche les 9 boutons de sélection de caméra + la barre de basculement.
 *
 * Les positions sont calculées par build_camera_rects(), même source que
 * camera_buttons_handleEvent() — garantit que clic et affichage sont toujours alignés.
 * L'état actif de chaque bouton est lu dans cameras_on[i].
 *
 * \param renderer Renderer SDL utilisé pour le dessin.
 * \param font     Police pour les labels des boutons.
 * \param windowW  Largeur de la fenêtre.
 * \param windowH  Hauteur de la fenêtre.
 */
void camera_buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{
    SDL_Rect btnCameras[9];
    build_camera_rects(btnCameras, windowW, windowH);
    SDL_Rect btnToggle = {BTN_TOGGLE_X, windowH - 50, BTN_TOGGLE_W, BTN_TOGGLE_H};

    /* Chaque bouton s'allume si la caméra correspondante est active */
    for (int i = 0; i < 9; i++)
        drawButton(renderer, font, btnCameras[i], cameras_on[i], " ");
    drawButton(renderer, font, btnToggle, panneau.moniteur, "CAMERAS");
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
    SDL_Rect mapCamera = {BTN_TOGGLE_X, windowH/2, BTN_TOGGLE_W, BTN_TOGGLE_H};

    drawCamera(renderer, mapCamera);
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
    if(panneau.moniteur == 0)
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
 * \param panneau.porte_droite Vrai si la porte droite est fermée sinon faux
 * \param panneau.porte_gauche Vrai si la porte gauche est fermée sinon faux
 * \param lumièreDroiteActive Vrai si la lumiere droite est allumee sinon faux
 * \param lumièreGaucheActive Vrai si la lumiere gauche est allumee sinon faux
 */
void affichage(){
    if(panneau.moniteur == 0){
        /* BLACKOUT : batterie épuisée OU extinction générale manuelle.
         * Dans les deux cas, toutes les commandes sont désactivées
         * et les portes s'ouvrent (plus d'énergie pour les maintenir). */
        if(battery <= 0 || panneau.lumieres){
            background = BLACKOUT;
            change = FAUX;
            panneau.porte_droite = FAUX;
            panneau.porte_gauche = FAUX;
            panneau.lumiere_droite = FAUX;
            panneau.lumiere_gauche = FAUX;
            ouverture_porte_gauche(map, joueur);
            ouverture_porte_droite(map, joueur);
        }
        else if(panneau.lumiere_droite && !panneau.porte_droite){
            if(monster->num_camera == PORTE_HAUT-1){
                background = MONSTER_R_DOOR_O;
            }
        else if(monster->num_camera == PORTE_HAUT){
                background = MONSTER_R_DOOR_O_A;
            }
            else
                background = R_DOOR_OFF_L_ON;
        }
        else if(panneau.lumiere_gauche && !panneau.porte_gauche){
            if(monster->num_camera == PORTE_BAS-1){
                background = MONSTER_L_DOOR_O;
            }
            else if(monster->num_camera == PORTE_BAS){
                background = MONSTER_L_DOOR_O_A;
            }
            else 
                background = L_DOOR_OFF_L_ON;
        }
        else if(panneau.porte_gauche && !panneau.lumiere_gauche){
            background = L_DOOR_ON_L_OFF;
        }
        else if(panneau.porte_droite && !panneau.lumiere_droite){
            background = R_DOOR_ON_L_OFF;
        }
        else if(panneau.porte_gauche && panneau.lumiere_gauche){
            background = L_DOOR_ON_L_ON;
        }
        else if(panneau.porte_droite && panneau.lumiere_droite){
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