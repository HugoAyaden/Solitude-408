


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
#define TEMPS_NUIT 360000
#define monsterMoveDelay 5000
#define UPDATE_TIME 1000.0f
#define NIGHT_1 0
#define NIGHT_2 1
#define NIGHT_3 2

/**
 * \brief Updates the displayed camera view.
 *
 * The camera numbers follow the layout defined in "map.c",
 * not the in-game numbering, for realism purposes.
 *
 * \param camera Pointer to the currently selected camera.
 * \param monster Pointer to the monster position.
 * \param camera_type Pointer to the current camera display mode.
 */
void change_camera(case_t * camera, case_t * monster, camera_type *camera_type){
    static int last_camera = -1;
    Mix_VolumeMusic(masterVol);
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
    
    else if(camera5on && camera->num_camera == CAMERA_11){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_11){
                if(monster->num_camera == CAMERA_11)
                    background = MIMIC_CORRIDOR_MI_M;
                else
                    background = MIMIC_CORRIDOR_MI;
            }
        else if (monster->num_camera == CAMERA_11)
            background = MIMIC_CORRIDOR_M;
        else
            background = MIMIC_CORRIDOR;
    }

     else if(camera6on && camera->num_camera == CAMERA_2){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_2){
                if(monster->num_camera == CAMERA_2)
                    background = HALLWAY_MI_M;
                else
                    background = HALLWAY_MI;
            }
        else if (monster->num_camera == CAMERA_2)
            background = HALLWAY_M;
        else
            background = HALLWAY;
    }

    else if(camera7on && camera->num_camera == CAMERA_4){
        *camera_type = SIDEWAYS;
        background = SKY;
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

    else if(camera3on && camera->num_camera == CAMERA_9){
        *camera_type = SIDEWAYS;
        if(mimic != NULL && mimic->num_camera == CAMERA_9){
                if(monster->num_camera == CAMERA_9)
                    background = FRONT_WALL_MI_M;
                else
                    background = FRONT_WALL_MI;
            }
        else if (monster->num_camera == CAMERA_9)
            background = FRONT_WALL_M;
        else
            background = FRONT_WALL;
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
        if(mimic != NULL && mimic->num_camera == CAMERA_12){
                if(monster->num_camera == CAMERA_12)
                    background = COMMAND_ROOM_MI_M;
                else
                    background = COMMAND_ROOM_MI;
            }
        else if (monster->num_camera == CAMERA_12)
            background = COMMAND_ROOM_M;
        else
            background = COMMAND_ROOM;
    }
    else
    {
        *camera_type = FIXED;
        background = STATIC_CAM;
    }
}

/**
 * \brief Returns the number of active doors.
 *
 * \return Number of currently active doors.
 */
int buttons_getDoorCount()
{
    return porteGaucheActive + porteDroiteActive;
}

/**
 * \brief Returns the number of active lights.
 *
 * \return Number of currently active lights.
 */
int buttons_getLightCount()
{
    return lumiereGaucheActive + lumiereDroiteActive;
}

/**
 * \brief Handles global game events.
 *
 * Dispatches SDL events to the appropriate subsystem,
 * such as the standard buttons or the camera buttons.
 *
 * \param event SDL event received.
 * \param window SDL window used by the UI.
 * \param img_stretchedW_game_res Width of the stretched game image.
 */
void game_handleEvent(SDL_Event *event, SDL_Window *window,int img_stretchedW_game_res)
{
    if (moniteurCameras == 0)
        buttons_handleEvent(event, window,img_stretchedW_game_res);
    else
        camera_buttons_handleEvent(event, window);
}

/**
 * \brief Initializes the player's battery.
 */
void battery_init()
{
    battery = 100.0f;
}
/**
 * \brief Initializes the main game systems.
 *
 * This includes the battery and all button states.
 */
void game_initialise()
{
    battery_init();
    buttons_init();
}

/**
 * \brief Updates the battery level.
 *
 * Battery consumption depends on the number of closed doors
 * and the number of active lights.
 *
 * \param deltaTime Time elapsed since the last frame.
 * \param doorCount Number of closed doors.
 * \param lightCount Number of active lights.
 */
