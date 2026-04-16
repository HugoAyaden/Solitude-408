/**
 * \file bfs.h
 * \brief Header for the optimised research of the player by the monster
 * \author Ayaden Hugo
 * \version 1.0
 * \date 09/03/2026
 * 
 */
#ifndef BFS_H
#define BFS_H

#include "constantes.h"
#include "ia_monstre.h"

/**
 * \brief Finds the next step for the monster using BFS.
 * \param start Pointer to the starting cell.
 * \param goal Pointer to the target cell.
 * \return Pointer to the next cell to move to, or NULL if no path is found.
 */

case_t *bfs_next_step(case_t *start, case_t *goal);
/**
 * \brief Moves the monster one step toward the player using BFS.
 * \param map Pointer to the game map structure.
 * \param monster Pointer to the monster's current position.
 * \param joueur Pointer to the player's current position.
 */

void move_monster(carte_t *map, case_t *monster, case_t *joueur);

#endif
