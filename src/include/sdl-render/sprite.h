/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_SPRITE_H
#define SDL_RENDER_SPRITE_H

#include <stdbool.h>

typedef struct SrSprites {
    SDL_Renderer* renderer;
} SrSprites;

typedef struct SrSprite {
    SDL_Texture* texture;
    SDL_Rect rect;
} SrSprite;

void srSpritesInit(SrSprites* self, SDL_Renderer* renderer);
void srSpritesCopy(SrSprites* self, const SrSprite* sprite, int x, int y, bool center);
void srSpritesCopyEx(SrSprites* self, const SrSprite* sprite, int x, int y, int rotate, float scale);

#endif
