/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_SPRITE_H
#define SDL_RENDER_SPRITE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct SrSprite {
    SDL_Texture* texture;
    SDL_Rect rect;
} SrSprite;

void srSpriteInit(SrSprite* self, SDL_Texture* texture, SDL_Rect rect);

typedef struct SrSprites {
    SDL_Renderer* renderer;
    int width;
    int height;
} SrSprites;

void srSpritesInit(SrSprites* self, SDL_Renderer* renderer);
void srSpritesCopy(SrSprites* self, const SrSprite* sprite, int x, int y, bool center, Uint8 alpha);
void srSpritesCopyEx(SrSprites* self, const SrSprite* sprite, int x, int y, int rotate, float scale,  Uint8 alpha);

#endif
