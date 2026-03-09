/**
 * \file ia_monstre_n1.c
 * \brief Création et initialisation de l'IA du monstre
 * \author Ayaden Hugo
 * \version 1.1
 * \date 16/02/2026
 * 
 */

#include <bfs.h>

/********** DEPLACEMENT DU MONSTRE OPTIMISE AU LONG DE LA PARTIE **********/

case_t *bfs_next_step(case_t *start, case_t *goal){

    queue_node_t queue[256];
    int front = 0, back = 0;

    booleen_t visited[256] = { FAUX };

    // Initialiser la queue avec le point de départ
    queue[back].cell = start;
    queue[back].parent = NULL;
    back++;
    visited[start->num_camera] = VRAI;

    // BFS
    while (front < back) {

        case_t *current = queue[front].cell;
        case_t *current_parent = queue[front].parent;
        front++;

        // Vérifier si on a atteint le goal en comparant les numéros de caméra
        if (current->num_camera == goal->num_camera) {
            // On a trouvé le goal
            // Remonter le chemin pour trouver le voisin direct du start
            case_t *trace = current;
            case_t *trace_parent = current_parent;
            
            while (trace_parent != NULL && trace_parent->num_camera != start->num_camera) {
                for (int i = 0; i < back; i++) {
                    if (queue[i].cell->num_camera == trace_parent->num_camera) {
                        trace = trace_parent;
                        trace_parent = queue[i].parent;
                        break;
                    }
                }
                if (trace_parent == NULL) break;
            }
            return trace;
        }

        // Ajouter tous les voisins non visités
        case_t *voisins[4] = {
            current->voisin_haut,
            current->voisin_droit,
            current->voisin_bas,
            current->voisin_gauche
        };

        for (int i = 0; i < 4; i++) {
            case_t *v = voisins[i];

            if (v != NULL &&
                v->acess == VRAI &&
                !visited[v->num_camera]) {

                visited[v->num_camera] = VRAI;

                queue[back].cell = v;
                queue[back].parent = current;
                back++;
            }
        }
    }

    return NULL;
}



void move_monster(carte_t *carte, case_t *monstre, case_t *joueur){

    case_t *next = bfs_next_step(monstre, joueur);

    if (next != NULL) {
        monstre->habite = FAUX;
        *monstre = *next;
        monstre->habite = VRAI;

        printf("Le monstre avance (opti) vers la caméra %d\n", monstre->num_camera);
    } else {
        printf("Le monstre ne trouve aucun chemin.\n");
    }
}








/* TEST DU SPAWN L'IA MONSTRE ET DE SON DEPLACEMENT (sans le systeme de portes donc le joueur perd a chaque fois) */
int main(){
    carte_t *carte = malloc(sizeof(carte_t));
    if (!carte) 
        return 0;
    srand(time(NULL));
    init_carte(carte);
    case_t monstre;
    case_t joueur;
    init_joueur(&joueur, carte);
    placement_monstre(carte, &monstre);
    printf("Le monstre est sur la caméra %d\n", monstre.num_camera);
    while(!fin(carte, &monstre)){
        if(rand() %10 < 3){ // 30% de chance de se déplacer de facon optimisee (hint)
            move_monster(carte, &monstre, &joueur);
        }
        else{
            printf("mouvement normal\n");
            movement_opportunity(carte, &monstre, monstre.num_camera % FIN_Y, monstre.num_camera / FIN_Y);
            printf("Le monstre se déplace sur la caméra %d\n", monstre.num_camera);
        }
    }
    detruire_carte(carte);
}