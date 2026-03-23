#include <panorama.h>


/**
  * \file panorama.c
  * \brief Fournie les fonctions pour le déplacement de camera de jeu
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/

/**
  * \fn void panoramic_game(int screen_width, int imgW, SDL_Rect* dst)
  * \brief Déplacement gauche-droite de la camera avec la souris, principalement pour la salle principal.
  * \param screen_width Entier, longeur de l'ecran
  * \param imgW Entier, longeur de l'image
  * \param imgRect SDL_Rect, rectangle de rendu
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/
void panoramic_game(int screen_width, int imgW, SDL_Rect* imgRect) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    float res_percentage = 0.95;                                    //pourcentage pour determiner zone de deplacement camera
    int pixel_offset = 10;                                          //decalage pixel deplacement
    int move_zone_left = (int)screen_width * res_percentage;        //position par rapport a l'ecran ou la camera commence à bouger - gauche
    int move_zone_right = (int)screen_width * (1 - res_percentage); //position par rapport a l'ecran ou la camera commence à bouger - droit
    int img_limit_right = -imgW + screen_width;                     //limite de position de l'image a droite
    int img_limit_left = 0;                                         //limite de position de l'image a gauche

    // Déplacer l'image horizontalement
    if (mouseX >= move_zone_left && imgRect->x > img_limit_right) {

        if ((imgRect->x - pixel_offset) <= img_limit_right) {
            imgRect->x = img_limit_right;
        }
        else {
            imgRect->x -= pixel_offset;
        }
    }
    else if (mouseX <= move_zone_right && imgRect->x < img_limit_left) {
        if ((imgRect->x + pixel_offset) >= img_limit_left)
        {
            imgRect->x = img_limit_left;
        }
        else {
            imgRect->x += pixel_offset;
        }
    }
}

/**
  * \fn void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst)
  * \brief Déplacement gauche-droite de la camera automatique, principalement pour les cameras.
  * \param screen_width int, longeur de l'ecran
  * \param imgW int, longeur de l'image
  * \param imgRect SDL_Rect*, rectangle de rendu
  * \param direction Direction*, direction de deplacement
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/
void panoramic_camera(int screen_width, int imgW, SDL_Rect* imgRect, direction_t* direction) {
    int pixel_offset = 1;                                           //decalage pixel deplacement
    int img_limit_right = -imgW + screen_width;                     //limite de position de l'image a droite
    int img_limit_left = 0;                                         //limite de position de l'image a gauche

    // Déplacer l'image horizontalement camera automatiquement
    if (*direction == GAUCHE)
    {
        if ((imgRect->x + pixel_offset) >= img_limit_left)
        {
            imgRect->x = img_limit_left;
            *direction = DROITE;
        }
        else
        {
            imgRect->x += pixel_offset;
        }
    }
    if (*direction == DROITE)
    {
        if ((imgRect->x - pixel_offset) <= img_limit_right)
        {
            imgRect->x = img_limit_right;
            *direction = GAUCHE;
        }
        else
        {
            imgRect->x -= pixel_offset;
        }
    }
}

/**
  * \fn void panoramic_init()
  * \brief Initialisation du panorama
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/


void panorama_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur SDL : %s\n", SDL_GetError());
    }

    IMG_Init(IMG_INIT_PNG);

    /*
    Recupere la resolution de l'ecran
    */
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int screen_width = DM.w;
    int screen_height = DM.h;

    printf("Résolution actuelle : %dx%d\n", screen_width, screen_height);

    /*
    Fenetre de jeu
    */
    SDL_Window* window = SDL_CreateWindow(
        "Panorama UI",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screen_width, screen_height,
        SDL_WINDOW_FULLSCREEN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Charger l'image
    SDL_Surface* surface = IMG_Load("assets/img/background/MONITOR ROOM.png");
    if (!surface)
    {
        printf("Erreur chargement PNG : %s\n", IMG_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Taille de l'image et position
    int imgW, imgH;
    SDL_QueryTexture(texture, NULL, NULL, &imgW, &imgH);

    float img_stretch_percentage = 1.4; //pourcentage d'etendue de l'image
    int img_stretched_res = (int)(screen_width * img_stretch_percentage); //nouvelle resolution de l'image
    int imgCenterRes =(-img_stretched_res+screen_width)/2; //milieu de l'image pour position

    SDL_Rect imgRect = { imgCenterRes, 0, img_stretched_res, screen_height }; // position initiale
    int running = 1;
    SDL_Event event;

    // Enum pour la direction camera
    direction_t direction = GAUCHE;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        //call fonction panoramic main room
        //panoramic_game(screen_width, img_stretched_res, &imgRect);
        //call fonction panoramic main room
        panoramic_camera(screen_width, img_stretched_res, &imgRect, &direction);

        // Rendu
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &imgRect);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // -60 FPS
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}
