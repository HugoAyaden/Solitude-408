/**
 * \file portes.h
 * \brief Header pour le fonctionnement des portes
 * \author Ayaden Hugo
 * \version 1.0
 * \date 15/02/2026
 * 
 */

#ifndef PORTES_H
#define PORTES_H

#include <bfs.h>

void fermeture_portes_droite(case_t *joueur, carte_t *carte);
void fermeture_portes_gauche(case_t *joueur, carte_t *carte);
void ouverture_porte_droite(carte_t *carte, case_t *joueur);
void ouverture_porte_gauche(carte_t *carte, case_t *joueur);
void attaquer_joueur(carte_t *carte, case_t *monstre, case_t *joueur);
void attaquer_joueur_echec(carte_t *carte, case_t *monstre, case_t *joueur);

#endif

