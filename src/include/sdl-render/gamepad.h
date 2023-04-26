/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_GAMEPAD_H
#define SDL_RENDER_GAMEPAD_H

typedef struct SrGamepad {
    int verticalAxis;
    int horizontalAxis;
    int a;
    int b;
    int menu;
} SrGamepad;

void srGamepadInit(SrGamepad* self);
int srGamepadPoll(SrGamepad* pad);

#endif
