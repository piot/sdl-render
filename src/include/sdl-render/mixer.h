/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef SDL_RENDER_MIXER_H
#define SDL_RENDER_MIXER_H

#include <SDL2_mixer/SDL_mixer.h>

typedef struct SrSample {
    Mix_Chunk* chunk;
} SrSample;

int srSampleLoad(SrSample* self, const char* filename);
void srSampleClose(SrSample* self);
int srSamplePlay(const SrSample* sample);
int srSampleLoop(const SrSample* sample);

typedef struct SrAudio {
    int frequency;
    Uint16 format;
    int channels;
} SrAudio;

int srAudioInit(SrAudio* self);
void srAudioClose(SrAudio* self);

#endif
