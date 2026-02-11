/**
 * \file carte.h
 * \brief Header pour la structure de la carte de jeu et du type booleen_t
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */

 #include <commun.h>

/* 
 * certaines caméras peuvent être initialisées mais ne pas être accessible
 * le monstre s'y trouve mais il n'est pas possible pour le joueur
 * d'en être certain (peur)
 */

 typedef struct case_s {
    //Y'a t-il un monstre sur la caméra
    booleen_t habite;

    int num_camera;
    //le booleen dit si la caméra est utilisée actuellement ou non (FAUX ou VRAI)
    booleen_t utilise;
    //majoriterement VRAI sauf pour des zones d'histoire (cabine de notre collegue)
    booleen_t acess;

    struct case_s * voisin_haut;
    struct case_s * voisin_droit;
    struct case_s * voisin_gauche;
    struct case_s * voisin_bas;

 }case_t;

 typedef struct carte_s {
   /* first index is row (0..Y-1), second is column (0..X-1) */
   case_t cases[X][Y];
}carte_t;

/* note: first parameter is row (0..Y-1), second is column (0..X-1) */
booleen_t accessible(int y, int x);
void init_carte(carte_t *carte);