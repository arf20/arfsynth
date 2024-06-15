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

#include <stdio.h>

#include <SDL2/SDL_audio.h>


static SDL_AudioDeviceID sink;

static void SDLCALL
callback(void *userdata, Uint8 *stream, int len)
{

}

int
audio_init()
{
    /* Driver enum, select and init */
    int num_drivers = SDL_GetNumAudioDrivers();
    printf("Audio drivers [%d]:\n", num_drivers);
    for (int i = 0; i < num_drivers; i++)
        printf("\t#%d: %s\n", i, SDL_GetAudioDriver(i));
    int driver_i = 0;
    printf("> ");
    scanf("%d", &driver_i);

    if (SDL_AudioInit(SDL_GetAudioDriver(driver_i)) < 0) {
        printf("Cannot initialize driver: %d\n", SDL_GetError());
        return -1;
    }


    /* Sink enum, select */
    int num_sinks = SDL_GetNumAudioDevices(SDL_FALSE);
    printf("Output devices [%d]:\n", num_sinks);
    for (int i = 0; i < num_sinks; i++)
        printf("\t#%d: %s\n", i, SDL_GetAudioDeviceName(i, SDL_FALSE));
    int sink_i = 0;
    printf("> ");
    scanf("%d", &sink_i);

    /* Format, dev open and callback set */

    /* Sample format */
    SDL_AudioSpec desired_fmt = { };
    desired_fmt.format =    AUDIO_S32SYS;       /* Signed int (32 bits) */
    desired_fmt.channels =  1;                  /* Stereo */
    desired_fmt.freq =      48000;              /* 48KHz */
    desired_fmt.samples =   1024;               /* 1024 */
    desired_fmt.callback =  callback;
    desired_fmt.userdata =  NULL;

    SDL_AudioSpec obtained_fmt = { };


    sink = SDL_OpenAudioDevice(
        SDL_GetAudioDeviceName(sink_i, SDL_FALSE),
        SDL_FALSE, &desired_fmt, &obtained_fmt, 0);
    
    if (sink == 0) {
        printf("Cannot open output device: %d\n", SDL_GetError());
        return -1;
    }

    /* Start audio */
    SDL_PauseAudioDevice(sink, 0);

    return 0;
}

void
audio_deinit()
{
	SDL_CloseAudioDevice(sink);
}
