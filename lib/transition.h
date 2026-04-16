/**
 * \file transition.h
 * \brief Animation between two screens (static effect)
 * \author ?
 * \version 1.0
 * \date ?
 */

#ifndef TRANSITION_H
#define TRANSITION_H

#include <SDL2/SDL.h>

/**
 * \brief Renders the animated static transition effect.
 *
 * Generates fresh TV static noise, applies smooth alpha fade (build-up then fade-out),
 * and adds random jitter offset for authentic CRT interference look.
 *
 * \param ren SDL renderer.
 * \param staticTex Pre-allocated static texture from CreateStaticTexture().
 * \param progress Transition progress (0.0 = start, 1.0 = end).
 */

void run_transition(SDL_Renderer* ren, SDL_Texture* staticTex, float progress);

/**
 * \brief Creates a streaming static texture for transition effects.
 *
 * Allocates a 200x200 RGBA texture optimized for real-time static generation
 * with blend mode enabled for alpha overlay.
 *
 * \param renderer SDL renderer used for texture creation.
 * \return Pointer to the static texture, or NULL on failure.
 */

SDL_Texture* CreateStaticTexture(SDL_Renderer* renderer);

#endif
