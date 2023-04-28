/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_FONT_H
#define SDL_RENDER_FONT_H

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdbool.h>

typedef struct SrFont {
    TTF_Font* font;
    SDL_Renderer* renderer;
} SrFont;

typedef struct SrTextTexture {
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect sourceRect;
} SrTextTexture;

void srFontInit(SrFont* self, SDL_Renderer* renderer, const char* ttfFile, int fontSize);
SrTextTexture srFontRender(const SrFont* self, const char* text, SDL_Color color);
void srFontRenderAndCopy(const SrFont* self, const char* text, int x, int y, SDL_Color color);
void srFontDestroy(SrFont* self);
void srTextTextureRender(SrTextTexture* self, int x, int y);
void srTextTextureDestroy(SrTextTexture* self);

#endif
