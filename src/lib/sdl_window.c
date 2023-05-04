/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "clog/clog.h"
#include <sdl-render/window.h>

void srWindowInit(SrWindow* self, int windowWidth, int windowHeight, const char* windowName)
{
    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    // SDL_INIT_NOPARACHUTE
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS ) < 0) { // | SDL_INIT_AUDIO
        printf("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
                                          windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS);
    if (window == 0) {
        CLOG_ERROR("SDL Window could not be created! SDL_Error: %s", SDL_GetError());
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == 0) {
        CLOG_ERROR("SDL Renderer could not be created")
    }
    SDL_RaiseWindow(window);
    self->renderer = renderer;
}

void srWindowRender(SrWindow* self, uint32_t background_color, void* userdata, SrVSyncFn callback)
{
    Uint8 r = background_color & 0xff;
    Uint8 g = (background_color >> 8) & 0xff;
    Uint8 b = (background_color >> 16) & 0xff;
    Uint8 a = SDL_ALPHA_OPAQUE;

    int result = SDL_SetRenderDrawColor(self->renderer, r, g, b, a);
    if (result != 0) {
        CLOG_ERROR("SDL could not set draw color")
    }

    SDL_RenderClear(self->renderer);
    callback(userdata, self);
    SDL_RenderPresent(self->renderer);
}

void srWindowClose(SrWindow* self)
{
    CLOG_DEBUG("closing sdl window and quitting")
    SDL_DestroyWindow(self->window);
    SDL_Quit();
}
