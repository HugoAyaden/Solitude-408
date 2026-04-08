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
    panneau.porte_gauche = 0;
    panneau.porte_droite = 0;
    panneau.lumiere_gauche = 0;
    panneau.lumiere_droite = 0;
    panneau.lumieres = 0;
    panneau.moniteur = 0;
    memset(cameras_on, 0, sizeof(cameras_on));
}

/* Retourne le nombre de caméras actuellement actives (0 si aucune). */
int cameraButton(){
    int total = 0;
    for (int i = 0; i < 9; i++) total += cameras_on[i];
    return total;
}

/* Éteint toutes les caméras. Appelé avant d'en activer une nouvelle
 * pour éviter qu'plusieurs caméras restent allumées simultanément. */
void reset_all_cameras(void)
{
    memset(cameras_on, 0, sizeof(cameras_on));
}

/**
 * \brief Calcule les SDL_Rect des 9 boutons de sélection de caméra.
 *
 * Les positions sont relatives à la taille de fenêtre (windowW/windowH).
 * Cette fonction est la source unique de vérité pour le layout des caméras :
 * elle est utilisée à la fois par camera_buttons_handleEvent() (détection de clic)
 * et camera_buttons_render() (affichage), évitant toute désynchronisation.
 *
 * Les offsets correspondent à la superposition sur l'image cam_map.png.
 *
 * \param rects   Tableau de 9 SDL_Rect à remplir.
 * \param windowW Largeur courante de la fenêtre.
 * \param windowH Hauteur courante de la fenêtre.
 */
