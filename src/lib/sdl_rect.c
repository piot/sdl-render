/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <SDL2/SDL.h>
#include <sdl-render/rect.h>
#include <sdl-render/util.h>

void srRectsInit(SrRects* self, SDL_Renderer* renderer)
{
    self->renderer = renderer;
    SDL_GetRendererOutputSize(renderer, &self->width, &self->height);
}

void srRectsLineRect(SrRects* self, int x, int y, int w, int h)
{
    SDL_Rect sdlRect;
    sdlRect.x = x;
    sdlRect.y = SrFlipYHeight(y, self->height, h);
    sdlRect.w = w;
    sdlRect.h = h;
    SDL_RenderDrawRect(self->renderer, &sdlRect);
}

void srRectsFillRect(SrRects* self, int x, int y, int w, int h)
{
    SDL_Rect sdlRect;
    sdlRect.x = x;
    sdlRect.y = SrFlipYHeight(y, self->height, h);
    sdlRect.w = w;
    sdlRect.h = h;
    SDL_RenderFillRect(self->renderer, &sdlRect);
}

void srRectsDrawLine(SrRects* self, int x1, int y1, int x2, int y2)
{
    int wrappedY1 = SrFlipY(y1, self->height);
    int wrappedY2 = SrFlipY(y2, self->height);

    SDL_RenderDrawLine(self->renderer,
                       x1, wrappedY1, x2, wrappedY2);
}
