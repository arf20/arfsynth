/*

    arfsynth: Simple modular software synth
    Copyright (C) 2023 arf20 (Ángel Ruiz Fernandez)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    audio.c: Audio interface

*/

#include "audio.h"
#include "config.h"
#include "sources.h"

#include <stdio.h>

#include <SDL2/SDL_audio.h>


float *last_block = NULL;

static SDL_AudioDeviceID sink;

static source_node_t *sources;

static void SDLCALL
callback(void *userdata, Uint8 *stream, int len)
{
    float *buff = (float*)stream;
    static int block_off = 0;

    for (int i = 0; i < block_size; i++) {
        float t = (float)(block_off + i) / (float)samp_rate;
        buff[i] = 0.0f;
        for (source_node_t *s = sources; s != NULL; s = s->next)
            buff[i] += source_sample(t, &s->source);
    }

    block_off += block_size;

    /* for graphics */
    for (int i = 0; i < block_size; i++) {
        float t = (float)(i) / (float)samp_rate;
        last_block[i] = 0.0f;
        for (source_node_t *s = sources; s != NULL; s = s->next)
            last_block[i] += source_sample(t, &s->source);
    }
}

void
audio_enum_drivers()
{
    int num_drivers = SDL_GetNumAudioDrivers();
    printf("Audio drivers [%d]:\n", num_drivers);
    for (int i = 0; i < num_drivers; i++)
        printf("\t%s\n", SDL_GetAudioDriver(i));
}

int
audio_enum_devices(const char *driver)
{
    if (SDL_AudioInit(driver) < 0) {
        printf("Cannot initialize driver: %d\n", SDL_GetError());
        return -1;
    }

    int num_devs = SDL_GetNumAudioDevices(SDL_FALSE);
    printf("Output devices for %s [%d]:\n", driver, num_devs);
    for (int i = 0; i < num_devs; i++)
        printf("\t%s\n", SDL_GetAudioDeviceName(i, SDL_FALSE));

    SDL_AudioQuit();
}

int
audio_init()
{
    /* Allocate graphic buffer */
    last_block = malloc(sizeof(float) * block_size);

    /* Driver init */
    if (SDL_AudioInit(audio_driver) < 0) {
        printf("Cannot initialize driver: %d\n", SDL_GetError());
        return -1;
    }

    /* Format, dev open and callback set */

    /* Sample format */
    SDL_AudioSpec desired_fmt = { };
    desired_fmt.format =    AUDIO_F32SYS;       /* Signed int (32 bits) */
    desired_fmt.channels =  1;                  /* Stereo */
    desired_fmt.freq =      samp_rate;          /* 48KHz */
    desired_fmt.samples =   block_size;         /* 1024 */
    desired_fmt.callback =  callback;
    desired_fmt.userdata =  NULL;

    SDL_AudioSpec obtained_fmt = { };


    sink = SDL_OpenAudioDevice(
        audio_device, SDL_FALSE, &desired_fmt, &obtained_fmt, 0
    );
    
    if (sink == 0) {
        printf("Cannot open output device: %d\n", SDL_GetError());
        return -1;
    }

    /* sample chord */
    sources = malloc(sizeof(source_node_t));
    sources->source = (source_t) { SOURCE_SINE, 440.0f, 0.2f, 0.0f };

    sources->next = malloc(sizeof(source_node_t));
    sources->next->source = (source_t) { SOURCE_SINE, 261.63f, 0.2f, 0.0f };

    sources->next->next = malloc(sizeof(source_node_t));
    sources->next->next->source = (source_t) { SOURCE_SINE, 329.63f, 0.2f, 0.0f };

    sources->next->next = NULL;

    /* Start audio */
    SDL_PauseAudioDevice(sink, 0);

    return 0;
}

void
audio_deinit()
{
    SDL_CloseAudioDevice(sink);
}