void battery_update(float deltaTime, int doorCount, int lightCount)
{
    BATTERY_DURATION = 2000.0f - night * 500;
    float drainRate = 100.0f / BATTERY_DURATION;

    if (doorCount == 2 && cameraButton())
        drainRate *= 4.0f; // 2 doors + camera monitor : max drain
    else if (doorCount == 2 && !cameraButton())
        drainRate *= 3.0f; // 2 doors : high drain
    else if (doorCount == 1)
        drainRate *= 2.0f; // 1 door : moderate drain

    //each added light increases drain by 100% (1 light = 2x drain, 2 lights = 3x drain)
    if (lightCount > 0)
        drainRate *= (1.0f + lightCount);

    battery -= drainRate * deltaTime;

    if (battery < 0)
        battery = 0;
}

/**
 * \brief Updates the main game logic.
 *
 * Currently updates battery consumption based on door and light usage.
 *
 * \param deltaTime Time elapsed since the last frame.
 */
void game_update(float deltaTime)
{
    int doorCount = buttons_getDoorCount();
    int lightCount = buttons_getLightCount();

    battery_update(deltaTime, doorCount, lightCount);
}

/**
 * \brief Adjusts the game difficulty according to the current night.
 *
 * Depending on the night, the monster may move more or less often,
 * and the mimic becomes active starting from night 2.
 *
 * \param night Current night number.
 */
void difficulte(int night){
    switch(night){
        case NIGHT_1:
            if(chance_deplacement() <= PERCENT_MOVE_MONSTER/7) {
                movement_opportunity(map, monster);
            }
            break;
        case NIGHT_2:
            if(chance_deplacement() <= PERCENT_MOVE_MONSTER/2) {
                move_monster(map, monster, joueur);
            }
            else{
                movement_opportunity(map, monster);
            }
            break;
        case NIGHT_3:
        //If both monsters are attacking ath the same time
        if((monster->num_camera == map->cases[X_JOUEUR-1][Y_JOUEUR].num_camera ||  monster->num_camera == map->cases[X_JOUEUR+1][Y_JOUEUR].num_camera) &&
             (mimic->num_camera == map->cases[X_JOUEUR-1][Y_JOUEUR].num_camera || mimic->num_camera == map->cases[X_JOUEUR+1][Y_JOUEUR].num_camera)){
                //only the mimic moves (then, the monster)
             mouvement_mimic(map, mimic);
             }
             //else they both move (balancing issues)
                if(chance_deplacement() < PERCENT_MOVE_MONSTER) {
                    move_monster(map, monster, joueur);
                    mouvement_mimic(map, mimic);
                }
                else{
                    movement_opportunity(map, monster);
                    mouvement_mimic(map, mimic);
                }
            break;
        default:
            break;
    }
}

/**
 * \brief Updates the monster and door logic for the current frame.
 *
 * Handles door-triggered attacks, applies AI difficulty behavior,
 * and updates the remaining time for the current night.
 */
void update(){
    // Monster moves each monsterMoveDelay milliseconds, if the door is closed when attacking the attack fails

    if(porteGaucheActive && monster->num_camera == PORTE_BAS){
        attaquer_joueur_echec(map, monster, joueur);
    }
    else if(porteDroiteActive && monster->num_camera == PORTE_HAUT){
        attaquer_joueur_echec(map, monster, joueur);
    }

    // Eaxh night got it's own difficulty, the monster move more often and the mimic become active at night 2
    difficulte(night);

    duree = SDL_GetTicks();
    finish = (tempsFin - duree) - deltaTime;
    /*Debugging outputs
    printf("nuit %d\n", night);
    printf("Le monster se déplace sur la caméra %d\n", monster->num_camera);
    printf("Temps ecoule : %2.f\n", finish);
    */
}

/**
 * \brief Preloads all game assets.
 *
 * Loads textures, animations, and sounds needed during gameplay.
 *
 * \param renderer SDL renderer used for texture creation.
 */
