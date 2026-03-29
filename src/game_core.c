#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <portes.h>
#include <MainMenu.h>


/**
 * \file game_core.c
 * \brief Boucle principale de jeu
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.3
 * \date 10/03/2026
 *
 */

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ERROR -1
#define MAX_NIGHT 2
#define BATTERY_DURATION 420.0f
#define TEMPS_NUIT 20000


static float battery = 100.0f;

const Uint32 monsterMoveDelay = 2000; // Temps avant chaque déplacement du monstre en millisecondes (1000 ms = 1 s)


typedef enum {CAMERA_0, CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5, 
              CAMERA_6, CAMERA_7, CAMERA_8, CAMERA_9 ,CAMERA_10, CAMERA_11,
              CAMERA_12, CAMERA_13, CAMERA_14, CAMERA_15
            } num_cameras;

// Deso Hugo mais fallait le faire
static int porteGaucheActive = 0;
static int porteDroiteActive = 0;
static int lumiereGaucheActive = 0;
static int lumiereDroiteActive = 0;
static int tempsDebut = 0;
static int tempsFin = 0;
static int change = 1;
static float finish = 0.0f;
static int duree = 0;
static int moniteurCameras = 0;
static int camera1on = 0;
static int camera2on = 0;
static int camera3on = 0;
static int camera4on = 0;
static int camera5on = 0;
static int camera6on = 0;
static int camera7on = 0;
static int camera8on = 0;
static int camera9on = 0;
static int camera10on = 0;
static int camera11on = 0;
static int camera12on = 0;
static int camera13on = 0;
static int camera14on = 0;
static int camera15on = 0;

static int cameraMap = 0;
int windowW = 0;
int windowH = 0;

static booleen_t boutonLumieres = FAUX;

static carte_t *carte = NULL;
static case_t *joueur = NULL;
static case_t *monstre = NULL;
static case_t *mimic = NULL;

static SDL_Texture *background;
static SDL_Texture *BLACKOUT = NULL;
static SDL_Texture *DOORS_OFF_L_OFF = NULL;
static SDL_Texture *DOORS_OFF_L_ON = NULL;
static SDL_Texture *DOORS_ON_L_ON = NULL;
static SDL_Texture *L_DOOR_OFF_L_ON = NULL;
static SDL_Texture *L_DOOR_ON_L_OFF = NULL;
static SDL_Texture *L_DOOR_ON_L_ON = NULL;
static SDL_Texture *R_DOOR_OFF_L_ON = NULL;
static SDL_Texture *R_DOOR_ON_L_OFF = NULL;
static SDL_Texture *R_DOOR_ON_L_ON = NULL;
static SDL_Texture *MONITOR_ROOM = NULL;
static SDL_Texture *STATIC = NULL;
static SDL_Texture *MONSTER_L_DOOR_C = NULL;
static SDL_Texture *MONSTER_L_DOOR_O_A = NULL;
static SDL_Texture *MONSTER_L_DOOR_O = NULL;
static SDL_Texture *MONSTER_R_DOOR_C = NULL;
static SDL_Texture *MONSTER_R_DOOR_O_A = NULL;
static SDL_Texture *MONSTER_R_DOOR_O = NULL;



static case_t * camera = NULL;




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
    textRect.w = surface->w /2;
    textRect.h = surface->h /2;
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
    boutonLumieres = 0;
    moniteurCameras = 0;
    camera4on = 0;
    camera6on = 0;
}

int cameraButton(){
    return camera1on + camera2on + camera3on + camera4on + camera5on + camera6on + camera7on + camera8on + camera9on + camera10on + camera11on + camera12on + camera13on
     + camera14on + camera15on;
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

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};

    if (SDL_PointInRect(&p, &btnPorteGauche))
        porteGaucheActive = !porteGaucheActive;

    if (SDL_PointInRect(&p, &btnLumiereGeneral))
        boutonLumieres = !boutonLumieres;

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
    int spacing = 20;    
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

void camera_buttons_handleEvent(SDL_Event *event, SDL_Window *window)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return;

    SDL_GetWindowSize(window, &windowW, &windowH);


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
    int spacing = 20;    
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

    int mx = event->button.x;
    int my = event->button.y;

    SDL_Point p = {mx, my};

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
        camera->num_camera = CAMERA_4;
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
        camera->num_camera = CAMERA_9;
    }
    if (SDL_PointInRect(&p, &btnCameras))
    moniteurCameras = !moniteurCameras;
}

