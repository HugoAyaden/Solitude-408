/**
 * \file ia_monstre_n2.c
 * \brief Creation and initialisation of the monster's AI for night 2
 * \author Ayaden Hugo
 * \version 1.1
 * \date 16/02/2026
 * 
 */

 #include "bfs.h"

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

int chance_deplacement(){
   int chance = rand() %10;
   return chance;
}

void move_monster(carte_t *map, case_t *monster, case_t *joueur){

    case_t *next = bfs_next_step(monster, joueur);

    if (next != NULL) {
        *monster = *next;

        printf("The monster moves (opti) towards camera %d\n", monster->num_camera);
    } else {
        printf("The moster didn't find a way.\n");
    }
}








/* TEST DU SPAWN L'IA MONSTRE ET DE SON DEPLACEMENT (sans le systeme de portes donc le joueur perd a chaque fois)
int main(){
    carte_t *map = malloc(sizeof(carte_t));
    if (!map) 
        return 0;
    srand(time(NULL));
    init_carte(map);
    case_t monster;
    case_t joueur;
    init_joueur(&joueur, map);
    placement_monstre(map, &monster);
    printf("Le monster est sur la caméra %d\n", monster.num_camera);
    while(!fin(map, &monster)){
        if(chance_deplacement() < 3){ // 30% de chance de se déplacer de facon optimisee (hint)
            move_monster(map, &monster, &joueur);
        }
        else{
            printf("mouvement normal\n");
            movement_opportunity(map, &monster, monster.num_camera % END_Y, monster.num_camera / END_Y);
            printf("Le monster se déplace sur la caméra %d\n", monster.num_camera);
        }
    }
    detruire_carte(map);
}

*/
