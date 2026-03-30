/**
 * \file carte.h
 * \brief Header pour la structure de la carte de jeu
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */
#ifndef CARTE_H
#define CARTE_H
#include <commun.h>
#include <constantes.h>

booleen_t accessible(int y, int x);
void init_carte(carte_t *carte);
void init_joueur(case_t *joueur, carte_t *carte);
void init_camera(case_t *camera, carte_t *carte);
void detruire_carte(carte_t *carte);

#endif