void change_camera(case_t * camera, case_t * monstre){
    if(camera8on && camera->num_camera == CAMERA_1 && monstre->num_camera == CAMERA_1){
        background = MONITOR_ROOM;
    }
    else
        background = STATIC;
}


static void drawCamera(SDL_Renderer *renderer, TTF_Font *font,
                       SDL_Rect rect, int active, const char *label)
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
    if(moniteurCameras == 0)
        buttons_handleEvent(event, window);
    else
        camera_buttons_handleEvent(event, window);
}

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
void game_initialise()
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
 * Chaque action du joueur et du monstre sont affichée
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
            ouverture_porte_gauche(carte, joueur);
            ouverture_porte_droite(carte, joueur);
        }
        else if(battery > 0 && boutonLumieres){
            background = BLACKOUT;
            change = FAUX;
            porteDroiteActive = FAUX;
            porteGaucheActive = FAUX;
            ouverture_porte_gauche(carte, joueur);
            ouverture_porte_droite(carte, joueur);
        }
        else if(lumiereDroiteActive && !porteDroiteActive){
            if(monstre->num_camera == PORTE_HAUT-1){
                background = MONSTER_R_DOOR_O;
            }
        else if(monstre->num_camera == PORTE_HAUT){
                background = MONSTER_R_DOOR_O_A;
            }
            else
                background = R_DOOR_OFF_L_ON;
        }
        else if(lumiereGaucheActive && !porteGaucheActive){
            if(monstre->num_camera == PORTE_BAS-1){
                background = MONSTER_L_DOOR_O;
            }
            else if(monstre->num_camera == PORTE_BAS){
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
    else{
        change_camera(camera, monstre);
    }
}

/**
 * \brief Gère la difficulté du jeu en fonction de la nuit actuelle.
 *
 * En fonction de la nuit, le monstre peut se déplacer plus ou moins fréquemment,
 * et le mimic peut être activé à partir de la nuit 2.
 *
 * \param night Numéro de la nuit actuelle (0, 1 ou 2).
 */

void difficulte(int night){
    switch(night){
        case 0:
            if(chance_deplacement() < 1) {
                movement_opportunity(carte, monstre, 
                                    monstre->num_camera % FIN_Y, 
                                    monstre->num_camera / FIN_Y);
            }
            break;
        case 1:
            if(chance_deplacement() < 3) {
                move_monster(carte, monstre, joueur);
            }
            else{
                movement_opportunity(carte, monstre,
                                    monstre->num_camera % FIN_Y,
                                    monstre->num_camera / FIN_Y);
            }
            break;
        case 2:
            if(chance_deplacement() < 10) {
                move_monster(carte, monstre, joueur);
            }
            else{
                movement_opportunity(carte, monstre,
                                    monstre->num_camera % FIN_Y,
                                    monstre->num_camera / FIN_Y);
            }
            mouvement_mimic(carte, mimic);
            break;
        default:
            break;
    }
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
void game_init(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* fontBattery, TTF_Font* fontButtons) {
    //Load Textures ( interminable )
    if (BLACKOUT == NULL) {
        BLACKOUT = IMG_LoadTexture(renderer, "./assets/img/INgame/BLACKOUT.png");
        DOORS_OFF_L_OFF = IMG_LoadTexture(renderer, "./assets/img/INgame/DOORS_OFF_L_OFF.png");
        DOORS_OFF_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/DOORS_OFF_L_ON.png");
        DOORS_ON_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/DOORS_ON_L_ON.png");
        L_DOOR_OFF_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/L_DOOR_OFF_L_ON.png");
        L_DOOR_ON_L_OFF = IMG_LoadTexture(renderer, "./assets/img/INgame/L_DOOR_ON_L_OFF.png");
        L_DOOR_ON_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/L_DOOR_ON_L_ON.png");
        R_DOOR_OFF_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/R_DOOR_OFF_L_ON.png");
        R_DOOR_ON_L_OFF = IMG_LoadTexture(renderer, "./assets/img/INgame/R_DOOR_ON_L_OFF.png");
        R_DOOR_ON_L_ON = IMG_LoadTexture(renderer, "./assets/img/INgame/R_DOOR_ON_L_ON.png");
        MONITOR_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM.png");
        STATIC = IMG_LoadTexture(renderer, "./assets/img/INgame/static.gif");
        MONSTER_L_DOOR_C = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_L_DOOR_C.png");
        MONSTER_L_DOOR_O_A = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_L_DOOR_O_A.png");
        MONSTER_L_DOOR_O = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_L_DOOR_O.png");
        MONSTER_R_DOOR_C = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_R_DOOR_C.png");
        MONSTER_R_DOOR_O_A = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_R_DOOR_O_A.png");
        MONSTER_R_DOOR_O = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_R_DOOR_O.png");
    }

    if (carte == NULL)   carte = malloc(sizeof(carte_t));
    if (camera == NULL)   camera = malloc(sizeof(carte_t));
    if (joueur == NULL)  joueur = malloc(sizeof(case_t));
    if (monstre == NULL) monstre = malloc(sizeof(case_t));
    if (mimic == NULL)    mimic = malloc(sizeof(case_t));
    
    //POUR UN REDEMARAGE A 0
    game_initialise();
    
    srand(time(NULL));
    init_carte(carte);
    init_joueur(joueur, carte);
    init_camera(camera, carte);
    placement_monstre(carte, monstre);

    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 monsterLastMove = SDL_GetTicks();
    int actual = -1;
    
    load_night();
    load_settings();
    if(night == ERROR){
        save_night(0);
        load_night();
    }
    if(night >=MAX_NIGHT+1 /*A CHANGER AVEC LES NOUVELLES NUITS*/ ){
        night = 2;
        save_night(night);
        load_night();
    }
    if(night >= MAX_NIGHT){
        placement_mimic(carte, mimic);
    }
    
    tempsDebut = SDL_GetTicks();

    tempsFin = SDL_GetTicks() + TEMPS_NUIT;
    finish = (tempsFin-duree);
    while (!fin(carte, monstre) && finish >= 0){
        Uint32 currentTime = SDL_GetTicks();
        //Temps du monstre avant chaque déplacement
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        //Echap pour quitter le jeu (pas de retour au menu sinon pression inexistante)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                exit(0);
            game_handleEvent(&event, window);
        }

        game_update(deltaTime);

        SDL_RenderClear(renderer);
        SDL_GetWindowSize(window, &windowW, &windowH);
        SDL_Rect bgRect = {0, 0, windowW, windowH};
        int lightCount = buttons_getLightCount();


    
        /*=====NE JAMAIS ENLEVER J'AI TROP SOUFFERT=====*/
        // Déplacement du monstre toutes les 5 secondes
        if (currentTime - monsterLastMove >= monsterMoveDelay)
        {
            monsterLastMove = currentTime;

                if(porteGaucheActive && monstre->num_camera == PORTE_BAS){
                    placement_monstre(carte, monstre);
                }
                else if(porteDroiteActive && monstre->num_camera == PORTE_HAUT){
                    placement_monstre(carte, monstre);
                }

                //Chaque nuit a sa difficulté d'IA
            difficulte(night);


            printf("nuit %d\n", night);
            printf("Le monstre se déplace sur la caméra %d\n", monstre->num_camera);
            printf("portes fermees %d\n", actual);
            duree = SDL_GetTicks();
            finish = (tempsFin-duree)+deltaTime;
            printf("Temps ecoule : %2.f\n", finish);
        }
        /*==============================================*/
        if(battery > 0 && !boutonLumieres){
            change = VRAI;
        }
        if(change == VRAI){
            if(actual != buttons_getDoorCount()){
                if(porteDroiteActive)
                    fermeture_portes_droite(joueur, carte);
                if(!porteDroiteActive)
                    ouverture_porte_droite(carte, joueur);
                if(porteGaucheActive)
                    fermeture_portes_gauche(joueur, carte);
                if(!porteGaucheActive)
                    ouverture_porte_gauche(carte, joueur);
                }
            }

        actual = buttons_getDoorCount();
        if (lightCount >= 2)
            background = DOORS_OFF_L_ON;


        /*=========DIFFERENTS AFFICHAGES EN FONCTION DES LUMIERES ET DES PORTES==========*/
        affichage();
        /*=========================================================*/

        SDL_RenderCopy(renderer, background, NULL, &bgRect);

        render_game(renderer, fontBattery, fontButtons, window);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    if(finish <=0 && !fin(carte, monstre)){
        night++;
        save_night(night);
    }
}

void game_final_cleanup(){
    if (carte != NULL) {
        detruire_carte(carte); 
        carte = NULL;
    }
    if (joueur != NULL) {
        joueur = NULL;
    }
    if (camera != NULL) {
        camera = NULL;
    }
    if (monstre != NULL) {
        monstre = NULL;
    }
    if (mimic != NULL) {
        mimic = NULL;
    }
}