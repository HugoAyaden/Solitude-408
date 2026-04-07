/**
 * \file ia_monstre.h
 * \brief Header pour les fonctions du monstre
 * \author Ayaden Hugo
 * \version 1.0
 * \date 12/02/2026
 * 
 */

#ifndef IA_MONSTRE_H
#define IA_MONSTRE_H

#include <carte.h>

/* DEPART DE CHACUN DES MONSTRES 
 *(le Y reste toujours le meme, l'autre coté du vaisseau par rapport au joueur)
 */
#define START_MONSTRE_X 3
#define START_MIMIC_X 1

/* DEPART DE LA MATRICE */
#define DEPART_Y 0
#define DEPART_X 0

#define FIN_Y 5
#define FIN_X 3


void placement_monstre(carte_t *carte, case_t *monstre);
booleen_t fin(carte_t *carte, case_t *monstre); 


void deplacement(carte_t * carte, case_t * monstre, int direction); 

/* 
 * Le monstre va tirer un chiffre au hasard, voir si il peut y accéder
 * si oui il se déplace sinon il en tire un autre jusqu'à ce qu'il puisse se déplacer
 */
int movement_opportunity(carte_t *carte, case_t *monstre, int y, int x);

void mouvement_mimic(carte_t *carte, case_t *mimic);
int attaque_mimic(carte_t carte, case_t *mimic, case_t *joueur);
void placement_mimic(carte_t *carte, case_t *mimic);

int chance_deplacement();
void timer_monstre();

#endif