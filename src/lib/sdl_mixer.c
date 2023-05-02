/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <sdl-render/mixer.h>
#include <clog/clog.h>

int srSampleLoad(SrSample* self, const char* filename)
{
    self->chunk = Mix_LoadWAV(filename);
    if (!self->chunk) {
        return -44;
    }
    return 0;
}

void srSampleClose(SrSample* self)
{
    Mix_FreeChunk(self->chunk);
    self->chunk = 0;
}

int srAudioInit(SrAudio* self)
{
    int result = Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 256);
    if (result < 0) {
        CLOG_ERROR("could not to open audio %s", SDL_GetError());
        return result;
    }

    result = Mix_AllocateChannels(4);
    if (result < 0) {
        CLOG_ERROR("could not to allocate mixing channels: %s", SDL_GetError());
        return result;
    }

    result = Mix_QuerySpec(&self->frequency, &self->format, &self->channels);
    if (result < 0)
    {
        return -1;
    }
    CLOG_DEBUG("audio init: %d %d bits %d channels", self->frequency, self->format, self->channels)

    return 0;
}

int srSamplePlay(const SrSample* sample)
{
    CLOG_VERBOSE("playing sample")
    return Mix_PlayChannel(-1, sample->chunk, 0);
}

int srSampleLoop(const SrSample* sample)
{
    return Mix_PlayChannel(-1, sample->chunk, -1);
}

void srAudioClose(SrAudio* self)
{
    Mix_CloseAudio();
}
