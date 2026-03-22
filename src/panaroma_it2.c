#include <panorama_it2.h>
/**
  * \file panorama.c
  * \brief Fournie les fonctions pour le déplacement de camera de jeu
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/



float get_camera_angle(int screen_width) {
    int mouseX;
    SDL_GetMouseState(&mouseX, NULL);

    float center = screen_width / 2.0f;
    float delta = (mouseX - center) / center; // -1 à 1
    float max_angle = 0.35f; // environ 20°

    return delta * max_angle;
}

void render_perspective(SDL_Renderer* r, SDL_Texture* tex,
    int screen_w, int screen_h,
    float angle, SDL_Rect* dst)
{
    int texW, texH;
    SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);

    // Calcul UV selon le scroll horizontal
    float u0 = (float)(-dst->x) / texW;
    float u1 = u0 + (float)screen_w / texW;

    // Sécurité
    if (u0 < 0) u0 = 0;
    if (u1 > 1) u1 = 1;

    float skew = tanf(angle) * (screen_w * 0.35f);

    SDL_Vertex verts[4] = {
        {{0 - skew, 0},            {1,1,1,1}, {u0, 0}},
        {{screen_w - skew, 0},     {1,1,1,1}, {u1, 0}},
        {{screen_w + skew, screen_h}, {1,1,1,1}, {u1, 1}},
        {{0 + skew, screen_h},     {1,1,1,1}, {u0, 1}}
    };

    int indices[6] = { 0,1,2, 2,3,0 };

    SDL_RenderGeometry(r, tex, verts, 4, indices, 6);
}




/**
  * \fn void panoramic_game(int screen_width, int imgW, SDL_Rect* dst)
  * \brief Déplacement gauche-droite de la camera avec la souris, principalement pour la salle principal.
  * \param screen_width Entier, longeur de l'ecran
  * \param imgW Entier, longeur de l'image
  * \param dst SDL_Rect, rectangle de rendu
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/
void panoramic_game(int screen_width, int imgW, SDL_Rect* dst) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    float res_percentage = 0.95; //pourcentage pour determiner zone de deplacement camera

    // Déplacer l'image horizontalement
    if (mouseX >= (int)(screen_width * res_percentage) && dst->x > (-imgW + screen_width)) {

        if ((dst->x - 10) <= (-imgW + screen_width)) {
            dst->x = (-imgW + screen_width);
        }
        else {
            dst->x -= 10;
        }
    }
    else if (mouseX <= (int)(screen_width * (1 - res_percentage)) && dst->x < 0) {
        if ((dst->x + 10) >= 0)
        {
            dst->x = 0;
        }
        else {
            dst->x += 10;
        }
    }
}

/**
  * \fn void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst)
  * \brief Déplacement gauche-droite de la camera automatique, principalement pour les cameras.
  * \param screen_width int, longeur de l'ecran
  * \param imgW int, longeur de l'image
  * \param dst SDL_Rect*, rectangle de rendu
  * \param direction Direction*, direction de deplacement
  * \author Dos Santos Mathis
  * \version 1.0
  * \date 19/03/2026
  *
*/
void panoramic_camera(int screen_width, int imgW, SDL_Rect* dst, direction_t* direction) {

    // Déplacer l'image horizontalement camera automatiquement
    if (*direction == RIGHT)
    {
        if ((dst->x + 3) >= 0)
        {
            dst->x = 0;
            *direction = LEFT;
        }
        else
        {
            dst->x += 3;
        }
    }
    if (*direction == LEFT)
    {
        if ((dst->x - 5) <= (-imgW + screen_width))
        {
            dst->x = (-imgW + screen_width);
            *direction = RIGHT;
        }
        else
        {
            dst->x -= 3;
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
    SDL_Surface* surface = IMG_Load("assets/img/background/4k_test.jpg");
    if (!surface)
    {
        printf("Erreur chargement PNG : %s\n", IMG_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Taille de l'image et position
    int imgW, imgH;
    SDL_QueryTexture(texture, NULL, NULL, &imgW, &imgH);

    SDL_Rect dst = { -imgW / 2, 0, imgW, screen_height }; // position initiale
    int running = 1;
    SDL_Event event;

    // Enum pour la direction camera
    direction_t direction = LEFT;

    while (running)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        panoramic_game(screen_width, imgW, &dst);

        float angle = get_camera_angle(screen_width);

        SDL_RenderClear(renderer);
        render_perspective(renderer, texture, screen_width, screen_height, angle, &dst);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}
