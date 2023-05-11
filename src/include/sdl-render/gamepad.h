/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_GAMEPAD_H
#define SDL_RENDER_GAMEPAD_H

#include <stddef.h>
#include <stdbool.h>

typedef struct SrGamepad {
    int verticalAxis;
    int horizontalAxis;
    int a;
    int b;
    int menu;
} SrGamepad;

#define SR_KEY_F1 (0)
#define SR_KEY_F2 (1)
#define SR_KEY_F3 (2)
#define SR_KEY_F4 (3)
#define SR_KEY_F5 (4)
#define SR_KEY_F6 (5)
#define SR_KEY_F7 (6)
#define SR_KEY_F8 (7)
#define SR_KEY_F9 (8)
#define SR_KEY_F10 (9)
#define SR_KEY_F11 (10)
#define SR_KEY_F12 (11)

typedef struct SrFunctionKeys {
    bool functionKeys[12];
} SrFunctionKeys;


void srFunctionKeysInit(SrFunctionKeys* self);

void srGamepadInit(SrGamepad* self);
int srGamepadPoll(SrGamepad* pad, size_t maxCount, SrFunctionKeys* functionKeys);

#endif
