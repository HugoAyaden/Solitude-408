/**
 * \file ia_monstre.h
 * \brief Header for the monster's functionement
 * \author Ayaden Hugo
 * \version 1.0
 * \date 12/02/2026
 * 
 */

#ifndef IA_MONSTRE_H
#define IA_MONSTRE_H

#include "map.h"


/* EVERY MONSTER'S START 
 *(The Y always stays the same, opposite of the player)
 */
#define START_MONSTRE_X 3
#define START_MIMIC_X 1

/* MATRICE'S START */
#define DEPART_Y 0
#define DEPART_X 0

/* MATRICE'S END */
#define END_Y 5
#define END_X 3


/**
 * \brief Places the monster at a random spawn point (excluding mimic spawn).
 *
 * Randomly selects spawn position 0 or 2 (skips position 1 reserved for mimic)
 * and plays spawn sound effect.
 *
 * \param map Pointer to the game map structure.
 * \param monster Pointer to the monster's current position (case_t).
 */

void placing_monster(carte_t *map, case_t *monster);
/**
 * \brief Ending condition check for monster attack on player.
 *
 * If the monster's current camera matches the player's camera, the monster has
 * reached the player, and the function returns VRAI. Otherwise, it returns FAUX.
 *
 * \param map Pointer to the game map structure.
 * \param monster Pointer to the monster's current position (case_t).
 * \return VRAI if the monster has reached the player, FAUX otherwise.
 */

booleen_t fin(carte_t *map, case_t *monster); 


void deplacement(carte_t * map, case_t * monster, int direction); 
/**
 * \brief Moves the monster randomly through accessible neighboring directions.
 *
 * Recursively tries random directions (up/right/down/left) until finding an
 * accessible neighbor or failing to move.
 *
 * \param map Pointer to the game map structure.
 * \param monster Pointer to the monster's current position (case_t).
 * \return VRAI if successful movement, FAUX if no valid path found.
 */

int movement_opportunity(carte_t *map, case_t *monster);

/**
 * \brief Handles the mimic's movement logic during gameplay.
 *
 * The mimic randomly moves across the map with a defined chance.
 * If it is adjacent to the player, it attacks. If the player’s light is on, the mimic kills the player;
 * otherwise, the mimic fails and returns to its spawn.
 *
 * \param map Pointer to the game map structure.
 * \param mimic Pointer to the mimic's current position (case_t).
 */

void mouvement_mimic(carte_t *map, case_t *mimic);
/**
 * \brief Executes the mimic’s attack behavior against the player.
 *
 * If the player’s light is on, the mimic kills the player and ends the game.
 * Otherwise, the mimic fails to attack and returns to its spawn.
 *
 * \param map Game map structure (passed by value).
 * \param mimic Pointer to the mimic's current position (case_t).
 * \param joueur Pointer to the player's current position (case_t).
 * \return VRAI if the player is killed by the mimic, FAUX otherwise.
 */

int attaque_mimic(carte_t map, case_t *mimic, case_t *joueur);
/**
 * \brief Mimic's spawnpoint
 * \param map Pointer to the game map structure.
 * \param mimic Pointer to the mimic's current position (case_t).
 *
 */

void placement_mimic(carte_t *map, case_t *mimic);
/**
 * \brief Plays an animated GIF sequence a specified number of times.
 *
 * Converts animation frames to textures, plays associated sound, and renders
 * the animation loop with proper frame timing using SDL delays.
 *
 * \param anim Pointer to the IMG_Animation structure.
 * \param renderer SDL renderer for texture rendering.
 * \param windowW Window width for full-screen rendering.
 * \param windowH Window height for full-screen rendering.
 * \param sound Sound effect to play with animation.
 * \param amount Number of complete animation cycles to play.
 */

void play_gif(IMG_Animation *anim, SDL_Renderer *renderer, int windowW, int windowH, Mix_Chunk *sound, int amount);

/**
 * \brief Returns a random percentage value used to decide movement probability.
 * \return A random integer between 0 and 99.
 */

int chance_deplacement();
void timer_monstre();

#endif
