#include "game.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init(); IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* win = SDL_CreateWindow("Solitude 408", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *vSmall = TTF_OpenFont("Settings/VCR.ttf", 30), *vLarge = TTF_OpenFont("Settings/VCR.ttf", 90);
    Mix_Chunk* sSound = Mix_LoadWAV("Transition/static.wav");
    SDL_Texture* sTex = CreateStaticTexture(ren);

    // Load saved settings (Volume, Brightness, etc.)
    load_settings(); 

    init_menu(ren, vSmall, vLarge);
    GameState state = STATE_MENU, next = STATE_MENU;
    bool run = true, trans = false;
    float progress = 0.0f;
    SDL_Event e;

    while (run) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) run = false;
            if (e.type == SDL_MOUSEBUTTONDOWN && !trans && state == STATE_MENU) {
                int c = check_menu_click((SDL_Point){e.button.x, e.button.y});
                if (c == 2) { trans = true; progress = 0.0f; next = STATE_SETTINGS; Mix_PlayChannel(-1, sSound, 0); }
                if (c == 3) run = false;
            }
        }

        if (state == STATE_SETTINGS && !trans && render_settings(ren, vSmall) == 1) {
            trans = true; progress = 0.0f; next = STATE_MENU; Mix_PlayChannel(-1, sSound, 0);
        }

        if (trans) {
            progress += 0.015f;
            if (progress >= 0.5f) state = next;
            if (progress >= 1.0f) { trans = false; Mix_HaltChannel(-1); }
        }

        SDL_RenderClear(ren);
        
        // Render current state
        (state == STATE_MENU) ? render_menu(ren) : render_settings(ren, vSmall);
        
        // Render transition
        if (trans) run_transition(ren, sTex, progress);

        // Render Global Brightness Overlay
        int sw, sh;
        SDL_GetRendererOutputSize(ren, &sw, &sh);
        draw_brightness_overlay(ren, sw, sh);

        SDL_RenderPresent(ren);
    }

    cleanup_menu(); cleanup_settings();
    Mix_FreeChunk(sSound); SDL_DestroyTexture(sTex);
    TTF_CloseFont(vSmall); TTF_CloseFont(vLarge);
    SDL_DestroyRenderer(ren); SDL_DestroyWindow(win);
    Mix_CloseAudio(); TTF_Quit(); IMG_Quit(); SDL_Quit();
    return 0;
}