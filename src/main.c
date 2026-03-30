#include <MainMenu.h>


void transition() {
    if (trans) {
        progress += 0.005f;
        if (progress >= 0.5f && state != next) {
            state = next;
            trans  = false;
            progress = 0.0f;
        }
    }
}

int main(int argc, char* argv[]) {
    (void)argc; (void)argv; 

    // --- 1. Subsystems Initialization ---
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 1;
    if (TTF_Init() == -1) return 1;
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    FILE *f = fopen("config/save.cfg", "r");
    //Si le fichier des paramètres n'existe pas
    if(!f){
        //on le crée et on écrit les paramètres par défaut

        save_settings();
    } else {
        //Sinon on y touche pas
        load_settings();
    }

    // --- 2. Window & Resolution Setup ---
    if (resIndex == 0)      { w = 3840; h = 2160; }
    else if (resIndex == 1) { w = 2560; h = 1440; }
    else if (resIndex == 3) { w = 1440; h = 900; }

    Uint32 flags = SDL_WINDOW_SHOWN;
    if (screenModeIndex == 1)      flags |= SDL_WINDOW_FULLSCREEN;
    else if (screenModeIndex == 2) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    SDL_Window* win = SDL_CreateWindow("Solitude 408", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // --- 3. Asset Loading ---
    SDL_Surface* icon = IMG_Load("assets/img/icon/icon.png"); 
    if (icon) {
        SDL_SetWindowIcon(win, icon);        
        SDL_FreeSurface(icon); 
    }

    TTF_Font *vSmall = TTF_OpenFont("assets/font/VCR.ttf", 30);
    TTF_Font *vLarge = TTF_OpenFont("assets/font/VCR.ttf", 80);
    Mix_Chunk* sSound = Mix_LoadWAV("assets/audio/sound/static.wav");
    SDL_Texture* sTex = CreateStaticTexture(ren);

    // Initialize Menu Module
    init_menu(ren, vSmall, vLarge);

    // --- 4. Main Game Loop Variables ---
    GameState state = STATE_MENU, next = STATE_MENU;
    SDL_Event e;

    while (run) {
        // --- 5. Event Handling ---
        while (SDL_PollEvent(&e)) {
            // Global Exit
            if (e.type == SDL_QUIT) run = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) run = false;

            // Menu Events
            if (e.type == SDL_MOUSEBUTTONDOWN && !trans && state == STATE_MENU) {
                int c = check_menu_click((SDL_Point){e.button.x, e.button.y});

                // NEW GAME
                if (c == NEW_GAME) {
                    trans = true; 
                    progress = 0.0f; 
                    next = STATE_NEW_GAME; 
                    if(sSound) Mix_PlayChannel(-1, sSound, 0); 
                }
                // CONTINUE
                 if (c == LOAD_GAME) {
                    trans = true; 
                    progress = 0.0f; 
                    next = STATE_CONTINUE; 
                    if(sSound) Mix_PlayChannel(-1, sSound, 0); 
                }
                // SETTINGS
                if (c == SETTINGS) { 
                    trans = true; 
                    progress = 0.0f; 
                    next = STATE_SETTINGS; 
                    if(sSound) Mix_PlayChannel(-1, sSound, 0); 
                }
                // EXIT
                if (c == EXIT_GAME) run = false; 
            }

        }

        // Transition -> New Game
        if (trans && next == STATE_NEW_GAME) {
            progress += 0.005f;
        if (progress >= 0.5f && state != next) { 
                save_night(0);
                game_init(ren, win, vSmall, vSmall); 
                state = STATE_MENU;
                next = STATE_MENU;
                trans = false; 
                Mix_HaltChannel(-1);
        }
        }
         // Transition -> Continue
        if (trans && next == STATE_CONTINUE) {
            progress += 0.005f;
            if (progress >= 0.5f && state != next) { 
                game_init(ren, win, vSmall, vSmall); 
                state = STATE_MENU;
                next = STATE_MENU;
                trans = false; 
                Mix_HaltChannel(-1);
            }
        }

        // Transition -> Settings
        if (next == STATE_SETTINGS && trans) {
            progress += 0.005f;
            if (progress >= 0.5f && state != next) { 
                state = next;
                next = STATE_MENU;
                trans = false; 
            }
        }

        if (next == STATE_MENU && trans) {
            progress += 0.005f;
            if (progress >= 0.5f && state != next) { 
                state = next;
                next = STATE_MENU;
                trans = false; 
            }
        }


        // --- 8. Rendering ---
        SDL_RenderClear(ren);

        if (state == STATE_MENU) {
            render_menu(ren);
        } 
        else if (state == STATE_SETTINGS) {
        int r = render_settings(ren, vSmall);
            if (r == 1 && !trans) {
                next = STATE_MENU;
                trans = true;
                progress = 0.0f;
            }
        }


        // Overlay static effect during transition
        if (trans) run_transition(ren, sTex, progress);

        // Global Overlays (Brightness)
        int sw, sh;
        SDL_GetRendererOutputSize(ren, &sw, &sh);
        draw_brightness_overlay(ren, sw, sh);

        SDL_RenderPresent(ren);
    }

    // --- 9. Cleanup & Shutdown ---
    cleanup_menu(); 
    cleanup_settings();
    game_final_cleanup();

    if(sSound) Mix_FreeChunk(sSound); 
    if(sTex) SDL_DestroyTexture(sTex);
    TTF_CloseFont(vSmall); TTF_CloseFont(vLarge);
    SDL_DestroyRenderer(ren); SDL_DestroyWindow(win);
    Mix_CloseAudio(); TTF_Quit(); IMG_Quit(); SDL_Quit();
    
    return 0;
}