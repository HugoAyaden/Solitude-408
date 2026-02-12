#include <game.h>
#include <stdio.h>
#include <stdlib.h>

// Global Settings Variables
int masterVol = 80, musicVol = 60, brightness = 50, mouseSens = 40;
int screenModeIndex = 1; 
int resIndex = 2; 

// Background Textures
static SDL_Texture* settingsStaticTex = NULL;
static SDL_Texture* settingsBG = NULL; 
static Uint32 saveNotificationTimer = 0; 

// Interface Options
const char* screenModes[] = {"WINDOWED", "FULLSCREEN", "BORDERLESS"};
const char* resolutions[] = {"3840x2160", "2560x1440", "1920x1080", "1440x900"};

// --- Save/Load Logic ---

void save_settings() {
    FILE* f = fopen("assets/save.cfg", "w");
    if (f) {
        fprintf(f, "%d %d %d %d %d %d", masterVol, musicVol, brightness, mouseSens, screenModeIndex, resIndex);
        fclose(f);
    }
    saveNotificationTimer = SDL_GetTicks() + 2000; 
}

void load_settings() {
    FILE* f = fopen("assets/save.cfg", "r");
    if (f) {
        if (fscanf(f, "%d %d %d %d %d %d", &masterVol, &musicVol, &brightness, &mouseSens, &screenModeIndex, &resIndex) == 6) {
            Mix_Volume(-1, (masterVol * MIX_MAX_VOLUME) / 100);
            Mix_VolumeMusic((musicVol * MIX_MAX_VOLUME) / 100);
        }
        fclose(f);
    }
}

// --- Brightness Overlay ---

void draw_brightness_overlay(SDL_Renderer* ren, int sw, int sh) {
    int alpha = (int)((1.0f - (brightness / 100.0f)) * 150); 
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, alpha);
    SDL_Rect full = {0, 0, sw, sh};
    SDL_RenderFillRect(ren, &full);
}

// --- VHS Style Notification Helper ---

void draw_vhs_save_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int sw, int sh) {
    if (!font) return;
    SDL_Color vhsGreen = {50, 255, 50, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, vhsGreen);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    
    SDL_Rect dst = { (sw / 6), sh - 185, surf->w, surf->h };
    
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

// --- Standard UI Helpers ---

void draw_centered_text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Rect btnRect) {
    if (!font) return;
    SDL_Color purple = {191, 0, 255, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, purple);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect textRect = { btnRect.x + (btnRect.w - surf->w) / 2, btnRect.y + (btnRect.h - surf->h) / 2, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &textRect);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_settings_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y) {
    if (!font) return;
    SDL_Color purple = {191, 0, 255, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, purple);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_white_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y) {
    if (!font) return;
    SDL_Color white = {255, 255, 255, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, white);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_red_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y) {
    if (!font) return;
    SDL_Color red = {255, 0, 0, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, red);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_small_hud_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y, SDL_Color col) {
    if (!font) return;
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, col);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, (int)(surf->w * 0.7), (int)(surf->h * 0.7) }; 
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_hud_icons(SDL_Renderer* ren, TTF_Font* font, int sw, int sh, int jX, int jY, bool visible, int targetY, bool glitchActive) {
    if (!visible || !font) return;
    (void)sh; // Silence unused parameter warning
    int hMargin = 85 + jX, topY = targetY + jY; 
    int bW = 40, bH = 20, bX = sw - hMargin - bW; 
    const char* batP = glitchActive ? "1%" : "100%";
    const char* qual = glitchActive ? "SD" : "HD";
    SDL_Color hCol = glitchActive ? (SDL_Color){255, 0, 0, 255} : (SDL_Color){255, 255, 255, 200};

    int qX = bX - 120;
    SDL_Rect qBox = {qX - 4, topY - 5, 35, 20}; 
    SDL_SetRenderDrawColor(ren, hCol.r, hCol.g, hCol.b, hCol.a);
    SDL_RenderDrawRect(ren, &qBox);
    draw_small_hud_text(ren, font, qual, qX, topY - 6, hCol);

    if (glitchActive) draw_red_text(ren, font, batP, bX - 60, topY - 10);
    else draw_white_text(ren, font, batP, bX - 85, topY - 10);

    SDL_Rect body = {bX, topY - 5, bW, bH};
    SDL_RenderDrawRect(ren, &body);
    SDL_Rect tip = {bX + bW, topY, 3, 10}; SDL_RenderFillRect(ren, &tip);
    int segs = glitchActive ? 1 : 3;
    for(int i = 0; i < segs; i++) {
        SDL_Rect seg = {bX + 3 + (i * 12), topY - 2, 9, bH - 6};
        SDL_RenderFillRect(ren, &seg);
    }
}

