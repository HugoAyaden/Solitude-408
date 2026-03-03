#include <portes.h>

#define PORTE_HAUT 5
#define PORTE_BAS 15

void fermeture_portes(case_t *joueur){ 
    joueur->voisin_haut = NULL;
    joueur->voisin_bas = NULL;
    joueur->acess = FAUX;
    printf("Porte fermée\n"); 

}

void ouverture_portes(carte_t *carte, case_t *joueur){ 
    /* rétablir les voisins du joueur */
    joueur->voisin_haut = &carte->cases[X_JOUEUR-1][Y_JOUEUR];
    joueur->voisin_bas = &carte->cases[X_JOUEUR+1][Y_JOUEUR];
    joueur->acess = VRAI;
    printf("Porte ouverte\n"); }

void attaquer_joueur(carte_t *carte, case_t *monstre, case_t *joueur){
    printf("Le monstre attaque le joueur !\n");
}

void attaquer_joueur_echec(carte_t *carte, case_t *monstre, case_t *joueur){
    placement_monstre(carte, monstre);
}



    /* */
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
    placement_monstre(carte, &monstre);
    //fermeture_portes(joueur);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    while(!fin(carte, &monstre)){
        if(movement_opportunity(carte, &monstre, monstre.num_camera % Y, monstre.num_camera / Y)){
            printf("Le monstre se déplace vers la caméra %d\n", monstre.num_camera);
            sleep(1); // Attendre 5 seconde avant le prochain déplacement
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
    }
    free(carte);
    free(joueur);
    joueur = NULL;
    return 0;
}