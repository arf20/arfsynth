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

    gui.c: SDL User Interface

*/

#include "gui.h"

#include "config.h"
#include "audio.h"

#include <unistd.h>
#include <sys/param.h>

#include <SDL2/SDL.h>

#include <fftw3.h>


typedef struct {
    struct {
        double top, bottom;
    } scope;
    struct {
        double top, bottom;
    } spectrograph;
} layout_t;


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static layout_t layout;

static fftw_plan fft_plan = NULL;
static double *spectrum = NULL;

int
gui_init()
{
    /* Init SDL, create window and renderer */
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "arfsynth",                         // window title
        SDL_WINDOWPOS_UNDEFINED,            // initial x position
        SDL_WINDOWPOS_UNDEFINED,            // initial y position
        width,                              // width, in pixels
        height,                             // height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        printf("Error opening window: %d\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (!renderer) {
        printf("Error creating renderer: %d\n", SDL_GetError());
        return -1;
    }

    layout = (layout_t) {
        0.66f, 1.0f,
        0.33f, 0.66f
    };

    /* Allocate and define FFT spectrum */
    spectrum = malloc(sizeof(double) * block_size);

    fft_plan = fftw_plan_r2r_1d(block_size, gui_block, spectrum,
        FFTW_R2HC, FFTW_ESTIMATE);



    return 0;
}

int
scope_y_map(double s)
{
    return (((layout.scope.bottom - layout.scope.top) * 0.5 * ((-s) + 1.0))
        + layout.scope.top) * height;
}

int
spectrum_y_map(double s, double max_abs)
{
    //s = 20.0*log(abs(s));
    s = 20.0*log(fabs(s) / max_abs);
    
    s = (s - -100.0) 
        * (layout.spectrograph.top - layout.spectrograph.bottom)
        / (3.0 - -100.0)
        + layout.spectrograph.bottom;
    if (s < layout.spectrograph.top) s = layout.spectrograph.top;
    if (s > layout.spectrograph.bottom) s = layout.spectrograph.bottom;
    s *= height;
    printf("%f\n", s);
    //if (s > 3.0) return layout.spectrograph.top * height;
    //f (s < -100.0) return layout.spectrograph.bottom * height;
    return (int)s;
}

void
gui_loop()
{
    int run = 1;
    SDL_Event event;

    while (run) {
        /* Compute FFT spectrum */
        fftw_execute(fft_plan);

        /* Render Clear */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /* Draw layout */
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderDrawLine(renderer, 0, scope_y_map(1.0f),
            width, scope_y_map(1.0f));
        SDL_RenderDrawLine(renderer, 0, layout.spectrograph.top * height,
            width, layout.spectrograph.top * height);

        /* Draw waveform scope */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < block_size - 1; i++) {
            SDL_RenderDrawLine(renderer, i, scope_y_map(gui_block[i]),
                i + 1, scope_y_map(gui_block[i + 1]));
        }

        /* Draw FFT spectrograph */
        double max_abs = 0.0;
        for (int i = 0; i < block_size; i++) {
            max_abs = MAX(max_abs, spectrum[i]);
        }
        //printf("%f\n", max_abs);

        for (int i = 0; i < block_size - 1; i++) {
            SDL_RenderDrawLine(renderer, 2*i, spectrum_y_map(spectrum[i], max_abs),
                2*(i+1), spectrum_y_map(spectrum[i + 1], max_abs));
            //printf("%d\n", spectrum_y_map(spectrum[i]));
        }

        SDL_RenderPresent(renderer);

        usleep(17000);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    run = 0;
                    return;
                } break;
                case SDL_KEYDOWN: {
                    
                } break;
            }
        }
    }
}

void
gui_deinit()
{
    fftw_destroy_plan(fft_plan);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
