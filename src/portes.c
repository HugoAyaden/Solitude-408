/**
 * \file portes.c
 * \brief Fonctions des portes du jeu.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 11/02/2026
 * 
 */

#include <portes.h>



void fermeture_portes_droite(case_t *joueur, carte_t *carte){ 
    carte->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = NULL;

}

void fermeture_portes_gauche(case_t *joueur, carte_t *carte){ 
    carte->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = NULL;

}

void ouverture_porte_droite(carte_t *carte, case_t *joueur){ 
    /* rétablir les voisins du joueur */
    carte->cases[X_JOUEUR-1][Y_JOUEUR].voisin_bas = joueur;

}

void ouverture_porte_gauche(carte_t *carte, case_t *joueur){ 
    /* rétablir les voisins du joueur */
    carte->cases[X_JOUEUR+1][Y_JOUEUR].voisin_haut = joueur;
}

void attaquer_joueur(carte_t *carte, case_t *monstre, case_t *joueur){
    printf("Le monstre attaque le joueur !\n");
}

void attaquer_joueur_echec(carte_t *carte, case_t *monstre, case_t *joueur){
    placement_monstre(carte, monstre);
}





    /*
int main(){

    carte_t *carte = malloc(sizeof(carte_t));
    case_t *joueur = malloc(sizeof(case_t));
    if (!carte || !joueur) {
        free(carte);
        free(joueur);
        return 0;
    }
    init_carte(carte);
    init_joueur(joueur, carte);
    carte->cases[X_JOUEUR][Y_JOUEUR] = *joueur;
    case_t monstre;
    case_t mimic;
    placement_mimic(carte, &mimic);
    placement_monstre(carte, &monstre);
    fermeture_portes(joueur);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    while(!fin(carte, &monstre) && !attaque_mimic(*carte, &mimic, joueur)){
        if(chance_deplacement() < 5 )
            move_monster(carte, &monstre, joueur);
        else{
            movement_opportunity(carte, &monstre, monstre.num_camera % FIN_Y, monstre.num_camera / FIN_Y);
            printf("Le monstre se déplace vers la caméra %d\n", monstre.num_camera);
        }
        sleep(1); // Attendre 1 seconde avant le prochain déplacement
        if(monstre.num_camera == PORTE_HAUT || monstre.num_camera == PORTE_BAS){
            if(joueur->acess == FAUX){
                printf("Le monstre attaque le joueur à la porte mais échoue !\n");
                attaquer_joueur_echec(carte, &monstre, joueur);
            }
            else{
                if(joueur->acess == VRAI){
                    attaquer_joueur(carte, &monstre, joueur);
                    fin(carte, &monstre);
                }
            }
        }
    }
    free(carte);
    free(joueur);
    joueur = NULL;
    return 0;
}
    */
