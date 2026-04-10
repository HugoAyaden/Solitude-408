/**
 * \file buttons.c
 * \brief File for every button interaction
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.1
 * \date 29/03/2026
 *
 */

#include "buttons.h"

/**
 * \brief Initialise l'état des boutons.
 *
 * Tous les boutons (portes, lumieres et cameras) sont désactivés
 * au lancement du jeu.
 */
void buttons_init()
{
    porteGaucheActive = 0;
    porteDroiteActive = 0;
    lumiereGaucheActive = 0;
    lumiereDroiteActive = 0;
    boutonLumieres = 0;
    moniteurCameras = 0;
    camera1on = 0;
    camera2on = 0;
    camera3on = 0;
    camera4on = 0;
    camera5on = 0;
    camera6on = 0;
    camera7on = 0;
    camera8on = 0;
    camera9on = 0;
}

int cameraButton(){
    return (camera1on + camera2on + camera3on + camera4on + camera5on + 
            camera6on + camera7on + camera8on + camera9on);
}

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

void drawButton(SDL_Renderer *renderer, TTF_Font *font,
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
    textRect.w = surface->w /2;
    textRect.h = surface->h /2;
    textRect.x = rect.x + (rect.w - textRect.w) / 2;
    textRect.y = rect.y + (rect.h - textRect.h) / 2;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * \brief Gère les événements liés aux boutons.
 *
 * Cette fonction détecte les clics de souris et active
 * ou désactive les boutons correspondants (portes et lumières).
 *
 * \param event Événement SDL reçu.
 * \param window Fenêtre SDL utilisée pour récupérer la taille.
 * \param img_stretchedW_game_res Largeur de l'image étirée dans la résolution du jeu.
 */
void buttons_handleEvent(SDL_Event *event, SDL_Window *window,int img_stretchedW_game_res)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    SDL_GetWindowSize(window, &windowW, &windowH);

    int buttonW = 60;
    int buttonH = 60;
    int spacing = img_stretchedW_game_res / spacing_amount;
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;


    SDL_Rect btnCameras = {spacingcamera, windowH -50, buttonWcamera, buttonHcamera};
    SDL_Rect btnPorteGauche = {spacing + camera_offset_x, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing + camera_offset_x, windowH / 2 + 10, buttonW, buttonH};
    SDL_Rect btnLumiereGeneral = {spacing + camera_offset_x, windowH / 2 + 160, buttonW, buttonH};

    SDL_Rect btnPorteDroite = {img_stretchedW_game_res - spacing - buttonW + camera_offset_x, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {img_stretchedW_game_res - spacing - buttonW + camera_offset_x, windowH / 2 + 10, buttonW, buttonH};

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};

    if (SDL_PointInRect(&p, &btnPorteGauche))
        porteGaucheActive = !porteGaucheActive;

    if (SDL_PointInRect(&p, &btnLumiereGeneral)){
        boutonLumieres = !boutonLumieres;
        joueur->lumiere = !joueur->lumiere;
    }

    if (SDL_PointInRect(&p, &btnCameras))
        moniteurCameras = !moniteurCameras;


    if (SDL_PointInRect(&p, &btnPorteDroite))
        porteDroiteActive = !porteDroiteActive;

    if (SDL_PointInRect(&p, &btnLumiereGauche))
        lumiereGaucheActive = !lumiereGaucheActive;

    if (SDL_PointInRect(&p, &btnLumiereDroite))
        lumiereDroiteActive = !lumiereDroiteActive;
}

/**
 * \brief Allow video camera change through buttons
 *
 */