void build_camera_rects(SDL_Rect rects[9], int windowW, int windowH)
{
    int w = BTN_CAM_W, h = BTN_CAM_H;
    rects[0] = (SDL_Rect){ windowW-150, windowH/2-54,  w, h }; /* cam 1 */
    rects[1] = (SDL_Rect){ windowW-150, windowH/2+55,  w, h }; /* cam 2 */
    rects[2] = (SDL_Rect){ windowW-272, windowH/2+1,   w, h }; /* cam 3 */
    rects[3] = (SDL_Rect){ windowW-337, windowH/2+10,  w, h }; /* cam 4 */
    rects[4] = (SDL_Rect){ windowW-468, windowH/2+55,  w, h }; /* cam 5 */
    rects[5] = (SDL_Rect){ windowW-468, windowH/2-54,  w, h }; /* cam 6 */
    rects[6] = (SDL_Rect){ windowW-274, windowH/2-177, w, h }; /* cam 7 */
    rects[7] = (SDL_Rect){ windowW-448, windowH/2-177, w, h }; /* cam 8 */
    rects[8] = (SDL_Rect){ windowW-337, windowH/2+144, w, h }; /* cam 9 */
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
 */
void buttons_handleEvent(SDL_Event *event, SDL_Window *window)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    SDL_GetWindowSize(window, &windowW, &windowH);

    SDL_Rect btnToggle    = {BTN_TOGGLE_X, windowH - 50, BTN_TOGGLE_W, BTN_TOGGLE_H};
    SDL_Rect btnPorteGauche  = {BTN_MAIN_SPACING, windowH/2 - BTN_MAIN_H - 10, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnLumiereGauche = {BTN_MAIN_SPACING, windowH/2 + 10, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnLumiereGeneral = {BTN_MAIN_SPACING, windowH/2 + 160, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnPorteDroite  = {windowW - BTN_MAIN_W - BTN_MAIN_SPACING, windowH/2 - BTN_MAIN_H - 10, BTN_MAIN_W, BTN_MAIN_H};
    SDL_Rect btnLumiereDroite = {windowW - BTN_MAIN_W - BTN_MAIN_SPACING, windowH/2 + 10, BTN_MAIN_W, BTN_MAIN_H};

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};

    if (SDL_PointInRect(&p, &btnPorteGauche))
        panneau.porte_gauche = !panneau.porte_gauche;

    if (SDL_PointInRect(&p, &btnLumiereGeneral)){
        panneau.lumieres = !panneau.lumieres;
        joueur->lumiere = !joueur->lumiere;
    }

    if (SDL_PointInRect(&p, &btnToggle))
        panneau.moniteur = !panneau.moniteur;


    if (SDL_PointInRect(&p, &btnPorteDroite))
        panneau.porte_droite = !panneau.porte_droite;

    if (SDL_PointInRect(&p, &btnLumiereGauche))
        panneau.lumiere_gauche = !panneau.lumiere_gauche;

    if (SDL_PointInRect(&p, &btnLumiereDroite))
        panneau.lumiere_droite = !panneau.lumiere_droite;
}

/**
 * \brief Gère les clics sur les boutons de sélection de caméra.
 *
 * Logique d'exclusivité : si une autre caméra est déjà active et que
 * l'utilisateur clique sur un bouton différent, toutes les caméras sont
 * d'abord éteintes (reset_all_cameras), puis la nouvelle est activée.
 * Si la même caméra est recliquée, elle est simplement désactivée (toggle).
 *
 * Les positions des boutons sont calculées par build_camera_rects() —
 * source unique partagée avec camera_buttons_render().
 */
void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    SDL_GetWindowSize(window, &windowW, &windowH);

    /* Positions calculées une seule fois, identiques à celles du rendu */
    SDL_Rect btnCameras[9];
    build_camera_rects(btnCameras, windowW, windowH);
    SDL_Rect btnToggle = {BTN_TOGGLE_X, windowH - 50, BTN_TOGGLE_W, BTN_TOGGLE_H};

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};
    if (SDL_PointInRect(&p, &btnCameras[0])){
        if(cameraButton() && cameras_on[0] == 0)
            reset_all_cameras();
        cameras_on[0] = !cameras_on[0];
        camera->num_camera = CAMERA_5;
    }
    if (SDL_PointInRect(&p, &btnCameras[1])){
        if(cameraButton() && cameras_on[1] == 0)
            reset_all_cameras();
        cameras_on[1] = !cameras_on[1];
        camera->num_camera = CAMERA_15;
    }
    if (SDL_PointInRect(&p, &btnCameras[2])){
        if(cameraButton() && cameras_on[2] == 0)
            reset_all_cameras();
        cameras_on[2] = !cameras_on[2];
        camera->num_camera = CAMERA_9;
    }
    if (SDL_PointInRect(&p, &btnCameras[3])){
        if(cameraButton() && cameras_on[3] == 0)
            reset_all_cameras();
        cameras_on[3] = !cameras_on[3];
        camera->num_camera = CAMERA_8;
    }
    if (SDL_PointInRect(&p, &btnCameras[4])){
        if(cameraButton() && cameras_on[4] == 0)
            reset_all_cameras();
        cameras_on[4] = !cameras_on[4];
        camera->num_camera = CAMERA_5;
    }
    if (SDL_PointInRect(&p, &btnCameras[5])){
        if(cameraButton() && cameras_on[5] == 0)
            reset_all_cameras();
        cameras_on[5] = !cameras_on[5];
        camera->num_camera = CAMERA_6;
    }
    if (SDL_PointInRect(&p, &btnCameras[6])){
        if(cameraButton() && cameras_on[6] == 0)
            reset_all_cameras();
        cameras_on[6] = !cameras_on[6];
        camera->num_camera = CAMERA_7;
    }
    if (SDL_PointInRect(&p, &btnCameras[7])){
        if(cameraButton() && cameras_on[7] == 0)
            reset_all_cameras();
        cameras_on[7] = !cameras_on[7];
        camera->num_camera = CAMERA_1;
    }
    if (SDL_PointInRect(&p, &btnCameras[8])){
        if(cameraButton() && cameras_on[8] == 0)
            reset_all_cameras();
        cameras_on[8] = !cameras_on[8];
        camera->num_camera = CAMERA_12;
    }
    if (SDL_PointInRect(&p, &btnToggle))
        panneau.moniteur = !panneau.moniteur;
}

/**
 * \brief Affiche la map de la camera
 *
 */
void drawCamera(SDL_Renderer *renderer, SDL_Rect rect)
{

    SDL_Surface *surface = IMG_Load("./assets/img/INgame/cam_map.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect;

    /* La taille de la surface que la map prend (ici, tout) */
    textRect.w = surface->w;
    textRect.h = surface->h;

    /* Placement de la map des camera sur l'ecran */
    textRect.x = rect.x + 800;
    textRect.y = rect.y - 200;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}