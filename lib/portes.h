/**
 * \file carte.h
 * \brief Header pour le fonctionnement des portes
 * \author Ayaden Hugo
 * \version 1.0
 * \date 15/02/2026
 * 
 */

#include <stdio.h>
#include <ia_monstre_n1.h>

void fermeture_portes(case_t *joueur);
void ouverture_portes(carte_t *carte, case_t *joueur);
void attaquer_joueur(carte_t *carte, case_t *monstre, case_t *joueur);
void attaquer_joueur_echec(carte_t *carte, case_t *monstre, case_t *joueur);

