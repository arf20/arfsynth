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

#include <SDL2/SDL.h>


typedef struct {
    struct scope {
        float top, bottom;
    } scope;
} layout_t;


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static layout_t layout;

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
        0.66f, 1.0f
    };

    

    return 0;
}

int
scope_y_map(float s)
{
    return (((layout.scope.bottom - layout.scope.top) * 0.5f * (s + 1.0f))
        + layout.scope.top) * height;
}

void
gui_loop()
{
    int run = 1;
    SDL_Event event;

    while (run) {
        /* Render Clear */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /* Draw layout */
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
        SDL_RenderDrawLine(renderer, 0, scope_y_map(1.0f),
            width, scope_y_map(1.0f));

        /* Draw waveforms */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < block_size - 1; i++) {
            SDL_RenderDrawLine(renderer, i, scope_y_map(last_block[i]),
                i + 1, scope_y_map(last_block[i + 1]));
        }

        SDL_RenderPresent(renderer);

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
