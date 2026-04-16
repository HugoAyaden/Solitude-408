/**
 * \file constants.h
 * \brief Header for initialisation of every variable.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include "commun.h"

#define true 1
#define false 0

extern int PERCENT_MOVE_MIMIC;
extern float PERCENT_MOVE_MONSTER;

/**
 * \brief Represents a camera room cell in the game map.
 *
 * Each cell stores its camera number, whether the light is turned on,
 * whether the room is accessible, and pointers to neighboring cells.
 */
typedef struct case_s {
    int num_camera;
    booleen_t lumiere;
    booleen_t acess;
    struct case_s *voisin_haut;
    struct case_s *voisin_droit;
    struct case_s *voisin_gauche;
    struct case_s *voisin_bas;
} case_t;

/**
 * \brief Game map container storing all cells.
 *
 * The map is stored as a fixed-size 2D array of cells indexed by
 * camera coordinates.
 */
typedef struct carte_s {
    case_t cases[FIN_X][FIN_Y];
} carte_t;

/**
 * \brief Represents a menu button with graphics and label.
 */
typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
    const char *label;
} MenuButton;

/**
 * \brief Node used for BFS pathfinding queue.
 *
 * Stores the current cell and the parent cell used to reconstruct paths.
 */
typedef struct {
    case_t *cell;
    case_t *parent;
} queue_node_t;

/**
 * \brief Screen mode options for the application window.
 */
typedef enum {WINDOWED, FULLSCREEN, BORDERLESS} screen_t;

/**
 * \brief Available high-level game states.
 */
typedef enum {
    STATE_MENU,
    STATE_SETTINGS,
    STATE_NEW_GAME,
    STATE_CONTINUE,
    STATE_CREDITS
} GameState;


/* ============CAMERAS.H==================== */
typedef enum {
    CAMERA_0, CAMERA_1, CAMERA_2, CAMERA_3,
    CAMERA_4, CAMERA_5, CAMERA_6, CAMERA_7,
    CAMERA_8, CAMERA_9, CAMERA_10, CAMERA_11,
    CAMERA_12, CAMERA_13, CAMERA_14, CAMERA_15
} num_cameras;

typedef struct {
    booleen_t active;
} camera_t;

typedef enum {
    HAUT, 
    DROITE, 
    BAS, 
    GAUCHE
} direction_t;

/**
 * \brief Every camera type in game. 
 */
typedef enum {
    FIXED,
    GAME,
    SIDEWAYS
} camera_type;


extern int moniteurCameras;
extern int camera1on;
extern int camera2on;
extern int camera3on;
extern int camera4on;
extern int camera5on;
extern int camera6on;
extern int camera7on;
extern int camera8on;
extern int camera9on;

/*=============================================*/

extern float battery;
extern int porteGaucheActive;
extern int porteDroiteActive;
extern int lumiereGaucheActive;
extern int lumiereDroiteActive;
extern int tempsDebut;
extern int tempsFin;
extern int change;
extern float finish;
extern int duree;
extern float BATTERY_DURATION;
extern int cameraMap;
extern int windowW;
extern int windowH;
extern int gameOver_monstre;
extern booleen_t boutonLumieres;
/*===============EVERY ENTITIES IN GAME==================*/
extern carte_t *map;
extern case_t *joueur;
extern case_t *monster;
extern case_t *mimic;
/*========================================================*/

/*=============================EVERY ASSET THAT NEEDS TO BE LOADED====================================*/
extern SDL_Texture *background;
extern SDL_Texture *BLACKOUT;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_OFF;
extern SDL_Texture *R_D_OFF_LI_OFF_L_OFF_LI_ON_M_W;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M ;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON ;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_ON_LI_OFF ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M_W ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_OFF ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_D ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W_D ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON_M ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_OFF_LI_ON ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF ;
extern SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_OFF ;
extern SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_ON ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_L_I_OFF_M ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_OFF_M ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_OFF ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON ;
extern SDL_Texture *R_D_OFF_LI_OFF_L_ON_LI_OFF_ON_M_W ;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_ON_LI_ON_M_W ;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_ON_LI_ON ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W_D ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W ;

extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON_M ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_ON ;
extern SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_ON_M_W ;
extern SDL_Texture *R_D_ON_LI_OFF_L_D_OFF_LI_ON_M ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_OFF_M_W_D;

extern SDL_Texture *R_D_ON_LI_OFF_L_D_ON_LI_ON_M_W;
extern SDL_Texture *R_D_ON_LI_OFF_L_D_ON_LI_ON;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W;
extern SDL_Texture *R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W_D ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON_M_W_D ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON_M_W ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON_M ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_ON ;
extern SDL_Texture *R_D_OFF_LI_ON_L_D_ON_LI_OFF_M;

