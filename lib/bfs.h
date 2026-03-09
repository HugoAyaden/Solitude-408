/**
 * \file bfs.h
 * \brief Header pour la recherche optimisée du chemin du monstre vers le joueur
 * \author Ayaden Hugo
 * \version 1.0
 * \date 09/03/2026
 * 
 */

#include <ia_monstre.h>

typedef struct {
    case_t *cell;
    case_t *parent;
} queue_node_t;

case_t *bfs_next_step(case_t *start, case_t *goal);
void move_monster(carte_t *carte, case_t *monstre, case_t *joueur);