void preload_assets(SDL_Renderer* renderer) {

       // Load Textures (unbearable to read, but it works)
    BLACKOUT = IMG_LoadTexture(renderer, "assets/img/INgame/BLACKOUT.png");


    /* GUIDE ON HOW TO READ THIS 
    
    Every single name goes by the order :

    Right_Door_(ON/OFF)_LIght_(ON/OFF)_Left_Door_(ON/OFF)_LIghts_(ON/OFF)_Monster_(M if monster is on the camera, nothing otherwise)_(W if the monster is at the window)_(D if it_s the right door (nothing on left door))
    SO R_D_OFF_LI_OFF_L_D_OFF_LI_OFF = Right Door OFF, Right Light OFF, Left Door OFF, Left Light OFF, No Monster
    
    */
    /* MAIN ROOMS ASSETS */
    R_D_OFF_LI_OFF_L_D_OFF_LI_OFF = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_OFF_LI_OFF.png");
    R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W = IMG_LoadTexture(renderer, "assets/img/INgame/R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W.png");
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

    /* CAMERAS ROOM ASSETS */
    SKY = IMG_LoadTexture(renderer, "./assets/img/INgame/SKY.png");
    MONITOR_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM.png");
    MONITOR_ROOM_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_M.png");
    MONITOR_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM.png");
    MONITOR_ROOM_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_M.png");
    MONITOR_ROOM_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_MI.png");
    MONITOR_ROOM_MI_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MONITOR_ROOM_MI_M.png");
    COMMAND_ROOM = IMG_LoadTexture(renderer, "./assets/img/INgame/COMMAND_ROOM.png");
    COMMAND_ROOM_M = IMG_LoadTexture(renderer, "./assets/img/INgame/COMMAND_ROOM_M.png");
    COMMAND_ROOM_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/COMMAND_ROOM_MI.png");
    COMMAND_ROOM_MI_M = IMG_LoadTexture(renderer, "./assets/img/INgame/COMMAND_ROOM_MI_M.png");
    MIMIC_CORRIDOR = IMG_LoadTexture(renderer, "./assets/img/INgame/MIMIC_CORRIDOR.png");
    MIMIC_CORRIDOR_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MIMIC_CORRIDOR_M.png");
    MIMIC_CORRIDOR_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/MIMIC_CORRIDOR_MI.png");
    MIMIC_CORRIDOR_MI_M = IMG_LoadTexture(renderer, "./assets/img/INgame/MIMIC_CORRIDOR_MI_M.png");
    FRONT_WALL = IMG_LoadTexture(renderer, "./assets/img/INgame/FRONT_WALL.png");
    FRONT_WALL_M = IMG_LoadTexture(renderer, "./assets/img/INgame/FRONT_WALL_M.png");
    FRONT_WALL_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/FRONT_WALL_MI.png");
    FRONT_WALL_MI_M = IMG_LoadTexture(renderer, "./assets/img/INgame/FRONT_WALL_MI_M.png");
    CORRIDOR = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR.png");
    CORRIDOR_M = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR_M.png");
    CORRIDOR_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR_MI.png");
    CORRIDOR_M_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/CORRIDOR_M_MI.png");
    HALLWAY = IMG_LoadTexture(renderer, "./assets/img/INgame/HALLWAY.png");
    HALLWAY_M = IMG_LoadTexture(renderer, "./assets/img/INgame/HALLWAY_M.png");
    HALLWAY_MI = IMG_LoadTexture(renderer, "./assets/img/INgame/HALLWAY_MI.png");
    HALLWAY_MI_M = IMG_LoadTexture(renderer, "./assets/img/INgame/HALLWAY_MI_M.png");
    STATIC_CAM = IMG_LoadTexture(renderer, "./assets/img/INgame/static_cam.gif");
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

    /* Camera static loaded as a music and played during all the game just put at 0 when its not used*/
    cameraStatic = Mix_LoadMUS("assets/audio/sound/camera-static.wav");

    /* SOUND EFFECTS */
    monsterSpawn = Mix_LoadWAV("./assets/audio/sound/googoogaga.mp3");
    mimicMove = Mix_LoadWAV("./assets/audio/sound/mimic.wav");
    door_close = Mix_LoadWAV("./assets/audio/sound/door_close.wav");
    light_on = Mix_LoadWAV("./assets/audio/sound/light_on.wav");
    button_on = Mix_LoadWAV("./assets/audio/sound/button_on.wav");
    button_off = Mix_LoadWAV("./assets/audio/sound/button_off.wav");
    sad_mimic = Mix_LoadWAV("./assets/audio/sound/sad.wav");
    attack = Mix_LoadWAV("./assets/audio/sound/attack_monster.wav");
    static_sound = Mix_LoadWAV("./assets/audio/sound/static_sound.mp3");
    cameraSwitch = Mix_LoadWAV("assets/audio/sound/camera-switch.wav");
    doorKnocking = Mix_LoadWAV("assets/audio/sound/door_knocking.wav");

    /* ANIMATIONS */
    monster_death = IMG_LoadAnimation("./assets/img/INgame/monster_death.gif");
    mimic_death = IMG_LoadAnimation("./assets/img/INgame/mimic_death.gif");
    STATIC = IMG_LoadAnimation("./assets/img/INgame/static.gif");

}

/**
 * \brief Initializes the game and starts the main gameplay loop.
 *
 * Allocates game objects, loads saved progress and settings,
 * initializes the map, player, cameras, and monster, then runs
 * the main rendering and event loop.
 *
 * \param renderer SDL renderer used for drawing.
 * \param window SDL window used for sizing and rendering setup.
 * \param fontBattery Font used for battery display.
 * \param fontButtons Font used for button labels.
 */
