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

*/

#ifndef _KEYMAP_H
#define _KEYMAP_H

#include <SDL2/SDL.h>

typedef enum {
    C0,
    C0S,
    D0,
    D0S,
    E0,
    F0,
    F0S,
    G0,
    G0S,
    A0,
    A0S,
    B0,
    C1,
    C1S,
    D1,
    D1S,
    E1,
    F1,
    F1S,
    G1,
    G1S,
    A1,
    A1S,
    B1,
    C2,
    C2S,
    D2,
    D2S,
    E2,
    F2,
    F2S,
    G2,
    G2S,
    A2,
    A2S,
    B2,
    C3,
    C3S,
    D3,
    D3S,
    E3,
    F3,
    F3S,
    G3,
    G3S,
    A3,
    A3S,
    B3,
    C4,
    C4S,
    D4,
    D4S,
    E4,
    F4,
    F4S,
    G4,
    G4S,
    A4,
    A4S,
    B4,
    C5,
    C5S,
    D5,
    D5S,
    E5,
    F5,
    F5S,
    G5,
    G5S,
    A5,
    A5S,
    B5,
    C6,
    C6S,
    D6,
    D6S,
    E6,
    F6,
    F6S,
    G6,
    G6S,
    A6,
    A6S,
    B6,
    C7,
    C7S,
    D7,
    D7S,
    E7,
    F7,
    F7S,
    G7,
    G7S,
    A7,
    A7S,
    B7,
    C8,
    C8S,
    D8,
    D8S,
    E8,
    F8,
    F8S,
    G8,
    G8S,
    A8,
    A8S,
    B8,
    C9,
    C9S,
    D9,
    D9S,
    E9,
    F9,
    F9S,
    G9,
    G9S,
    A9,
    A9S,
    B9,
} note_t;

float freqs[120] = {
    16.351f,
    17.324f,
    18.354f,
    19.445f,
    20.601f,
    21.827f,
    23.124f,
    24.499f,
    25.956f,
    27.5f,
    29.135f,
    30.868f,
    32.703f,
    34.648f,
    36.708f,
    38.891f,
    41.203f,
    43.654f,
    46.249f,
    48.999f,
    51.913f,
    55.0f,
    58.27f,
    61.735f,
    65.406f,
    69.296f,
    73.416f,
    77.782f,
    82.407f,
    87.307f,
    92.499f,
    97.999f,
    103.826f,
    110.0f,
    116.541f,
    123.471f,
    130.813f,
    138.591f,
    146.832f,
    155.563f,
    164.814f,
    174.614f,
    184.997f,
    195.998f,
    207.652f,
    220.0f,
    233.082f,
    246.942f,
    261.626f,
    277.183f,
    293.665f,
    311.127f,
    329.628f,
    349.228f,
    369.994f,
    391.995f,
    415.305f,
    440.0f,
    466.164f,
    493.883f,
    523.251f,
    554.365f,
    587.33f,
    622.254f,
    659.255f,
    698.456f,
    739.989f,
    783.991f,
    830.609f,
    880.0f,
    932.328f,
    987.767f,
    1046.502f,
    1108.731f,
    1174.659f,
    1244.508f,
    1318.51f,
    1396.913f,
    1479.978f,
    1567.982f,
    1661.219f,
    1760.0f,
    1864.655f,
    1975.533f,
    2093.005f,
    2217.461f,
    2349.318f,
    2489.016f,
    2637.021f,
    2793.826f,
    2959.955f,
    3135.964f,
    3322.438f,
    3520.0f,
    3729.31f,
    3951.066f,
    4186.009f,
    4434.922f,
    4698.636f,
    4978.032f,
    5274.042f,
    5587.652f,
    5919.91f,
    6271.928f,
    6644.876f,
    7040.0f,
    7458.62f,
    7902.132f,
    8372.018f,
    8869.844f,
    9397.272f,
    9956.064f,
    10548.084f,
    11175.304f,
    11839.82f,
    12543.856f,
    13289.752f,
    14080.0f,
    14917.24f,
    15804.264f
};

note_t keymap[256] = {
    [SDL_SCANCODE_NONUSBACKSLASH] = C3,
    [SDL_SCANCODE_Z] =              D3,
    [SDL_SCANCODE_X] =              E3,
    [SDL_SCANCODE_C] =              F3,
    [SDL_SCANCODE_V] =              G3,
    [SDL_SCANCODE_B] =              A3,
    [SDL_SCANCODE_N] =              B3,

    [SDL_SCANCODE_M] =              C4,
    [SDL_SCANCODE_COMMA] =          D4,
    [SDL_SCANCODE_PERIOD] =         E4,
    [SDL_SCANCODE_SLASH] =          F4,
    [SDL_SCANCODE_RSHIFT] =         G4,

    [SDL_SCANCODE_A] =              C3S,
    [SDL_SCANCODE_S] =              D3S,
    [SDL_SCANCODE_F] =              F3S,
    [SDL_SCANCODE_G] =              G3S,
    [SDL_SCANCODE_H] =              A3S,

    [SDL_SCANCODE_K] =              C4S,
    [SDL_SCANCODE_L] =              D4S,
    [SDL_SCANCODE_APOSTROPHE] =     F4S,
    [SDL_SCANCODE_BACKSLASH] =      G4S,


    [SDL_SCANCODE_Q] =              C4,
    [SDL_SCANCODE_W] =              D4,
    [SDL_SCANCODE_E] =              E4,
    [SDL_SCANCODE_R] =              F4,
    [SDL_SCANCODE_T] =              G4,
    [SDL_SCANCODE_Y] =              A4,
    [SDL_SCANCODE_U] =              B4,

    [SDL_SCANCODE_I] =              C5,
    [SDL_SCANCODE_O] =              D5,
    [SDL_SCANCODE_P] =              E5,
    [SDL_SCANCODE_LEFTBRACKET] =    F5,
    [SDL_SCANCODE_RIGHTBRACKET] =   G5,

    [SDL_SCANCODE_2] =              C4S,
    [SDL_SCANCODE_3] =              D4S,
    [SDL_SCANCODE_5] =              F4S,
    [SDL_SCANCODE_6] =              G4S,
    [SDL_SCANCODE_7] =              A4S,

    [SDL_SCANCODE_9] =              C5S,
    [SDL_SCANCODE_0] =              D5S,
    [SDL_SCANCODE_EQUALS] =         F5S,
};

#endif /* _KEYMAP_H */