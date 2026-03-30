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

/* 
 * certaines caméras peuvent être initialisées mais ne pas être accessible
 * le monstre s'y trouve mais il n'est pas possible pour le joueur
 * d'en être certain (peur)
 */

 typedef struct case_s {
    //pour le monstre, temps avant de pouvoir se déplacer à nouveau
    float moove_cooldown;
    //Y'a t-il un monstre sur la caméra
    booleen_t habite;

    int num_camera;
    //le booleen dit si la caméra est utilisée actuellement ou non (FAUX ou VRAI)
    booleen_t utilise;

   /*
    * si la lumière est allumée ou éteinte, cela influence le comportement du mimic, 
    * si la salle du joueur est allumée lors de son attaque il tue le joueur sinon il passe et il retourne a son spawn
    */

    booleen_t lumiere; 
    //majoriterement VRAI sauf pour des zones d'histoire (cabine de notre collegue)
    booleen_t acess;

    struct case_s * voisin_haut;
    struct case_s * voisin_droit;
    struct case_s * voisin_gauche;
    struct case_s * voisin_bas;

 }case_t;

 typedef struct carte_s {

   case_t cases[FIN_X][FIN_Y];
}carte_t;

booleen_t accessible(int y, int x);
void init_carte(carte_t *carte);
void init_joueur(case_t *joueur, carte_t *carte);
void init_camera(case_t *camera, carte_t *carte);
void detruire_carte(carte_t *carte);

#endif