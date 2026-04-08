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

 typedef enum {HAUT, DROITE, BAS, GAUCHE} direction_t;

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


void placing_monster(carte_t *map, case_t *monster);
booleen_t fin(carte_t *map, case_t *monster); 


void deplacement(carte_t * map, case_t * monster, int direction); 
int movement_opportunity(carte_t *map, case_t *monster);

void mouvement_mimic(carte_t *map, case_t *mimic);
int attaque_mimic(carte_t map, case_t *mimic, case_t *joueur);
void placement_mimic(carte_t *map, case_t *mimic);

int chance_deplacement();
void timer_monstre();

#endif