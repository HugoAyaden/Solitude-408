#ifndef GAME_CORE_H
#define GAME_CORE_H
#include <carte.h>

typedef enum {CAMERA_0, CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5, 
              CAMERA_6, CAMERA_7, CAMERA_8, CAMERA_9 ,CAMERA_10, CAMERA_11,
              CAMERA_12, CAMERA_13, CAMERA_14, CAMERA_15
            } num_cameras;

typedef struct {
    booleen_t active;
} camera_t;

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

float BATTERY_DURATION = 420.0f;

int cameraMap = 0;
int windowW = 0;
int windowH = 0;

booleen_t boutonLumieres = FAUX;

carte_t *carte = NULL;
case_t *joueur = NULL;
case_t *monstre = NULL;
case_t *mimic = NULL;

SDL_Texture *background;
SDL_Texture *BLACKOUT = NULL;
SDL_Texture *DOORS_OFF_L_OFF = NULL;
SDL_Texture *DOORS_OFF_L_ON = NULL;
SDL_Texture *DOORS_ON_L_ON = NULL;
SDL_Texture *L_DOOR_OFF_L_ON = NULL;
SDL_Texture *L_DOOR_ON_L_OFF = NULL;
SDL_Texture *L_DOOR_ON_L_ON = NULL;
SDL_Texture *R_DOOR_OFF_L_ON = NULL;
SDL_Texture *R_DOOR_ON_L_OFF = NULL;
SDL_Texture *R_DOOR_ON_L_ON = NULL;
SDL_Texture *MONITOR_ROOM = NULL;
SDL_Texture *MONITOR_ROOM_M = NULL;
SDL_Texture *CORRIDOR = NULL;
SDL_Texture *CORRIDOR_M = NULL;
SDL_Texture *COMMAND_ROOM = NULL;
SDL_Texture *COMMAND_ROOM_M = NULL;
SDL_Texture *STATIC = NULL;
SDL_Texture *MONSTER_L_DOOR_C = NULL;
SDL_Texture *MONSTER_L_DOOR_O_A = NULL;
SDL_Texture *MONSTER_L_DOOR_O = NULL;
SDL_Texture *MONSTER_R_DOOR_C = NULL;
SDL_Texture *MONSTER_R_DOOR_O_A = NULL;
SDL_Texture *MONSTER_R_DOOR_O = NULL;
Uint32 lastSound = 0; 
Uint32 now = 0; 

Mix_Chunk* song = NULL;



case_t * camera = NULL;

Uint32 currentTime = 0;
Uint32 monsterLastMove = 0;
float deltaTime = 0;


void change_camera(case_t * camera, case_t * monstre);
int buttons_getDoorCount();
int buttons_getLightCount();
void game_handleEvent(SDL_Event *event, SDL_Window *window);
void battery_init();
void game_initialise();
void battery_update(float deltaTime, int doorCount, int lightCount);
void game_update(float deltaTime);
void difficulte(int night);
void update();
void game_init(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* fontBattery, TTF_Font* fontButtons);
void game_final_cleanup();

#endif