/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <SDL2/SDL.h>
#include <clog/clog.h>
#include <sdl-render/gamepad.h>
#include <stdbool.h>

static void keyChange(SrGamepad* targets, SDL_Keycode sym, int invert)
{
    switch (sym)
    {
        case SDLK_w:
            targets[0].verticalAxis += invert;
            break;
        case SDLK_s:
            targets[0].verticalAxis -= invert;
            break;
        case SDLK_d:
            targets[0].horizontalAxis += invert;
            break;
        case SDLK_a:
            targets[0].horizontalAxis -= invert;
            break;
        case SDLK_SPACE:
            targets[0].a += invert;
            break;
        case SDLK_ESCAPE:
        case SDLK_LSHIFT:
            targets[0].b += invert;

        case SDLK_i:
            targets[1].verticalAxis += invert;
            break;
        case SDLK_k:
            targets[1].verticalAxis -= invert;
            break;
        case SDLK_l:
            targets[1].horizontalAxis += invert;
            break;
        case SDLK_j:
            targets[1].horizontalAxis -= invert;
            break;
        case SDLK_h:
            targets[1].a += invert;
            break;

    }
}

static int checkSdlEvent(SrGamepad* target) {
    SDL_Event event;
    int quit = 0;

    if (SDL_PollEvent(&event)) {

        switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKQUOTE) {
                    quit = 1;
                }
                if (event.key.repeat) {
                    break;
                }
                if (event.key.keysym.sym == SDLK_F2) {
                    target->menu = 1;
                }
                keyChange(target, event.key.keysym.sym, 1);
                break;
            case SDL_KEYUP:
                if (event.key.repeat) {
                    break;
                }
                keyChange(target, event.key.keysym.sym, -1);
                if (event.key.keysym.sym == SDLK_F2) {
                    target->menu = 0;
                }
                break;
            case SDL_TEXTINPUT:
                break;
        }
    }

    return quit;
}

void srGamepadInit(SrGamepad* self)
{
    self->verticalAxis = 0;
    self->horizontalAxis = 0;
    self->a = 0;
    self->menu = 0;
}

int srGamepadPoll(SrGamepad* pads, size_t count)
{
    int i = checkSdlEvent(pads);

    //CLOG_VERBOSE("gamepad: %d %d %d  1: %d", pads[0].horizontalAxis, pads[0].verticalAxis, pads[0].a, pads[1].horizontalAxis)
    return i;
}
