/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "clog/clog.h"
#include "sdl-render/util.h"
#include <SDL2/SDL.h>
#include <sdl-render/sprite.h>

void srSpritesInit(SrSprites* self, SDL_Renderer* renderer)
{
    self->renderer = renderer;
    SDL_GetRendererOutputSize(renderer, &self->width, &self->height);
}

void srSpritesCopy(SrSprites* self, const SrSprite* sprite, int x, int y, bool center)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = SrFlipY(y, self->height);
    dest.w = sprite->rect.w;
    dest.h = sprite->rect.h;

    if (center) {
        dest.x -= (dest.w / 2);
        dest.y -= (dest.h / 2);
    }

    SDL_RenderCopy(self->renderer, sprite->texture, &sprite->rect, &dest);
}

void srSpritesCopyEx(SrSprites* self, const SrSprite* sprite, int x, int y, int rotate, float scale)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_Rect dest;

    dest.x = x;
    dest.y = SrFlipY(y, self->height);
    dest.w = (int) ((float) sprite->rect.w * scale);
    dest.h = (int) ((float) sprite->rect.h * scale);

    if (true) {
        dest.x -= (dest.w / 2);
        dest.y -= (dest.h / 2);
    }

    SDL_Point center = {(dest.w / 2), (dest.h / 2)};

    int result = SDL_RenderCopyEx(self->renderer, sprite->texture, &sprite->rect, &dest, -rotate, &center, flip);

    if (result != 0) {
        CLOG_ERROR("could not render")
    }
}
