/**
 * \file portes.h
 * \brief Header for in game doors
 * \author Ayaden Hugo
 * \version 1.0
 * \date 15/02/2026
 * 
 */

#ifndef PORTES_H
#define PORTES_H

#include "bfs.h"

/**
 * \brief Closes the right door blocking monster access.
 *
 * Plays the door close sound and severs the connection between the
 * room above the player and the player's room.
 *
 * \param joueur Pointer to the player structure.
 * \param map Pointer to the game map.
 */

void fermeture_portes_droite(case_t *joueur, carte_t *map);
/**
 * \brief Closes the left door blocking monster access.
 *
 * Plays the door close sound and severs the connection between the
 * room below the player and the player's room.
 *
 * \param joueur Pointer to the player structure.
 * \param map Pointer to the game map.
 */

void fermeture_portes_gauche(case_t *joueur, carte_t *map);
/**
 * \brief Opens the right door restoring monster access.
 *
 * Reconnects the room above the player to the player's room.
 *
 * \param map Pointer to the game map.
 * \param joueur Pointer to the player structure.
 */

void ouverture_porte_droite(carte_t *map, case_t *joueur);
/**
 * \brief Opens the left door restoring monster access.
 *
 * Reconnects the room below the player to the player's room.
 *
 * \param map Pointer to the game map.
 * \param joueur Pointer to the player structure.
 */

void ouverture_porte_gauche(carte_t *map, case_t *joueur);
void attaquer_joueur(carte_t *map, case_t *monster, case_t *joueur);
/**
 * \brief Handles failed monster attack when door is closed.
 *
 * Plays door knocking sound and respawns the monster at a random spawn point.
 *
 * \param map Pointer to the game map.
 * \param monster Pointer to the monster structure.
 * \param joueur Pointer to the player structure.
 */

void attaquer_joueur_echec(carte_t *map, case_t *monster, case_t *joueur);

#endif

