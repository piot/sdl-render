/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_RECT_H
#define SDL_RENDER_RECT_H

#include <stdbool.h>

typedef struct SrRects {
    SDL_Renderer* renderer;
    int width;
    int height;
} SrRects;

void srRectsInit(SrRects* self, SDL_Renderer* renderer);
void srRectsLineRect(SrRects* self, int x, int y, int w, int h);
void srRectsFillRect(SrRects* self, int x, int y, int w, int h);
void srRectsDrawLine(SrRects* self, int x1, int y1, int x2, int y2);

#endif
