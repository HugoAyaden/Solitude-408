#include "../game.h"
#include <stdio.h>

// Global Settings Variables
int masterVol = 80, musicVol = 60, brightness = 50, mouseSens = 40;
static SDL_Texture* settingsStaticTex = NULL;
static SDL_Texture* settingsBG = NULL; // Texture for the space background
static Uint32 saveNotificationTimer = 0; 

// --- Save/Load Logic ---

void save_settings() {
    FILE* f = fopen("save.cfg", "w");
    if (f) {
        fprintf(f, "%d %d %d %d", masterVol, musicVol, brightness, mouseSens);
        fclose(f);
    }
    saveNotificationTimer = SDL_GetTicks() + 2000; 
}

void load_settings() {
    FILE* f = fopen("save.cfg", "r");
    if (f) {
        if (fscanf(f, "%d %d %d %d", &masterVol, &musicVol, &brightness, &mouseSens) == 4) {
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
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { (sw / 6), sh - 230, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

// --- Standard UI Helpers ---

void draw_centered_text(SDL_Renderer* ren, TTF_Font* font, const char* text, SDL_Rect btnRect) {
    if (!font) return;
    SDL_Color purple = {191, 0, 255, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, purple);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect textRect = { btnRect.x + (btnRect.w - surf->w) / 2, btnRect.y + (btnRect.h - surf->h) / 2, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &textRect);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_settings_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y) {
    if (!font) return;
    SDL_Color purple = {191, 0, 255, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, purple);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_white_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y) {
    if (!font) return;
    SDL_Color white = {255, 255, 255, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, white);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_red_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y) {
    if (!font) return;
    SDL_Color red = {255, 0, 0, 255}; 
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, red);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_small_hud_text(SDL_Renderer* ren, TTF_Font* font, const char* text, int x, int y, SDL_Color col) {
    if (!font) return;
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, col);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, (int)(surf->w * 0.7), (int)(surf->h * 0.7) }; 
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void draw_hud_icons(SDL_Renderer* ren, TTF_Font* font, int sw, int sh, int jX, int jY, bool visible, int targetY, bool glitchActive) {
    if (!visible || !font) return;
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

int render_settings(SDL_Renderer* ren, TTF_Font* font) {
    int sw, sh; SDL_GetRendererOutputSize(ren, &sw, &sh);
    Uint32 now = SDL_GetTicks();

    // Load Background Texture
    if (!settingsBG) {
        settingsBG = IMG_LoadTexture(ren, "Menu/background.png");
    }

    // 1. Static Texture
    if (!settingsStaticTex) {
        settingsStaticTex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 400, 225);
        SDL_SetTextureBlendMode(settingsStaticTex, SDL_BLENDMODE_BLEND);
    }
    Uint32* px; int p; SDL_LockTexture(settingsStaticTex, NULL, (void**)&px, &p);
    for (int i = 0; i < 400 * 225; i++) { Uint8 g = rand() % 65; px[i] = (g << 24) | (g << 16) | (g << 8) | 255; }
    SDL_UnlockTexture(settingsStaticTex);

    // Render Order: BG -> Static Overlay
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren);
    
    if (settingsBG) {
        SDL_SetTextureColorMod(settingsBG, 100, 80, 110); // Darken BG significantly
        SDL_RenderCopy(ren, settingsBG, NULL, NULL);
    }

    SDL_SetTextureAlphaMod(settingsStaticTex, 140); // Lowered alpha to see BG through it
    SDL_RenderCopy(ren, settingsStaticTex, NULL, NULL);

    // 2. Glitch State
    static int lastCycle = -1; static bool glitchCycle = false;
    int curCycle = now / 3000;
    if (curCycle != lastCycle) { glitchCycle = (rand() % 100 < 50); lastCycle = curCycle; }
    
    bool isGlitchingNow = (glitchCycle && (now % 3000 < 500)) || (now < saveNotificationTimer);

    // 3. Scanlines
    static float scanlinePos = 0;
    scanlinePos += 1.5f; if (scanlinePos > sh) scanlinePos = 0;
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, isGlitchingNow ? 140 : 80); 
    for (int i = 0; i < sh; i += 10) { 
        int y = (i + (int)scanlinePos) % sh;
        SDL_Rect line = {0, y, sw, 4}; SDL_RenderFillRect(ren, &line);
    }

    // 4. Jitter and HUD positions
    int jX = 0, jY = 0; bool showHUD = true;
    if (isGlitchingNow) {
        jX = (rand() % 120) - 60; jY = (rand() % 60) - 30;
        if (rand() % 10 < 9) showHUD = false;
    }

    // 5. VHS Green Save Prompt
    if (now < saveNotificationTimer) {
        draw_vhs_save_text(ren, font, ">> TAPE SAVED", sw, sh);
    }

    // 6. HUD
    int rY_Base = 110; 
    if (showHUD) {
        int rX = 85 + jX, rY = rY_Base + jY, rad = 8;
        if ((now / 500) % 2 == 0) {
            SDL_SetRenderDrawColor(ren, 220, 0, 0, 255);
            for (int w = 0; w < rad * 2; w++) for (int h = 0; h < rad * 2; h++) {
                int dx = rad - w, dy = rad - h; if ((dx*dx + dy*dy) <= (rad * rad)) SDL_RenderDrawPoint(ren, rX + dx, rY + dy);
            }
        }
        char tStr[32]; snprintf(tStr, sizeof(tStr), "REC 00:00:%02d:%02d", (now/1000)/60, (now/1000)%60);
        draw_white_text(ren, font, tStr, rX + 22, rY - 10);
        draw_hud_icons(ren, font, sw, sh, jX, jY, showHUD, rY_Base, isGlitchingNow);
    }

    // 7. UI Controls
    int lM = sw / 6; 
    SDL_Rect sliders[] = { {lM, sh/4, 420, 35}, {lM, sh/4+100, 420, 35}, {lM, sh/4+200, 420, 35}, {lM, sh/4+300, 420, 35} };
    int* vals[] = {&masterVol, &musicVol, &brightness, &mouseSens};
    const char* labels[] = {"MASTER VOLUME", "MUSIC VOLUME", "BRIGHTNESS", "MOUSE SENSITIVITY"};
    SDL_Rect sBtn = {lM, sh-180, 180, 50}, bBtn = {lM + 210, sh-180, 180, 50};

    int mx, my; Uint32 mState = SDL_GetMouseState(&mx, &my);
    bool isLeftDown = (mState & SDL_BUTTON(SDL_BUTTON_LEFT));

    if (isLeftDown) {
        for (int i = 0; i < 4; i++) if (mx >= sliders[i].x && mx <= sliders[i].x + sliders[i].w && my >= sliders[i].y && my <= sliders[i].y + sliders[i].h) {
            *vals[i] = (mx - sliders[i].x) * 100 / sliders[i].w;
            if (i == 0) Mix_Volume(-1, (*vals[0] * MIX_MAX_VOLUME) / 100);
            if (i == 1) Mix_VolumeMusic((*vals[1] * MIX_MAX_VOLUME) / 100);
        }
    }

    for (int i = 0; i < 4; i++) {
        draw_settings_text(ren, font, labels[i], sliders[i].x, sliders[i].y - 35);
        char vT[8]; snprintf(vT, sizeof(vT), "%d%%", *vals[i]);
        draw_settings_text(ren, font, vT, sliders[i].x + sliders[i].w + 20, sliders[i].y + 5);
        SDL_SetRenderDrawColor(ren, 40, 40, 50, 255); SDL_RenderDrawRect(ren, &sliders[i]);
        SDL_Rect f = sliders[i]; f.w = (int)(f.w * (*vals[i] / 100.0f));
        SDL_SetRenderDrawColor(ren, 150, 0, 200, 255); SDL_RenderFillRect(ren, &f);
    }

    // Buttons
    bool overSave = (mx >= sBtn.x && mx <= sBtn.x + sBtn.w && my >= sBtn.y && my <= sBtn.y + sBtn.h);
    if (overSave && isLeftDown) { SDL_SetRenderDrawColor(ren, 100, 100, 110, 255); save_settings(); }
    else SDL_SetRenderDrawColor(ren, 188, 188, 198, 255);
    SDL_RenderFillRect(ren, &sBtn); draw_centered_text(ren, font, "SAVE", sBtn);

    bool overBack = (mx >= bBtn.x && mx <= bBtn.x + bBtn.w && my >= bBtn.y && my <= bBtn.y + bBtn.h);
    if (overBack && isLeftDown) {
        SDL_SetRenderDrawColor(ren, 100, 100, 110, 255); SDL_RenderFillRect(ren, &bBtn);
        draw_centered_text(ren, font, "BACK", bBtn);
        return 1;
    } else {
        SDL_SetRenderDrawColor(ren, 188, 188, 198, 255); SDL_RenderFillRect(ren, &bBtn);
        draw_centered_text(ren, font, "BACK", bBtn);
    }

    draw_hud_corners(ren, sw, sh, jX, jY, showHUD);
    return 0;
}

void cleanup_settings() { 
    if (settingsStaticTex) SDL_DestroyTexture(settingsStaticTex); 
    if (settingsBG) SDL_DestroyTexture(settingsBG); // Cleanup background
    settingsStaticTex = NULL; 
    settingsBG = NULL; 
}