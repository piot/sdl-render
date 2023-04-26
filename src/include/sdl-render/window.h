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

typedef void (*SrVSyncFn)(void* self, SrWindow* window);
void srWindowInit(SrWindow* self, int width, int height, const char* name);
void srWindowRender(SrWindow* self, uint32_t color, void* userdata, SrVSyncFn callback);
void srWindowClose(SrWindow* self);

#endif
