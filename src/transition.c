#include <game.h>

SDL_Texture* CreateStaticTexture(SDL_Renderer* renderer) {
    SDL_Texture* staticTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 200, 200);
    SDL_SetTextureBlendMode(staticTex, SDL_BLENDMODE_BLEND);
    return staticTex;
}

void run_transition(SDL_Renderer* ren, SDL_Texture* staticTex, float progress) {
    int sw, sh;
    SDL_GetRendererOutputSize(ren, &sw, &sh);

    Uint32* pixels; int pitch;
    SDL_LockTexture(staticTex, NULL, (void**)&pixels, &pitch);
    for (int i = 0; i < 200 * 200; i++) {
        Uint8 gray = rand() % 255;
        pixels[i] = (gray << 24) | (gray << 16) | (gray << 8) | 0xFF;
    }
    SDL_UnlockTexture(staticTex);

    float alpha = (progress < 0.5f) ? (progress * 2.0f) : (1.0f - (progress - 0.5f) * 2.0f);
    SDL_SetTextureAlphaMod(staticTex, (Uint8)(alpha * 255));
    SDL_Rect jitter = { -(rand() % 30), -(rand() % 30), sw + 60, sh + 60 };
    SDL_RenderCopy(ren, staticTex, NULL, &jitter);
}