void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    SDL_GetWindowSize(window, &windowW, &windowH);


    int buttonW = 44;
    int buttonH = 27;

    /* PLACEMENT DES BOUTTONS DES CAMERAS (fastidieux) */
    //camera 1
    int buttonX1 = windowW-154+buttonW;
    int buttonY1 = windowH/2-54;

    //camera 2
    int buttonX2 = windowW-154+buttonW;
    int buttonY2 = windowH/2+55;

    //camera 3
    int buttonX3 = windowW-276+buttonW;
    int buttonY3 = windowH/2 + 1;

    //camera 4
    int buttonX4 = windowW-341+buttonW;
    int buttonY4 = windowH/2+10;

    //camera 5
    int buttonX5 = windowW-472+buttonW;
    int buttonY5 = windowH/2+55;

    //camera 6
    int buttonX6 = windowW-472+buttonW;
    int buttonY6 = windowH/2-54;

    //camera 7
    int buttonX7 = windowW-278+buttonW;
    int buttonY7= windowH/2-177;

    //camera 8
    int buttonX8 = windowW-452+buttonW;
    int buttonY8 = windowH/2-177;

    //camera 9
    int buttonX9 = windowW-341+buttonW;
    int buttonY9 = windowH/2+144;

    //toggle camera   
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;


    SDL_Rect btnCameras = {spacingcamera, windowH -50, buttonWcamera, buttonHcamera};
    SDL_Rect btnCamera1 = {buttonX1, buttonY1, buttonW, buttonH};
    SDL_Rect btnCamera2 = {buttonX2, buttonY2, buttonW, buttonH};
    SDL_Rect btnCamera3 = {buttonX3, buttonY3, buttonW, buttonH};
    SDL_Rect btnCamera4 = {buttonX4, buttonY4, buttonW, buttonH};
    SDL_Rect btnCamera5 = {buttonX5, buttonY5, buttonW, buttonH};
    SDL_Rect btnCamera6 = {buttonX6, buttonY6, buttonW, buttonH};
    SDL_Rect btnCamera7 = {buttonX7, buttonY7, buttonW, buttonH};
    SDL_Rect btnCamera8 = {buttonX8, buttonY8, buttonW, buttonH};
    SDL_Rect btnCamera9 = {buttonX9, buttonY9, buttonW, buttonH};

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};
    if (SDL_PointInRect(&p, &btnCamera1)){
        if(cameraButton() && camera1on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera1on = !camera1on;
        camera->num_camera = CAMERA_5;
    }
    if (SDL_PointInRect(&p, &btnCamera2)){
        if(cameraButton() && camera2on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera2on = !camera2on;
        camera->num_camera = CAMERA_15;
    }
    if (SDL_PointInRect(&p, &btnCamera3)){
        if(cameraButton() && camera3on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera3on = !camera3on;
        camera->num_camera = CAMERA_9;
    }
    if (SDL_PointInRect(&p, &btnCamera4)){
        if(cameraButton() && camera4on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera4on = !camera4on;
        camera->num_camera = CAMERA_8;
    }
    if (SDL_PointInRect(&p, &btnCamera5)){
        if(cameraButton() && camera5on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera5on = !camera5on;
        camera->num_camera = CAMERA_5;
    }
    if (SDL_PointInRect(&p, &btnCamera6)){
        if(cameraButton() && camera6on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera6on = !camera6on;
        camera->num_camera = CAMERA_6;
    }
    if (SDL_PointInRect(&p, &btnCamera7)){
        if(cameraButton() && camera7on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera7on = !camera7on;
        camera->num_camera = CAMERA_7;
    }

    //CAMERA 1 DANS LA MATRICE
    if (SDL_PointInRect(&p, &btnCamera8)){
        if(cameraButton() && camera8on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera8on = !camera8on;
        camera->num_camera = CAMERA_1;
    }
    //CAMERA 1 DANS LA MATRICE
    if (SDL_PointInRect(&p, &btnCamera9)){
        if(cameraButton() && camera9on == 0){
            camera1on = 0;
            camera2on = 0;
            camera3on = 0;
            camera4on = 0;
            camera5on = 0;
            camera6on = 0;
            camera7on = 0;
            camera8on = 0;
            camera9on = 0;
        }
        camera9on = !camera9on;
        camera->num_camera = CAMERA_12;
    }
    if (SDL_PointInRect(&p, &btnCameras))
    moniteurCameras = !moniteurCameras;
}

/**
 * \brief Affiche la map de la camera
 *
 */
void drawCamera(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label,
                    int windowW, int windowH)
{
    SDL_Surface *surface = IMG_Load("./assets/img/INgame/cam_map.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect;
    /* La taille de la surface que la map prend (ici, tout) */
    textRect.w = surface->w;
    textRect.h = surface->h;
    
    /* Placement de la map des camera sur l'ecran */
    textRect.x = windowW - textRect.w;
    textRect.y = rect.y - 200;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}