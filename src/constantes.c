/**
 * \file constants.c
 * \brief Initialisation of every variable.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#include "constantes.h"


int PERCENT_MOVE_MIMIC = 20;
float PERCENT_MOVE_MONSTER = 70;

float battery = 100.0f;
int porteGaucheActive = 0;
int porteDroiteActive = 0;
int lumiereGaucheActive = 0;
int lumiereDroiteActive = 0;
int tempsDebut = 0;
int tempsFin = 0;
int change = 1;
float finish = 0.0f;
int duree = 0;
int moniteurCameras = 0;
int camera1on = 0;
int camera2on = 0;
int camera3on = 0;
int camera4on = 0;
int camera5on = 0;
int camera6on = 0;
int camera7on = 0;
int camera8on = 0;
int camera9on = 0;
float BATTERY_DURATION = 720.0f;
int cameraMap = 0;
int windowW = 0;
int windowH = 0;
booleen_t boutonLumieres = FAUX;
carte_t *map = NULL;
case_t *joueur = NULL;
case_t *monster = NULL;
case_t *mimic = NULL;
SDL_Texture *background = NULL;
SDL_Texture *BLACKOUT = NULL;
SDL_Texture *MONITOR_ROOM = NULL;
SDL_Texture *MONITOR_ROOM_M = NULL;
SDL_Texture *MONITOR_ROOM_MI = NULL;
SDL_Texture *MONITOR_ROOM_MI_M = NULL;
SDL_Texture *COMMAND_ROOM = NULL;
SDL_Texture *COMMAND_ROOM_M = NULL;
SDL_Texture *STATIC = NULL;
SDL_Texture *MONSTER_L_DOOR_C = NULL;
SDL_Texture *MONSTER_L_DOOR_O_A = NULL;
SDL_Texture *MONSTER_L_DOOR_O = NULL;
SDL_Texture *MONSTER_R_DOOR_C = NULL;
SDL_Texture *MONSTER_R_DOOR_O_A = NULL;
SDL_Texture *MONSTER_R_DOOR_O = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_OFF  = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_OFF_LI_ON_M_W  = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_ON_LI_OFF = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M_W = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_OFF = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_D = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W_D = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W_D = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF_M = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON_M_W_D = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON_M_W = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON_M = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF = NULL;
SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_OFF = NULL;
SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_ON = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_OFF_M = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_OFF = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_ON_LI_OFF_ON_M_W = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_ON_LI_ON_M_W = NULL;
SDL_Texture *R_D_OFF_LI_OFF_L_D_ON_LI_ON = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W_D = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W = NULL;

SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON_M = NULL;
SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON = NULL;
SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_ON_M_W = NULL;
SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_ON_M = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_OFF_M_W_D = NULL;

SDL_Texture *R_D_ON_LI_OFF_L_D_ON_LI_ON_M_W = NULL;
SDL_Texture *R_D_ON_LI_OFF_L_D_ON_LI_ON = NULL;

SDL_Texture *R_D_ON_LI_OFF_L_D_ON_LI_OFF = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W_D = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON_M = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_OFF_M_W_D = NULL;
SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_OFF = NULL;
SDL_Texture *L_D = NULL;
SDL_Texture *L_D_M = NULL;
SDL_Texture *L_D_MI = NULL;
SDL_Texture *L_D_M_MI = NULL;
SDL_Texture *R_D = NULL;
SDL_Texture *R_D_M = NULL;
SDL_Texture *R_D_MI = NULL;
SDL_Texture *R_D_M_MI = NULL;
SDL_Texture *CORRIDOR = NULL;
SDL_Texture *CORRIDOR_M = NULL;
SDL_Texture *CORRIDOR_MI = NULL;
SDL_Texture *CORRIDOR_M_MI = NULL;
Uint32 lastSound = 0;
Uint32 now = 0;
Mix_Chunk *song = NULL;
case_t *camera = NULL;
Uint32 currentTime = 0;
Uint32 monsterLastMove = 0;
float deltaTime = 0.0f;
int w = 1920;
int h = 1080;
int run = true;
int trans = false;
float progress = 0.0f;
GameState state = STATE_MENU;
GameState next = STATE_MENU;
int masterVol = 80;
int musicVol = 60;
int brightness = 50;
int mouseSens = 40;
int screenModeIndex = 1;
int resIndex = 2;
int night = -1;
int overBack = 0;
Mix_Chunk *sGlitch = NULL;
SDL_Texture *settingsStaticTex = NULL;
SDL_Texture *settingsBG = NULL;
Uint32 saveNotificationTimer = 0;
const char *screenModes[] = {"WINDOWED", "FULLSCREEN", "BORDERLESS"};
const char *resolutions[] = {"3840x2160", "2560x1440", "1920x1080", "1440x900"};
SDL_Texture *bgTexture = NULL;
SDL_Texture *titleText = NULL;
SDL_Rect titleRect;
MenuButton buttons[5];
int assetsLoaded = false;
Uint32 lastTime = 0;
int pixel_offset_game = 20;         //decalage pixel deplacement jeu
int pixel_offset_cam = 1;           //decalage pixel deplacement camera
float res_percentage = 0.95;        //pourcentage pour determiner zone de deplacement camera
int img_limit_left = 0;             //limite de position de l'image a gauche
float img_stretch_game_percentage = 1.6; //pourcentage d'etendue de l'image jeu
float img_stretch_cam_percentage = 1.1; //pourcentage d'etendue de l'image cam
int camera_offset_x = 0;                //PAS UNE CONSTANTE, recup la position de l'image pour calculer la position des boutons
int spacing_amount = 6;                 //pourcentage de l'image de jeu ou les boutons de portes sont affichés, plus c'est petit plus ils sont proches du centre
int lightCount = 0;
<<<<<<< HEAD
=======
Mix_Music* sOst = NULL;
>>>>>>> dev
Mix_Music* cameraStatic = NULL;
Mix_Chunk* cameraSwitch = NULL;
Mix_Chunk* doorKnocking = NULL;

Mix_Chunk* monsterSpawn = NULL;
<<<<<<< HEAD
Mix_Chunk* mimicMove = NULL;
=======
Mix_Chunk* mimicMove = NULL;
Mix_Chunk* door_close = NULL;
Mix_Chunk* light_on = NULL;
Mix_Chunk* button_on = NULL;
Mix_Chunk* button_off = NULL;
Mix_Chunk* sad_mimic = NULL;
>>>>>>> dev
