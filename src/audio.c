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

#include <stdio.h>

#include <SDL2/SDL_audio.h>

#define PI          3.1415926535897932384626

#define SAMP_RATE	48000
#define BLOCK_SIZE	1024


float *last_block = NULL;

static SDL_AudioDeviceID sink;

static void SDLCALL
callback(void *userdata, Uint8 *stream, int len)
{
	float *buff = (float*)stream;
	int block_off = 0;

	for (int i = 0; i < BLOCK_SIZE; i++) {
		float t = (float)i / (float)SAMP_RATE;
		buff[i] = sin(2.0f * PI * 440.0f * t);
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
    desired_fmt.freq =      SAMP_RATE;          /* 48KHz */
    desired_fmt.samples =   BLOCK_SIZE;         /* 1024 */
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

    /* Start audio */
    SDL_PauseAudioDevice(sink, 0);

    return 0;
}

void
audio_deinit()
{
	SDL_CloseAudioDevice(sink);
}
