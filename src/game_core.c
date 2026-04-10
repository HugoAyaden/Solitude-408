


/**
 * \file game_core.c
 * \brief Main game loop
 * \author Bastien LEFEVRE TAUGOURDEAU, Hugo AYADEN
 * \version 1.4
 * \date 10/03/2026
 *
 */

#include "game_core.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ERROR -1
#define MAX_NIGHT 2
#define TEMPS_NUIT 180000
#define monsterMoveDelay 6000

/**
 * \brief Image static anim
 *
 * Les numeros des cameras sont suivant le schéma de "carte.c"
 * et non celui du jeu (par souci de réalisme).
 */
void static_vid(SDL_Renderer *renderer){
        //test animation
    IMG_Animation *anim = IMG_LoadAnimation("./assets/img/INgame/static.gif");
    SDL_Texture **textures = malloc(anim->count * sizeof(SDL_Texture*));
    for (int i = 0; i < anim->count; i++) {
    textures[i] = SDL_CreateTextureFromSurface(renderer, anim->frames[i]);
    }
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    int time = 0;
    while (time<1000) {

        Uint32 now = SDL_GetTicks();

        if (now - lastFrameTime >= anim->delays[currentFrame]) {
            currentFrame = (currentFrame + 1) % anim->count;
            lastFrameTime = now;
        }

        SDL_Rect dst = { 0, 0, windowW, windowH };
        SDL_RenderCopy(renderer, textures[currentFrame], NULL, &dst);

        SDL_RenderPresent(renderer);
        time++;
    }
}

/**
 * \brief Permet l'affichage des cameras
 *
 * Les numeros des cameras sont suivant le schéma de "map.c"
 * et non celui du jeu (par souci de réalisme).
 */
void change_camera(case_t * camera, case_t * monster, camera_type *camera_type){
    static int last_camera = -1;
    Mix_VolumeMusic(30);
    if(camera->num_camera != last_camera){
        Mix_PlayChannel(-1, cameraSwitch, 0);
        last_camera = camera->num_camera;
    }

    if(camera8on && camera->num_camera == CAMERA_1){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_1){
                if(monster->num_camera == CAMERA_1)
                    background = MONITOR_ROOM_MI_M;
                else
                    background = MONITOR_ROOM_MI;
            }
        else if (monster->num_camera == CAMERA_1)
            background = MONITOR_ROOM_M;
        else
            background = MONITOR_ROOM;
    }


    else if(camera1on && camera->num_camera == CAMERA_5){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_5){
                if(monster->num_camera == CAMERA_5)
                    background = R_D_M_MI;
                else
                    background = R_D_MI;
            }
        else if (monster->num_camera == CAMERA_5)
            background = R_D_M;
        else
            background = R_D;
    }

    else if(camera2on && camera->num_camera == CAMERA_15){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_15){
                if(monster->num_camera == CAMERA_15)
                    background = L_D_M_MI;
                else
                    background = L_D_MI;
            }
        else if (monster->num_camera == CAMERA_15)
            background = L_D_M;
        else
            background = L_D;
    }
    else if(camera4on && camera->num_camera == CAMERA_8){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_8){
                if(monster->num_camera == CAMERA_8)
                    background = CORRIDOR_M_MI;
                else
                    background = CORRIDOR_MI;
            }
        else if (monster->num_camera == CAMERA_8)
            background = CORRIDOR_M;
        else
            background = CORRIDOR;
    }
    else if (camera9on && camera->num_camera == CAMERA_12)
    {
        *camera_type = SIDEWAYS;
        if (monster->num_camera == CAMERA_12)
            background = COMMAND_ROOM_M;
        else
            background = COMMAND_ROOM;
    }
    else
    {
        *camera_type = FIXED;
        background = STATIC;
    }
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
 * \param img_stretchedW_game_res Largeur de l'image étirée dans la résolution du jeu.
 */
