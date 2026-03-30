/**
 * \file commun.h
 * \brief Header general
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#ifndef COMMUN_H
#define COMMUN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

 /* TAILLE DE LA CARTE */
#define FIN_Y 5
#define FIN_X 3

#define PORTE_HAUT 5
#define PORTE_BAS 15

/* POSITION DU JOUEUR */
#define Y_JOUEUR 4
#define X_JOUEUR 1

typedef enum {FAUX,VRAI} booleen_t;

#endif