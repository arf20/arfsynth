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

#include <SDL2/SDL.h>


#define WWIDTH  1280
#define WHEIGHT 720


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int
gui_init()
{
    /* Init SDL, create window and renderer */
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "arfsynth",                   // window title
        SDL_WINDOWPOS_UNDEFINED,            // initial x position
        SDL_WINDOWPOS_UNDEFINED,            // initial y position
        WWIDTH,                             // width, in pixels
        WHEIGHT,                            // height, in pixels
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

    return 0;
}

void
gui_loop()
{
    int run = 1;
    SDL_Event event;

    while (run) {
        /* Clear */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);



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
