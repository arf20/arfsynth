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


double *gui_block = NULL;

static SDL_AudioDeviceID sink;

static vcolist_node_t *vcolist;

static float f_0 = 440.0f;

static void SDLCALL
callback(void *userdata, Uint8 *stream, int len)
{
    float *buff = (float*)stream;
    static int block_off = 0;

    for (int i = 0; i < block_size; i++) {
        float t = (float)(block_off + i) / (float)samp_rate;
        buff[i] = 0.0f;
        for (vcolist_node_t *node = vcolist; node != NULL; node = node->next)
            buff[i] += vco_sample(t, f_0, &node->data);
    }

    block_off += block_size;

    /* for graphics */
    for (int i = 0; i < block_size; i++) {
        float t = (float)(i) / (float)samp_rate;
        gui_block[i] = 0.0f;
        for (vcolist_node_t *node = vcolist; node != NULL; node = node->next)
            gui_block[i] += vco_sample(t, f_0, &node->data);
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
    gui_block = malloc(sizeof(double) * block_size);

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
    vcolist = malloc(sizeof(vcolist_node_t));
    vcolist->data = (vco_t) { SOURCE_SINE, 1.0f, 0.2f, 0.0f };

    vcolist->next = malloc(sizeof(vcolist_node_t));
    vcolist->next->data = (vco_t) { SOURCE_SINE, 2.0f, 0.2f, 0.0f };

    vcolist->next->next = malloc(sizeof(vcolist_node_t));
    vcolist->next->next->data = (vco_t) { SOURCE_SINE, 3.0f, 0.2f, 0.0f };

    vcolist->next->next->next = NULL;

    /* Start audio */
    SDL_PauseAudioDevice(sink, 0);

    return 0;
}

void
audio_deinit()
{
    SDL_CloseAudioDevice(sink);
}