void game_init(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* fontBattery, TTF_Font* fontButtons) {

    if (map == NULL)   map = malloc(sizeof(carte_t));
    if (camera == NULL)   camera = malloc(sizeof(carte_t));
    if (joueur == NULL)  joueur = malloc(sizeof(case_t));
    if (monster == NULL) monster = malloc(sizeof(case_t));
    if (mimic == NULL)    mimic = malloc(sizeof(case_t));
    

    //RESET ALL GAME PROGRESS VARIABLES
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
    //prevent the game to go beyond the max nights that are in game
    if (night > MAX_NIGHT /*To change if you add more nights*/)
    {
        night = MAX_NIGHT;
        save_night(night);
        load_night();
    }
    //Initialize the mimic if the player has reached night 2
    if(night >= MAX_NIGHT){
        placement_mimic(map, mimic);
    }

    // --- START THE GAME TIMER ---
    tempsDebut = SDL_GetTicks();

    tempsFin = tempsDebut + TEMPS_NUIT;
    duree = tempsDebut;
    finish = TEMPS_NUIT;
   
    /*=========PANORAMA BEHAVIOR==========*/
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
    // We keep rendering the normal game so the screen doesn't freeze while waiting for the last few milliseconds of the music fade out

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

     while (!fin(map, monster) && !fin(map, mimic) && finish >= 0){
        if(cameraStatic || cameraSwitch) 
            Mix_VolumeMusic(0);
        Uint32 currentTime = SDL_GetTicks();
        //Monster time update time
        deltaTime = (currentTime - lastTime) / UPDATE_TIME;
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

        //How the camera behave depending the game mode (normal or camera monitor)
        if(camera_type == GAME){
            panoramic_game(windowW, img_stretchedW_game_res, &bgRectGame);
        } else if(camera_type == SIDEWAYS){
            panoramic_camera(windowW, img_stretchedW_cam_res, &bgRectCam, &camera_direction);
        }


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

        //WHILE BATTERY > 0 THE BUTTONS CAN BE PRESSED
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

        //Main rendering function, used for every rendering of the game depending the states (camera, monster, mimic, doors, lights, etc...)
        affichage(&camera_type);


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
    // How the game end depending if the player win or lose (monster or mimic attack)
    if(finish <=0 && !fin(map, monster) && !fin(map, mimic)){
        //If the player wins and has finished the last night
        if(night == MAX_NIGHT){
            transitionWin(renderer, window);
            Mix_PlayMusic(sOst, -1);
            Mix_VolumeMusic(musicVol);
            render_credits(renderer, window);
        }
        //If the player wins but it wasn't the last night (transition to the next night)
        else{
            night++;
            save_night(night);
            transitionNuit(renderer, window, night);
            Mix_PlayMusic(sOst, -1);
            Mix_VolumeMusic(musicVol);
        }
    }
    //If the monster kills the player (screamer)
    else if(fin(map, monster)){
        play_gif(monster_death, renderer, windowW, windowH, attack, 1);
        play_gif(STATIC, renderer, windowW, windowH, static_sound, 4);
        Mix_PlayMusic(sOst, -1);
        Mix_VolumeMusic(musicVol);
    }
    //If the mimic kills the player (screamer)
    else if(fin(map, mimic)){
        play_gif(mimic_death, renderer, windowW, windowH, attack, 1);
        play_gif(STATIC, renderer, windowW, windowH, static_sound, 4);
        Mix_PlayMusic(sOst, -1);
        Mix_VolumeMusic(musicVol);
    }
}

/**
 * \brief Frees all game resources and clears allocated memory.
 *
 * Releases map data, dynamically allocated entities, and loaded audio assets.
 */
void game_final_cleanup(){
    if (map != NULL) {
        detruire_carte(map); 
        map = NULL;
    }
    if (joueur != NULL)
    {
        free(joueur);
        joueur = NULL;
    }
    if (camera != NULL)
    {
        free(camera);
        camera = NULL;
    }
    if (monster != NULL) {
        free(monster);
        monster = NULL;
    }
    if (mimic != NULL)
    {
        free(mimic);
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
    Mix_FreeChunk(sad_mimic);
    Mix_FreeChunk(attack);
    IMG_FreeAnimation(monster_death);
    IMG_FreeAnimation(mimic_death);
    IMG_FreeAnimation(STATIC);
}
