#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <commun.h>


typedef struct { SDL_Rect rect; SDL_Texture* texture; const char* label; } MenuButton;
typedef enum { STATE_MENU, STATE_SETTINGS, STATE_NEW_GAME, STATE_CONTINUE} GameState;

typedef enum {CAMERA_0, CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5, 
              CAMERA_6, CAMERA_7, CAMERA_8, CAMERA_9 ,CAMERA_10, CAMERA_11,
              CAMERA_12, CAMERA_13, CAMERA_14, CAMERA_15
            } num_cameras;

//BFS.H
typedef struct {
    booleen_t active;
} camera_t;

typedef struct {
    case_t *cell;
    case_t *parent;
} queue_node_t;

//CARTE.H
/* 
 * certaines caméras peuvent être initialisées mais ne pas être accessible
 * le monstre s'y trouve mais il n'est pas possible pour le joueur
 * d'en être certain (peur)
 */

 typedef struct case_s {
    //pour le monstre, temps avant de pouvoir se déplacer à nouveau
    float moove_cooldown;
    //Y'a t-il un monstre sur la caméra
    booleen_t habite;

    int num_camera;
    //le booleen dit si la caméra est utilisée actuellement ou non (FAUX ou VRAI)
    booleen_t utilise;

   /*
    * si la lumière est allumée ou éteinte, cela influence le comportement du mimic, 
    * si la salle du joueur est allumée lors de son attaque il tue le joueur sinon il passe et il retourne a son spawn
    */

    booleen_t lumiere; 
    //majoriterement VRAI sauf pour des zones d'histoire (cabine de notre collegue)
    booleen_t acess;

    struct case_s * voisin_haut;
    struct case_s * voisin_droit;
    struct case_s * voisin_gauche;
    struct case_s * voisin_bas;

 }case_t;

 typedef struct carte_s {

   case_t cases[FIN_X][FIN_Y];
}carte_t;


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


#endif