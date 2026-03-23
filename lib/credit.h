#ifndef CREDIT_H
#define CREDIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

/**
 * \file credit.h
 * \brief Gestion et affichage des crédits du jeu.
 * \author Bastien LEFEVRE TAUGOURDEAU
 * \version 1.0
 * \date 2026
 *
 * Ce module permet d'afficher les crédits du jeu avec un effet
 * de défilement vertical (style générique de fin).
 */

/**
 * \brief Affiche les crédits du jeu avec un défilement vertical.
 *
 * Cette fonction affiche un écran de crédits avec un effet de
 * défilement du texte du bas vers le haut. Un fond d'écran est
 * affiché et certaines lignes peuvent être mises en valeur avec
 * différentes tailles de police.
 *
 * L'affichage se termine lorsque tous les crédits sont sortis
 * de l'écran ou si l'utilisateur ferme la fenêtre ou appuie sur Échap.
 *
 * \param renderer Le renderer SDL utilisé pour le rendu graphique.
 * \param window La fenêtre SDL utilisée pour récupérer la taille d'affichage.
 */
void afficher_credits(SDL_Renderer *renderer, SDL_Window *window);

#endif // CREDIT_H