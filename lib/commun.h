
typedef enum {FAUX,VRAI} booleen_t;


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
    case_t cases[4][3];
}carte_t;