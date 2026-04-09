/**
 * \file main.c
 * \brief FIle for the game to decite game state.
 * \author Amara Louay
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#include "MainMenu.h"
#include "transition.h" 

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

    // --- 1. Initialization ---
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 1;
    if (TTF_Init() == -1) return 1;
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    FILE *f = fopen("config/save.cfg", "r");
    if(!f) save_settings(); else load_settings();

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
    if (icon) { SDL_SetWindowIcon(win, icon); SDL_FreeSurface(icon); }

    TTF_Font *vSmall = TTF_OpenFont("assets/font/VCR.ttf", 30);
    TTF_Font *vLarge = TTF_OpenFont("assets/font/VCR.ttf", 80);
    
    Mix_Chunk* sTran = Mix_LoadWAV("assets/audio/sound/static.wav"); 
    if(sTran) Mix_VolumeChunk(sTran, 10);
    
    Mix_Music* sOst = Mix_LoadMUS("assets/audio/sound/ost.wav"); 
    if(sOst) Mix_VolumeMusic(30);

    SDL_Texture* sTex = CreateStaticTexture(ren);

    // --- Music Timer Variables ---
    Uint32 musicStartTime = SDL_GetTicks() + 1500; 
    int musicStarted = false;

    // Initialize Menu Module
    init_menu(ren, vSmall, vLarge);

    // =========================================
    // --- PRELOAD ASSETS (The Loading Screen) ---
    // Draw a black screen so the boot-up feels clean
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    
    // Optional Pro-Move: If you want to render "LOADING..." text here, you can!
    
    SDL_RenderPresent(ren);

    // Now freeze the CPU for a second to load everything into RAM
    preload_assets(ren); 
    // =========================================

    GameState state = STATE_MENU, next = STATE_MENU;
    SDL_Event e;

    while (run) {
        Uint32 now = SDL_GetTicks();

        // --- 4. Music Logic (Wait & Resume) ---
        if (!musicStarted && sOst && now >= musicStartTime) {
            Mix_PlayMusic(sOst, -1);
            musicStarted = true;
        }

        // --- 5. Event Handling ---
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) run = false;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                if (state == STATE_MENU) {
                    run = false;
                } else if (!trans) {
                    next = STATE_MENU; trans = true; progress = 0.0f;
                    if(sTran) Mix_PlayChannel(-1, sTran, 0);
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && !trans && state == STATE_MENU) {
                int c = check_menu_click((SDL_Point){e.button.x, e.button.y});
                // NO FADEOUT HERE ANYMORE! Let the music play!
                if (c == NEW_GAME) { trans = true; progress = 0.0f; next = STATE_NEW_GAME; if(sTran) Mix_PlayChannel(-1, sTran, 0); }
                if (c == LOAD_GAME) { trans = true; progress = 0.0f; next = STATE_CONTINUE; if(sTran) Mix_PlayChannel(-1, sTran, 0); }
                if (c == SETTINGS) { trans = true; progress = 0.0f; next = STATE_SETTINGS; if(sTran) Mix_PlayChannel(-1, sTran, 0); }
                if (c == CREDITS) { trans = true; progress = 0.0f; next = STATE_CREDITS; if(sTran) Mix_PlayChannel(-1, sTran, 0); }
                if (c == EXIT_GAME) run = false; 
            }
        }

        // --- 6. Transitions ---
        // Transition -> New Game & Continue
        if (trans && (next == STATE_NEW_GAME || next == STATE_CONTINUE)) {
            
            if (progress < 0.5f) {
                progress += 0.005f; // 1. Static builds up
            } else {
                // 2. Max static reached! Draw PURE BLACK SCREEN.
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                SDL_RenderClear(ren);
                SDL_RenderPresent(ren);

                // 3. Launch game! (Music is STILL PLAYING seamlessly during the heavy loading)
                if (next == STATE_NEW_GAME) save_night(0);
                game_init(ren, win, vSmall, vSmall); 
                
                // 4. BACK FROM GAME
                state = STATE_MENU; 
                next = STATE_MENU; 
                trans = false;
                progress = 0.0f;
                musicStarted = false; 
                musicStartTime = SDL_GetTicks() + 3000; 
                Mix_HaltChannel(-1);
            }
        }

        // Other Transitions
        if (next == STATE_SETTINGS && trans) {
            progress += 0.005f;
            if (progress >= 0.5f && state != next) { state = next; next = STATE_MENU; trans = false; }
        }
        if (next == STATE_CREDITS && trans) {
            progress += 0.005f;
            if (progress >= 0.5f && state != next) { state = next; next = STATE_MENU; trans = false; }
        }
        if (next == STATE_MENU && trans) {
            progress += 0.005f;
            if (progress >= 0.5f && state != next) { state = next; trans = false; }
        }

        // --- 8. Rendering ---
        SDL_RenderClear(ren);

        if (state == STATE_MENU) {
            render_menu(ren);
        } else if (state == STATE_SETTINGS) {
            int r = render_settings(ren, vSmall);
            if (r == 1 && !trans) {
                next = STATE_MENU; trans = true; progress = 0.0f;
                if(sTran) Mix_PlayChannel(-1, sTran, 0);
            }
        } else if (state == STATE_CREDITS && !trans) {
            render_credits(ren, win);
            SDL_Event trash; while(SDL_PollEvent(&trash));
            next = STATE_MENU; trans = true; progress = 0.0f;
            if(sTran) Mix_PlayChannel(-1, sTran, 0);
        }
    
        if (trans) run_transition(ren, sTex, progress);

        int sw, sh;
        SDL_GetRendererOutputSize(ren, &sw, &sh);
        draw_brightness_overlay(ren, sw, sh);

        SDL_RenderPresent(ren);
    }

    // --- 9. Cleanup ---
    cleanup_menu(); cleanup_settings(); game_final_cleanup();
    if(sOst) Mix_FreeMusic(sOst);
    if(sTran) Mix_FreeChunk(sTran); 
    if(sTex) SDL_DestroyTexture(sTex);  
    TTF_CloseFont(vSmall); TTF_CloseFont(vLarge);
    SDL_DestroyRenderer(ren); SDL_DestroyWindow(win);
    Mix_CloseAudio(); TTF_Quit(); IMG_Quit(); SDL_Quit();
    return 0;
}