void game_handleEvent(SDL_Event *event, SDL_Window *window,int img_stretchedW_game_res)
{
    if (moniteurCameras == 0)
        buttons_handleEvent(event, window,img_stretchedW_game_res);
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
    BATTERY_DURATION = 2000.0f - night * 500;
    float drainRate = 100.0f / BATTERY_DURATION;

    if (doorCount == 2 && cameraButton())
        drainRate *= 4.0f;
    else if (doorCount == 2 && !cameraButton())
        drainRate *= 3.0f;
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
 * \brief Gère la difficulté du jeu en fonction de la nuit actuelle.
 *
 * En fonction de la nuit, le monster peut se déplacer plus ou moins fréquemment,
 * et le mimic peut être activé à partir de la nuit 2.
 *
 * \param night Numéro de la nuit actuelle (0, 1 ou 2).
 */

void difficulte(int night){
    switch(night){
        case 0:
            if(chance_deplacement() <= PERCENT_MOVE_MONSTER/7) {
                movement_opportunity(map, monster, 
                                    monster->num_camera % FIN_Y, 
                                    monster->num_camera / FIN_Y);
            }
            break;
        case 1:
            if(chance_deplacement() <= PERCENT_MOVE_MONSTER/2) {
                move_monster(map, monster, joueur);
            }
            else{
                movement_opportunity(map, monster,
                                    monster->num_camera % FIN_Y,
                                    monster->num_camera / FIN_Y);
            }
            break;
        case 2:
            if(chance_deplacement() < PERCENT_MOVE_MONSTER) {
                move_monster(map, monster, joueur);
            }
            else{
                movement_opportunity(map, monster,
                                    monster->num_camera % FIN_Y,
                                    monster->num_camera / FIN_Y);
            }
            mouvement_mimic(map, mimic);
            break;
        default:
            break;
    }
}


void update(){
/*=====NE JAMAIS ENLEVER J'AI TROP SOUFFERT=====*/
    // Déplacement du monster toutes les 5 secondes

    if(porteGaucheActive && monster->num_camera == PORTE_BAS){
        attaquer_joueur_echec(map, monster, joueur);
    }
    else if(porteDroiteActive && monster->num_camera == PORTE_HAUT){
        attaquer_joueur_echec(map, monster, joueur);
    }

    // Chaque nuit a sa difficulté d'IA
    difficulte(night);

    printf("nuit %d\n", night);
    printf("Le monster se déplace sur la caméra %d\n", monster->num_camera);
    duree = SDL_GetTicks();
    finish = (tempsFin - duree) - deltaTime;
    printf("Temps ecoule : %2.f\n", finish);
}
/*==============================================*/

/**
 * \brief Function to preload the assets at game launch.
 *
 * 
 * 
 * 
 *
 * \return 
 */
void preload_assets(SDL_Renderer* renderer) {

       // Load Textures (internimable)
    BLACKOUT = IMG_LoadTexture(renderer, "assets/img/INgame/BLACKOUT.png");

    R_D_OFF_LI_OFF_L_D_OFF_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_OFF_LI_OFF.png");
    R_D_OFF_LI_OFF_L_OFF_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W.png");
    R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M.png");
    R_D_OFF_LI_OFF_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_OFF_LI_ON.png");
    R_D_OFF_LI_OFF_L_D_ON_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_ON_LI_OFF.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M_W.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_OFF.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_D.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W_D.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_ON_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON_M.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON.png");
    R_D_OFF_LI_ON_L_D_ON_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_OFF.png");
    R_D_ON_LI_OFF_L_D_OFF_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_OFF_LI_OFF.png");
    R_D_ON_LI_OFF_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_OFF_LI_ON.png");
    R_D_ON_LI_ON_L_D_OFF_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_OFF.png");
    R_D_ON_LI_ON_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_ON.png");
    R_D_OFF_LI_ON_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON.png");
    R_D_OFF_LI_OFF_L_ON_LI_OFF_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_L_OFF_L_ON_LI_ON_M_W.png");
    R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W_D.png");
    R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W.png");
    R_D_OFF_LI_ON_L_D_ON_LI_OFF_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_OFF_M.png");
    R_D_ON_LI_ON_L_D_ON_LI_ON_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_ON_LI_ON_M_W_D.png");
    R_D_ON_LI_ON_L_D_ON_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_ON_LI_ON_M_W.png");
    R_D_ON_LI_ON_L_D_ON_LI_ON_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_ON_LI_ON_M.png");
    R_D_ON_LI_ON_L_D_ON_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_ON_LI_ON.png");


    R_D_OFF_LI_OFF_L_D_ON_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_ON_LI_ON_M_W.png");
    R_D_OFF_LI_OFF_L_D_ON_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_ON_LI_ON.png");
    R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W_D.png");
    R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W.png");

    R_D_OFF_LI_ON_L_D_ON_LI_ON_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_ON_M.png");
    R_D_OFF_LI_ON_L_D_ON_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_ON_LI_ON.png");
    R_D_ON_LI_OFF_L_D_OFF_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_OFF_LI_ON_M_W.png");
    R_D_ON_LI_OFF_L_D_OFF_LI_ON_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_OFF_LI_ON_M.png");

    R_D_ON_LI_OFF_L_D_ON_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_ON_LI_OFF.png");
    R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W_D.png");
    R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W.png");
    R_D_ON_LI_ON_L_D_OFF_LI_ON_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_ON_M.png");
    R_D_ON_LI_ON_L_D_OFF_LI_OFF_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_OFF_M_W_D.png");
    R_D_ON_LI_ON_L_D_ON_LI_OFF_M_W_D = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_ON_LI_OFF_M_W_D.png");
    R_D_ON_LI_ON_L_D_ON_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_ON_LI_OFF.png");

    R_D_ON_LI_OFF_L_D_ON_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_ON_LI_ON_M_W.png");
    R_D_ON_LI_OFF_L_D_ON_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_OFF_L_D_ON_LI_ON.png");

    MONITOR_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM.png");
    MONITOR_ROOM_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_M.png");
    MONITOR_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM.png");
    MONITOR_ROOM_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_M.png");
    MONITOR_ROOM_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_MI.png");
    MONITOR_ROOM_MI_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_MI_M.png");
    COMMAND_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/COMMAND_ROOM.png");
    COMMAND_ROOM_M = IMG_LoadTexture(renderer, "./assets/img/INgame/COMMAND_ROOM_M.png");
    CORRIDOR = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR.png");
    CORRIDOR_M = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR_M.png");
    CORRIDOR_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR_MI.png");
    CORRIDOR_M_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR_M_MI.png");
    STATIC = IMG_LoadTexture(renderer, "./assets/img/INgame/static.gif");
    MONSTER_L_DOOR_C = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_L_DOOR_C.png");
    MONSTER_L_DOOR_O_A = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_L_DOOR_O_A.png");
    MONSTER_L_DOOR_O = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_L_DOOR_O.png");
    L_D = IMG_LoadTexture(renderer, "./assets/img/INgame/L_D.png");
    L_D_M = IMG_LoadTexture(renderer, "./assets/img/INgame/L_D_M.png");
    L_D_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/L_D_MI.png");
    L_D_M_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/L_D_M_MI.png");
    R_D = IMG_LoadTexture(renderer, "./assets/img/INgame/R_D.png");
    R_D_M = IMG_LoadTexture(renderer, "./assets/img/INgame/R_D_M.png");
    R_D_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/R_D_MI.png");
    R_D_M_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/R_D_M_MI.png");
    MONSTER_R_DOOR_O_A = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_R_DOOR_O_A.png");
    MONSTER_R_DOOR_O = IMG_LoadTexture(renderer, "./assets/img/INgame/MONSTER_R_DOOR_O.png");
    cameraStatic = Mix_LoadMUS("assets/audio/sound/camera-static.wav");
    cameraSwitch = Mix_LoadWAV("assets/audio/sound/camera-switch.wav");
    doorKnocking = Mix_LoadWAV("assets/audio/sound/door_knocking.wav");

    monsterSpawn = Mix_LoadWAV("./assets/audio/sound/googoogaga.mp3");
    mimicMove = Mix_LoadWAV("./assets/audio/sound/mimic.wav");
    door_close = Mix_LoadWAV("./assets/audio/sound/door_close.wav");
    light_on = Mix_LoadWAV("./assets/audio/sound/light_on.wav");
    button_on = Mix_LoadWAV("./assets/audio/sound/button_on.wav");
    button_off = Mix_LoadWAV("./assets/audio/sound/button_off.wav");
    sad_mimic = Mix_LoadWAV("./assets/audio/sound/sad.wav");

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

    if (map == NULL)   map = malloc(sizeof(carte_t));
    if (camera == NULL)   camera = malloc(sizeof(carte_t));
    if (joueur == NULL)  joueur = malloc(sizeof(case_t));
    if (monster == NULL) monster = malloc(sizeof(case_t));
    if (mimic == NULL)    mimic = malloc(sizeof(case_t));
    
    //transition ici
    

    //POUR UN REDEMARAGE A 0
    game_initialise();

    srand(time(NULL));
    init_carte(map);
    init_joueur(joueur, map);
    init_camera(camera, map);
    placing_monster(map, monster);

    SDL_Event event;
    lastTime = SDL_GetTicks();
    monsterLastMove = SDL_GetTicks();
    int actual = -1;

    load_night();
    load_settings();
    if (night == ERROR)
    {
        save_night(0);
        load_night();
    }
    if (night > MAX_NIGHT /*A CHANGER AVEC LES NOUVELLES NUITS*/)
    {
        night = MAX_NIGHT;
        save_night(night);
        load_night();
    }
    if(night >= MAX_NIGHT){
        placement_mimic(map, mimic);
    }

    tempsDebut = SDL_GetTicks();

    tempsFin = tempsDebut + TEMPS_NUIT;
    duree = tempsDebut;
    finish = TEMPS_NUIT;
   
    /*=========GESTION PANORAMA==========*/
    int imgW, imgH;
    camera_type camera_type = GAME;
    direction_t camera_direction = GAUCHE;
    SDL_GetWindowSize(window, &windowW, &windowH);          // obtient la taille de la fenetre
    SDL_QueryTexture(background, NULL, NULL, &imgW, &imgH); // recup des infos background

    // PARAMETRES Camera Jeu
    int img_stretchedW_game_res = (int)(windowW * img_stretch_game_percentage); // nouvelle resolution de l'image
    int img_stretchedH_game_res = (int)(windowH * img_stretch_game_percentage); // nouvelle resolution de l'image
    int img_centerW_game_res = (int)(-img_stretchedW_game_res + windowW) / 2;   // milieu de l'image pour position largeur
    int img_centerH_game_res = (int)(-img_stretchedH_game_res + windowH) / 2;   // milieu de l'image pour position hauteur

    // PARAMETRES Camera
    int img_stretchedW_cam_res = (int)(windowW * img_stretch_cam_percentage); // nouvelle resolution de l'image
    int img_stretchedH_cam_res = (int)(windowH * img_stretch_cam_percentage); // nouvelle resolution de l'image
    int img_centerW_cam_res = (int)(-img_stretchedW_cam_res + windowW) / 2;   // milieu de l'image pour position largeur
    int img_centerH_cam_res = (int)(-img_stretchedH_cam_res + windowH) / 2;   // milieu de l'image pour position hauteur

    // RECT en fonction cam.
    SDL_Rect bgRect = {0, 0, windowW, windowH};
    SDL_Rect bgRectGame = {img_centerW_game_res, img_centerH_game_res, img_stretchedW_game_res, img_stretchedH_game_res};
    SDL_Rect bgRectCam = {img_centerW_cam_res, img_centerH_cam_res, img_stretchedW_cam_res, img_stretchedH_cam_res};

    camera_offset_x = bgRectGame.x; // initialisation de l'offset de la camera pour les boutons

    // ==========================================
    // --- 1. START FADING THE MENU MUSIC ---
    Mix_FadeOutMusic(1500); // 1.5 second fade out

    // --- 2. CINEMATIC FADE-IN FROM BLACK ---
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    

    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        SDL_RenderClear(renderer);
        
        lightCount = buttons_getLightCount();
        affichage(&camera_type); 
        
        SDL_RenderCopy(renderer, background, NULL, &bgRectGame);
        render_game(renderer, fontBattery, fontButtons, window, img_stretchedW_game_res);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer, NULL);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 60fps smooth fade
    }

    // --- 3. HOLD UNTIL MUSIC FADES OUT COMPLETELY ---
    // We keep rendering the normal game so the screen doesn't freeze
    // while waiting for the last few milliseconds of the music fade out!

    while(Mix_PlayingMusic()) {
        SDL_RenderClear(renderer);
        lightCount = buttons_getLightCount();
        affichage(&camera_type);
        SDL_RenderCopy(renderer, background, NULL, &bgRectGame);
        render_game(renderer, fontBattery, fontButtons, window, img_stretchedW_game_res);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // --- 4. START THE CREEPY IN-GAME AMBIENCE ---
    Mix_PlayMusic(cameraStatic, -1);
    // ==========================================

     while (!fin(map, monster) && !fin(map, mimic) && finish >= 0){
        if(cameraStatic || cameraSwitch) Mix_VolumeMusic(0);
        Uint32 currentTime = SDL_GetTicks();
        //Temps du monster avant chaque déplacement
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        //ESCAPE TO LEAVE THE GAME (no pause button otherwise no pressure)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                exit(0);
            game_handleEvent(&event, window,img_stretchedW_game_res);
        }

        game_update(deltaTime);

        SDL_RenderClear(renderer);

        //Call deplacement de jeu
        if(camera_type == GAME){
            panoramic_game(windowW, img_stretchedW_game_res, &bgRectGame);
        } else if(camera_type == SIDEWAYS){
            panoramic_camera(windowW, img_stretchedW_cam_res, &bgRectCam, &camera_direction);
        }
    
        int lightCount = buttons_getLightCount();


        //Update monster state (timer out of the loop to not crash it)
        if (currentTime - monsterLastMove >= monsterMoveDelay)
        {
            monsterLastMove = currentTime;
            update();
        }

        if (battery > 0 && !boutonLumieres)
        {
            change = VRAI;
        }

        //WHILE BATTERY > 0
        if(change == VRAI){
            if(actual != buttons_getDoorCount()){
                if(porteDroiteActive)
                    fermeture_portes_droite(joueur, map);
                if(!porteDroiteActive)
                    ouverture_porte_droite(map, joueur);
                if(porteGaucheActive)
                    fermeture_portes_gauche(joueur, map);
                if(!porteGaucheActive)
                    ouverture_porte_gauche(map, joueur);
                }
            }
        
        actual = buttons_getDoorCount();
        if (lightCount >= 2)
            background = R_D_OFF_LI_ON_L_D_OFF_LI_ON;

        /*=========DIFFERENTS AFFICHAGES EN FONCTION DES LUMIERES ET DES PORTES==========*/
        affichage(&camera_type);
        /*=========================================================*/
        if (camera_type == GAME)
        {
            SDL_RenderCopy(renderer, background, NULL, &bgRectGame);
        }
        else if (camera_type == SIDEWAYS)
        {
            SDL_RenderCopy(renderer, background, NULL, &bgRectCam);
        }
        else
        {
            SDL_RenderCopy(renderer, background, NULL, &bgRect);
        }

        render_game(renderer, fontBattery, fontButtons, window, img_stretchedW_game_res);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    if(finish <=0 && !fin(map, monster) && !fin(map, mimic)){
        if(night == MAX_NIGHT){
            transitionWin(renderer, window);
            Mix_PlayMusic(sOst, -1);
            Mix_VolumeMusic(musicVol);
            render_credits(renderer, window);
        }
        else{
            transitionNuit(renderer, window, night);
            night++;
            save_night(night);
            Mix_PlayMusic(sOst, -1);
            Mix_VolumeMusic(musicVol);
        }
    }
}

void game_final_cleanup(){
    if (map != NULL) {
        detruire_carte(map); 
        map = NULL;
    }
    if (joueur != NULL)
    {
        joueur = NULL;
    }
    if (camera != NULL)
    {
        camera = NULL;
    }
    if (monster != NULL) {
        monster = NULL;
    }
    if (mimic != NULL)
    {
        mimic = NULL;
    }
    Mix_FreeMusic(cameraStatic);
    Mix_FreeChunk(cameraSwitch);
    Mix_FreeChunk(doorKnocking);
    Mix_FreeChunk(monsterSpawn);
    Mix_FreeChunk(mimicMove);
    Mix_FreeChunk(door_close);
    Mix_FreeChunk(light_on);
    Mix_FreeChunk(button_on);
    Mix_FreeChunk(button_off);
}