void draw_hud_corners(SDL_Renderer* ren, int sw, int sh, int jX, int jY, bool visible) {
    if (!visible) return;
    SDL_SetRenderDrawColor(ren, 200, 200, 200, 150); 
    int m = 60, len = 100, th = 5;
    int mX = m + jX, mY = m + jY;
    SDL_Rect tlH = {mX, mY, len, th}, tlV = {mX, mY, th, len};
    SDL_RenderFillRect(ren, &tlH); SDL_RenderFillRect(ren, &tlV);
    SDL_Rect trH = {sw - mX - len, mY, len, th}, trV = {sw - mX - th, mY, th, len};
    SDL_RenderFillRect(ren, &trH); SDL_RenderFillRect(ren, &trV);
    SDL_Rect blH = {mX, sh - mY - th, len, th}, blV = {mX, sh - mY - len, th, len};
    SDL_RenderFillRect(ren, &blH); SDL_RenderFillRect(ren, &blV);
    SDL_Rect brH = {sw - mX - len, sh - mY - th, len, th}, brV = {sw - mX - th, sh - mY - len, th, len};
    SDL_RenderFillRect(ren, &brH); SDL_RenderFillRect(ren, &brV);
}

// --- Main Render Function ---

int render_settings(SDL_Renderer* ren, TTF_Font* font) {
    if (!font) return 0;
    int sw, sh; SDL_GetRendererOutputSize(ren, &sw, &sh);
    Uint32 now = SDL_GetTicks();
    
    // --- 1. Static & Background Setup ---
    if (!settingsBG) settingsBG = IMG_LoadTexture(ren, "assets/background.png");
    if (!settingsStaticTex) {
        settingsStaticTex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 400, 225);
        if(settingsStaticTex) SDL_SetTextureBlendMode(settingsStaticTex, SDL_BLENDMODE_BLEND);
    }
    
    if (settingsStaticTex) {
        Uint32* px; int p; SDL_LockTexture(settingsStaticTex, NULL, (void**)&px, &p);
        for (int i = 0; i < 400 * 225; i++) { Uint8 g = rand() % 65; px[i] = (g << 24) | (g << 16) | (g << 8) | 255; }
        SDL_UnlockTexture(settingsStaticTex);
    }

    // --- 2. Advanced VHS Glitch Logic ---
    static int lastCycle = -1; static bool glitchCycle = false;
    int curCycle = now / 3000;
    if (curCycle != lastCycle) { glitchCycle = (rand() % 100 < 30); lastCycle = curCycle; } 
    
    bool isGlitchingNow = (glitchCycle && (now % 3000 < 400)) || (now < saveNotificationTimer);
    int jX = 0, jY = 0; bool showHUD = true;
    if (isGlitchingNow) {
        jX = (rand() % 60) - 30; jY = (rand() % 30) - 15;
        if (rand() % 10 < 2) showHUD = false; 
    }

    // --- 3. Base Rendering ---
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren);
    if (settingsBG) {
        SDL_SetTextureColorMod(settingsBG, 100, 80, 110);
        SDL_RenderCopy(ren, settingsBG, NULL, NULL);
    }
    if (settingsStaticTex) {
        SDL_SetTextureAlphaMod(settingsStaticTex, 140);
        SDL_RenderCopy(ren, settingsStaticTex, NULL, NULL);
    }

    // --- 4. Animated Scanlines ---
    static float scanlinePos = 0;
    scanlinePos += 1.2f; if (scanlinePos > sh) scanlinePos = 0;
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, isGlitchingNow ? 160 : 70); 
    for (int i = 0; i < sh; i += 12) { 
        int y = (i + (int)scanlinePos) % sh;
        SDL_Rect line = {0, y, sw, 3}; SDL_RenderFillRect(ren, &line);
    }

    // --- 5. Input Handling ---
    int mx, my; Uint32 mState = SDL_GetMouseState(&mx, &my);
    bool isLeftDown = (mState & SDL_BUTTON(SDL_BUTTON_LEFT));
    static bool mPressed = false;
    bool justClicked = (isLeftDown && !mPressed);

    // --- 6. UI Symmetrical Layout Calculations ---
    int lM = sw / 6;
    int spacing = 85; 
    int startY = (sh / 2) - ((6 * spacing) / 2); 
    SDL_Window* win = SDL_RenderGetWindow(ren);

    // --- 7. Toggles (Screen Mode & Resolution) ---
    SDL_Rect screenBox = { lM + 250, startY, 220, 35 };
    SDL_Rect resBox    = { lM + 250, startY + spacing, 220, 35 };

    draw_settings_text(ren, font, "SCREEN MODE", lM, screenBox.y + 5);
    draw_settings_text(ren, font, "RESOLUTION",  lM, resBox.y + 5);

    SDL_SetRenderDrawColor(ren, 40, 40, 50, 255);
    SDL_RenderFillRect(ren, &screenBox); SDL_RenderFillRect(ren, &resBox);

    draw_centered_text(ren, font, screenModes[screenModeIndex], screenBox);
    draw_centered_text(ren, font, resolutions[resIndex], resBox);

    if (justClicked) {
        if (SDL_PointInRect(&(SDL_Point){mx, my}, &screenBox)) {
            screenModeIndex = (screenModeIndex + 1) % 3;
            if (screenModeIndex == 0) {
                SDL_SetWindowFullscreen(win, 0);
                SDL_HideWindow(win); SDL_ShowWindow(win); SDL_RaiseWindow(win);
            }
            else if (screenModeIndex == 1) SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
            else SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        if (SDL_PointInRect(&(SDL_Point){mx, my}, &resBox)) {
            resIndex = (resIndex + 1) % 4;
            int wArr[] = {3840, 2560, 1920, 1440}, hArr[] = {2160, 1440, 1080, 900};
            SDL_SetWindowSize(win, wArr[resIndex], hArr[resIndex]);
            SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }
    }

    // --- 8. Sliders ---
    int sliderStartY = startY + (spacing * 2);
    int* vals[] = {&masterVol, &musicVol, &brightness, &mouseSens};
    const char* labels[] = {"MASTER VOLUME", "MUSIC VOLUME", "BRIGHTNESS", "MOUSE SENSITIVITY"};

    for (int i = 0; i < 4; i++) {
        SDL_Rect s = { lM, sliderStartY + (i * spacing) + 20, 420, 30 };
        if (isLeftDown && SDL_PointInRect(&(SDL_Point){mx, my}, &s)) {
            *vals[i] = (mx - s.x) * 101 / s.w;
            if (*vals[i] < 0) { *vals[i] = 0; } 
            if (*vals[i] > 100) { *vals[i] = 100;}
            if (i == 0) Mix_Volume(-1, (*vals[0] * 128) / 100);
            if (i == 1) Mix_VolumeMusic((*vals[1] * 128) / 100);
        }
        draw_settings_text(ren, font, labels[i], s.x, s.y - 30);
        char vT[8]; snprintf(vT, sizeof(vT), "%d%%", *vals[i]);
        draw_settings_text(ren, font, vT, s.x + s.w + 15, s.y);
        
        SDL_SetRenderDrawColor(ren, 40, 40, 50, 255); SDL_RenderDrawRect(ren, &s);
        SDL_Rect fill = s; fill.w = (int)(s.w * (*vals[i] / 100.0f));
        SDL_SetRenderDrawColor(ren, 150, 0, 200, 255); SDL_RenderFillRect(ren, &fill);
    }

    // --- 9. VHS HUD ---
    if (showHUD) {
        int hudTopY = 110; 
        int rX = 85 + jX, rY = hudTopY + jY - 15; 
        if ((now / 500) % 2 == 0) { 
            SDL_SetRenderDrawColor(ren, 220, 0, 0, 255);
            int rad = 6;
            for (int w = 0; w < rad * 2; w++) {
                for (int h = 0; h < rad * 2; h++) {
                    int dx = rad - w, dy = rad - h;
                    if ((dx*dx + dy*dy) <= (rad * rad)) SDL_RenderDrawPoint(ren, rX + dx, rY + dy + 15);
                }
            }
        }
        char tStr[32]; snprintf(tStr, sizeof(tStr), "REC 00:00:%02d:%02d", (now/1000)/60, (now/1000)%60);
        draw_white_text(ren, font, tStr, rX + 22, rY);
        draw_hud_icons(ren, font, sw, sh, jX, jY, true, hudTopY, isGlitchingNow);
    }

    if (now < saveNotificationTimer) draw_vhs_save_text(ren, font, ">>TAPE SAVED", sw, sh);

    // --- 10. Buttons ---
    SDL_Rect sBtn = {lM, sh - 125, 180, 45}, bBtn = {lM + 210, sh - 125, 180, 45};
    
    bool overSave = SDL_PointInRect(&(SDL_Point){mx, my}, &sBtn);
    if (overSave && isLeftDown) { 
        SDL_SetRenderDrawColor(ren, 100, 100, 110, 255); 
        if(justClicked) save_settings(); 
    }
    else SDL_SetRenderDrawColor(ren, 188, 188, 198, 255);
    SDL_RenderFillRect(ren, &sBtn); draw_centered_text(ren, font, "SAVE", sBtn);

    bool overBack = SDL_PointInRect(&(SDL_Point){mx, my}, &bBtn);
    if (overBack && justClicked) { mPressed = isLeftDown; return 1; } 
    SDL_SetRenderDrawColor(ren, 188, 188, 198, 255);
    SDL_RenderFillRect(ren, &bBtn); draw_centered_text(ren, font, "BACK", bBtn);

    mPressed = isLeftDown; 
    draw_hud_corners(ren, sw, sh, jX, jY, showHUD);
    return 0;
}

void cleanup_settings() { 
    if (settingsStaticTex) SDL_DestroyTexture(settingsStaticTex); 
    if (settingsBG) SDL_DestroyTexture(settingsBG); 
    settingsStaticTex = NULL; settingsBG = NULL; 
}