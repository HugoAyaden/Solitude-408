/**
 * \file ia_monstre_n1.h
 * \brief Header pour les fonctions du monstre la nuit 1
 * \author Ayaden Hugo
 * \version 1.0
 * \date 12/02/2026
 * 
 */


#include <carte.h>



void placement_monstre(carte_t *carte, case_t *monstre);
booleen_t fin(carte_t *carte, case_t *monstre); 


void deplacement(carte_t * carte, case_t * monstre, int direction); 

/* 
 * Le monstre va tirer un chiffre au hasard, voir si il peut y accéder
 * si oui il se déplace sinon il en tire un autre jusqu'à ce qu'il puisse se déplacer
 */
int movement_opportunity(carte_t *carte, case_t *monstre, int y, int x);