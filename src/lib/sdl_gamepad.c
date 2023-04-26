/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <sdl-render/gamepad.h>
#include <SDL2/SDL.h>
#include <clog/clog.h>

static void keyChange(SrGamepad* target, SDL_Keycode sym, int invert)
{
    switch (sym)
    {
        case SDLK_w:
            target->verticalAxis += invert;
            break;
        case SDLK_s:
            target->verticalAxis -= invert;
            break;
        case SDLK_d:
            target->horizontalAxis += invert;
            break;
        case SDLK_a:
            target->horizontalAxis -= invert;
            break;
        case SDLK_SPACE:
            target->a += invert;
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
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
                if (event.key.repeat) {
                    break;
                }
                keyChange(target, event.key.keysym.sym, 1);
                break;
            case SDL_KEYUP:
                if (event.key.repeat) {
                    break;
                }
                keyChange(target, event.key.keysym.sym, -1);
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
}

int srGamepadPoll(SrGamepad* pad)
{
    int i = checkSdlEvent(pad);

    CLOG_VERBOSE("gamepad: %d %d %d", pad->horizontalAxis, pad->verticalAxis, pad->a)
    return i;
}