extern SDL_Texture *R_D_ON_LI_OFF_L_D_ON_LI_OFF ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W_D ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_OFF_LI_ON_M ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_OFF_M_W_D ;
extern SDL_Texture *R_D_ON_LI_ON_L_D_ON_LI_OFF ;
extern SDL_Texture *SKY;
extern SDL_Texture *MONITOR_ROOM;
extern SDL_Texture *MONITOR_ROOM_M;
extern SDL_Texture *MONITOR_ROOM_MI;
extern SDL_Texture *MONITOR_ROOM_MI_M;
extern SDL_Texture *COMMAND_ROOM;
extern SDL_Texture *COMMAND_ROOM_M;
extern SDL_Texture *COMMAND_ROOM_MI;
extern SDL_Texture *COMMAND_ROOM_MI_M;
extern IMG_Animation *STATIC;
extern SDL_Texture *STATIC_CAM;
extern SDL_Texture *MONSTER_L_DOOR_C;
extern SDL_Texture *MONSTER_L_DOOR_O_A;
extern SDL_Texture *MONSTER_L_DOOR_O;
extern SDL_Texture *MONSTER_R_DOOR_C;
extern SDL_Texture *MONSTER_R_DOOR_O_A;
extern SDL_Texture *MONSTER_R_DOOR_O;
extern SDL_Texture *L_D;
extern SDL_Texture *L_D_M;
extern SDL_Texture *L_D_MI;
extern SDL_Texture *L_D_M_MI;
extern SDL_Texture *R_D;
extern SDL_Texture *R_D_M;
extern SDL_Texture *R_D_MI;
extern SDL_Texture *R_D_M_MI;
extern SDL_Texture *CORRIDOR;
extern SDL_Texture *CORRIDOR_M;
extern SDL_Texture *CORRIDOR_MI;
extern SDL_Texture *CORRIDOR_M_MI;
extern SDL_Texture *MIMIC_CORRIDOR;
extern SDL_Texture *MIMIC_CORRIDOR_M;
extern SDL_Texture *MIMIC_CORRIDOR_MI;
extern SDL_Texture *MIMIC_CORRIDOR_MI_M;
extern SDL_Texture *FRONT_WALL;
extern SDL_Texture *FRONT_WALL_M;
extern SDL_Texture *FRONT_WALL_MI;
extern SDL_Texture *FRONT_WALL_MI_M;
extern SDL_Texture *HALLWAY;
extern SDL_Texture *HALLWAY_M;
extern SDL_Texture *HALLWAY_MI;
extern SDL_Texture *HALLWAY_MI_M;
extern IMG_Animation *monster_death;
extern IMG_Animation *mimic_death;
extern Mix_Music* sOst; 
extern Mix_Chunk* cameraStatic;
extern Mix_Chunk* cameraSwitch;
extern Mix_Chunk* doorKnocking;
extern Mix_Chunk* monsterSpawn;
extern Mix_Chunk* mimicMove;
extern Mix_Chunk* door_close;
extern Mix_Chunk* light_on;
extern Mix_Chunk* button_on;
extern Mix_Chunk* button_off;
extern Mix_Chunk* sad_mimic;
extern Mix_Chunk* attack;
extern Mix_Chunk *static_sound;
extern Mix_Chunk *song;
/*=======================================================*/
extern SDL_Renderer *renderer;
extern Uint32 lastSound;
extern Uint32 now;
extern case_t *camera;
extern Uint32 currentTime;
extern Uint32 monsterLastMove;
extern float deltaTime;
extern int w;
extern int h;
extern int run;
extern int trans;
extern float progress;
extern GameState state;
extern GameState next;
extern int masterVol;
extern int musicVol;
extern int brightness;
extern int mouseSens;
extern int screenModeIndex;
extern int resIndex;
extern int night;
extern int overBack;
extern Mix_Chunk *sGlitch;
extern SDL_Texture *settingsStaticTex;
extern SDL_Texture *settingsBG;
extern Uint32 saveNotificationTimer;
extern const char *screenModes[];
extern const char *resolutions[];
extern SDL_Texture *bgTexture;
extern SDL_Texture *titleText;
extern SDL_Rect titleRect;
extern MenuButton buttons[5];
extern int assetsLoaded;
extern Uint32 lastTime;
extern int lightCount;
extern int pixel_offset_game;
extern int pixel_offset_cam;
extern float res_percentage;
extern int img_limit_left;
extern float img_stretch_game_percentage;
extern float img_stretch_cam_percentage;
extern int camera_offset_x;
extern int spacing_amount;
extern int is_first_draw;
#endif
