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
#define TEMPS_NUIT 1000
#define monsterMoveDelay 3000

/**
 * \brief Permet l'affichage des cameras
 *
 * Les numeros des cameras sont suivant le schéma de "map.c"
 * et non celui du jeu (par souci de réalisme).
 */
void change_camera(case_t * camera, case_t * monster){
    static int last_camera = -1;
    Mix_VolumeMusic(30);
    if(camera->num_camera != last_camera){
        Mix_PlayChannel(-1, cameraSwitch, 0);
        last_camera = camera->num_camera;
    }

    if(camera8on && camera->num_camera == CAMERA_1){
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
    else if(camera9on && camera->num_camera == CAMERA_12){
        if (monster->num_camera == CAMERA_12)
            background = COMMAND_ROOM_M;
        else
            background = COMMAND_ROOM;
    }
    else
        background = STATIC;
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
        BATTERY_DURATION = 2000.0f - night*500;
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
            if(chance_deplacement() <= 1) {
                movement_opportunity(map, monster, 
                                    monster->num_camera % FIN_Y, 
                                    monster->num_camera / FIN_Y);
            }
            break;
        case 1:
            if(chance_deplacement() <= 5) {
                move_monster(map, monster, joueur);
            }
            else{
                movement_opportunity(map, monster,
                                    monster->num_camera % FIN_Y,
                                    monster->num_camera / FIN_Y);
            }
            break;
        case 2:
            if(chance_deplacement() < 7) {
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

        //Chaque nuit a sa difficulté d'IA
    difficulte(night);


    printf("nuit %d\n", night);
    printf("Le monster se déplace sur la caméra %d\n", monster->num_camera);
    duree = SDL_GetTicks();
    finish = (tempsFin-duree)+deltaTime;
    printf("Temps ecoule : %2.f\n", finish);
}
    /*==============================================*/

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
R_D_ON_LI_ON_L_D_OFF_LI_OFF_M = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_l_D_OFF_LI_OFF_M.png");
R_D_ON_LI_ON_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_ON_LI_ON_L_D_OFF_LI_ON.png");
R_D_OFF_LI_ON_L_D_OFF_LI_ON = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_ON_L_D_OFF_LI_ON.png");
R_D_OFF_LI_OFF_L_ON_LI_OFF_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_L_OFF_L_ON_LI_ON_M_W.png");

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

    if (map == NULL)   map = malloc(sizeof(carte_t));
    if (camera == NULL)   camera = malloc(sizeof(carte_t));
    if (joueur == NULL)  joueur = malloc(sizeof(case_t));
    if (monster == NULL) monster = malloc(sizeof(case_t));
    if (mimic == NULL)    mimic = malloc(sizeof(case_t));
    
    //transition ici
    

    //POUR UN REDEMARAGE A 0
    game_initialise();
    Mix_PlayMusic(cameraStatic, -1);
    
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
    if(night == ERROR){
        save_night(0);
        load_night();
    }
    if(night >MAX_NIGHT /*A CHANGER AVEC LES NOUVELLES NUITS*/ ){
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
            game_handleEvent(&event, window);
        }

        game_update(deltaTime);

        SDL_RenderClear(renderer);
        SDL_GetWindowSize(window, &windowW, &windowH);
        SDL_Rect bgRect = {0, 0, windowW, windowH};
        lightCount = buttons_getLightCount();


        //Update monster state (timer out of the loop to not crash it)
        if (currentTime - monsterLastMove >= monsterMoveDelay)
        {
            monsterLastMove = currentTime;
        update();
        }

        if(battery > 0 && !boutonLumieres){
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


        /*=DIFFERENTS DISPLAYS OF EACH BACKGROUND=*/
        affichage();
        /*========================================*/

        SDL_RenderCopy(renderer, background, NULL, &bgRect);

        render_game(renderer, fontBattery, fontButtons, window);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    if(finish <=0 && !fin(map, monster)){
        transitionNuit(renderer, window, night);
        night++;
        save_night(night);
    }
}

void game_final_cleanup(){
    if (map != NULL) {
        detruire_carte(map); 
        map = NULL;
    }
    if (joueur != NULL) {
        joueur = NULL;
    }
    if (camera != NULL) {
        camera = NULL;
    }
    if (monster != NULL) {
        monster = NULL;
    }
    if (mimic != NULL) {
        mimic = NULL;
    }
    
}