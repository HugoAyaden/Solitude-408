#include <stdio.h>
#include <commun.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define N 4
#define M 3
#define X_JOUEUR 3
#define Y_JOUEUR 1


booleen_t carte(case_t * monstre, case_t * joueur ){
     return VRAI;
}



void init_carte(carte_t carte_init){
    int i = 0;
    int j = 0;
    int num = 1;
    for(;i<N; i++){
        for(;j<M;j++){

            //initialise les cases de la carte
            carte_init.cases[i][j].habite = FAUX;
            carte_init.cases[i][j].num_camera = num;
            num++;
            carte_init.cases[i][j].utilise = FAUX;
            
            //vérifie que les cases voisines sont accessibles et pas hors de la carte
            if(accessible(i-1,j))
                carte_init.cases[i][j].voisin_haut = &carte_init.cases[i-1][j];
            if(accessible(i,j-1))
                carte_init.cases[i][j].voisin_gauche = &carte_init.cases[i][j-1];
            if(accessible(i,j+1))
                carte_init.cases[i][j].voisin_droit = &carte_init.cases[i][j+1];
            if(accessible(i+1,j))
                carte_init.cases[i][j].voisin_bas = &carte_init.cases[i+1][j];

            //autorise l'acces a toutes les cases sauf celle du joueur
            if(X_JOUEUR == i && Y_JOUEUR == j)
                carte_init.cases[i][j].acess = FAUX;
            else
                carte_init.cases[i][j].acess = VRAI;
        }
    }
}

booleen_t accessible(int i, int j){
    if(i < 0 || i >= N || j < 0 || j >= M)
        return FAUX;
    return VRAI;
}

booleen_t deplacement(carte_t * carte, case_t * monstre, int x, int y){
    if(carte->cases[x][y].acess == VRAI){
        *monstre = carte->cases[x][y];
        return VRAI;
    }
    return FAUX;
}




int main(){
    carte_t carte;
    init_carte(carte);

}