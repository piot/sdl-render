/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SdlWindow_h
#define SdlWindow_h

#include <SDL2/SDL.h>

typedef struct SrWindow {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SrWindow;

void srWindowInit(SrWindow* self, int width, int height, const char* name);
void srWindowRenderPrepare(SrWindow* self, uint32_t color);
void srWindowRenderPresent(SrWindow* self);
void srWindowClose(SrWindow* self);

#endif
