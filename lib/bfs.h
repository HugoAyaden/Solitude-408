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

case_t *bfs_next_step(case_t *start, case_t *goal);
void move_monster(carte_t *map, case_t *monster, case_t *joueur);

#endif