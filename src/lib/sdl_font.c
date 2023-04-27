/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "sdl-render/util.h"
#include <clog/clog.h>
#include <sdl-render/font.h>

void srFontInit(SrFont* self, SDL_Renderer* renderer, const char* ttfFile, int fontSize)
{
    TTF_Init();

    TTF_Font* font = TTF_OpenFont(ttfFile, fontSize);
    if (font == 0) {
        CLOG_ERROR("could not load font '%s'", ttfFile)
        return;
    }

    self->font = font;
    self->renderer = renderer;
}

void srFontDestroy(SrFont* self)
{
    TTF_CloseFont(self->font);
}

SrTextTexture srFontRender(SrFont* self, const char* text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(self->font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(self->renderer, surface);

    SrTextTexture result;

    result.surface = surface;
    result.texture = texture;
    result.renderer = self->renderer;
    result.sourceRect.x = 0;
    result.sourceRect.y = 0;
    result.sourceRect.w = surface->w;
    result.sourceRect.h = surface->h;

    return result;
}

void srTextTextureRender(SrTextTexture* self, int x, int y)
{
    int width;
    int height;
    SDL_GetRendererOutputSize(self->renderer, &width, &height);
    SDL_Rect dest = {x, SrFlipY(y, height), self->surface->w, self->surface->h};
    SDL_RenderCopy(self->renderer, self->texture, &self->sourceRect, &dest);
}

void srTextTextureDestroy(SrTextTexture* self)
{
    SDL_FreeSurface(self->surface);
    SDL_DestroyTexture(self->texture);
}

void srFontRenderAndCopy(SrFont* self, const char* text, int x, int y, SDL_Color color)
{
    SrTextTexture textTexture = srFontRender(self, text, color);
    srTextTextureRender(&textTexture, x, y);
    srTextTextureDestroy(&textTexture);
}
