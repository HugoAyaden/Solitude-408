/**
 * \file map.h
 * \brief Header for the map structure
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */
#ifndef CARTE_H
#define CARTE_H
#include "commun.h"
#include "constantes.h"

/**
 * \brief Checks if a position on the map is accessible.
 *
 * Verifies that the coordinates (x, y) are within the valid map boundaries.
 *
 * \param x X-coordinate to check.
 * \param y Y-coordinate to check.
 * \return VRAI if accessible, FAUX otherwise.
 */

booleen_t accessible(int y, int x);
/**
 * \brief Initializes the complete game map.
 *
 * Creates a 5x3 grid of interconnected camera rooms with specific walls
 * blocking certain movements according to the predefined map layout.
 * Numbers cameras sequentially from 1 to 15, sets all accessible by default.
 *
 * \param carte_init Pointer to the carte_t structure to initialize.
 */

void init_carte(carte_t *map);
/**
 * \brief Initializes the player entity.
 *
 * Sets the player position to the predefined spawn point (X_JOUEUR, Y_JOUEUR),
 * enables the light by default, and connects neighbors (except left/right walls).
 *
 * \param joueur Pointer to the player structure.
 * \param map Pointer to the initialized map.
 */

void init_joueur(case_t *joueur, carte_t *map);
/**
 * \brief Initializes the camera entity.
 *
 * Sets camera to position 10 with default properties and no neighbors.
 *
 * \param camera Pointer to the camera structure.
 * \param map Pointer to the initialized map.
 */

void init_camera(case_t *camera, carte_t *map);
/**
 * \brief Frees the map structure.
 *
 * \param map Pointer to the carte_t structure to destroy.
 */

void detruire_carte(carte_t *map);

#endif
