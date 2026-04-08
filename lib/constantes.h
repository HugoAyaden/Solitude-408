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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define true 1
#define false 0

typedef struct case_s {
    int num_camera;
    booleen_t lumiere;
    booleen_t acess;
    struct case_s *voisin_haut;
    struct case_s *voisin_droit;
    struct case_s *voisin_gauche;
    struct case_s *voisin_bas;
} case_t;

typedef struct carte_s {
    case_t cases[FIN_X][FIN_Y];
} carte_t;

typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
    const char *label;
} MenuButton;


typedef struct {
    case_t *cell;
    case_t *parent;
} queue_node_t;

typedef enum {WINDOWED,FULLSCREEN,BORDERLESS}screen_t;

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

/**
 * Regroupe tous les états des commandes du joueur (portes, lumières, moniteur).
 * Chaque champ vaut 0 (inactif) ou 1 (actif), sauf lumieres qui est un booleen_t.
 */
typedef struct {
    int porte_gauche;     /* porte gauche verrouillée : bloque le chemin du monstre côté bas  */
    int porte_droite;     /* porte droite verrouillée : bloque le chemin du monstre côté haut */
    int lumiere_gauche;   /* lumière du couloir gauche allumée                                 */
    int lumiere_droite;   /* lumière du couloir droit allumée                                  */
    booleen_t lumieres;   /* extinction générale (= BLACKOUT forcé)                            */
    int moniteur;         /* mode moniteur actif : affiche les caméras au lieu des boutons     */
} PanneauControle;

extern PanneauControle panneau;  /* instance unique, initialisée dans constantes.c             */

/* État d'activation de chacun des 9 boutons de caméra (0 = éteint, 1 = actif).
 * Remplace les 9 variables globales camera1on…camera9on.
 * Indice i correspond au bouton caméra i+1 dans l'interface.               */
extern int cameras_on[9];

/*=============================================*/

extern float battery;
extern int tempsDebut;
extern int tempsFin;
extern int change;
extern float finish;
extern int duree;
extern float BATTERY_DURATION;
extern int cameraMap;
extern int windowW;
extern int windowH;
extern booleen_t boutonLumieres;
extern carte_t *map;
extern case_t *joueur;
extern case_t *monster;
extern case_t *mimic;
extern SDL_Texture *background;
extern SDL_Texture *BLACKOUT;
extern SDL_Texture *DOORS_OFF_L_OFF;
extern SDL_Texture *DOORS_OFF_L_ON;
extern SDL_Texture *DOORS_ON_L_ON;
extern SDL_Texture *L_DOOR_OFF_L_ON;
extern SDL_Texture *L_DOOR_ON_L_OFF;
extern SDL_Texture *L_DOOR_ON_L_ON;
extern SDL_Texture *R_DOOR_OFF_L_ON;
extern SDL_Texture *R_DOOR_ON_L_OFF;
extern SDL_Texture *R_DOOR_ON_L_ON;
extern SDL_Texture *MONITOR_ROOM;
extern SDL_Texture *MONITOR_ROOM_M;
extern SDL_Texture *CORRIDOR;
extern SDL_Texture *CORRIDOR_M;
extern SDL_Texture *COMMAND_ROOM;
extern SDL_Texture *COMMAND_ROOM_M;
extern SDL_Texture *STATIC;
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
extern SDL_Texture *CORRIDOR_M;
extern SDL_Texture *CORRIDOR_MI;
extern SDL_Texture *CORRIDOR_M_MI;
extern Uint32 lastSound;
extern Uint32 now;
extern Mix_Chunk *song;
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
extern Mix_Music* cameraStatic;
extern Mix_Chunk* cameraSwitch;
extern Mix_Chunk* doorKnocking;

extern Mix_Chunk* monsterSpawn;
extern Mix_Chunk* mimicMove;
#endif