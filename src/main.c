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

    main.c: Program entry point

*/

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "audio.h"
#include "gui.h"


int
main(int argc, char **argv)
{
    printf("arfsynth\nLicensed under GPLv3\n");

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--audio-drivers") == 0)
                audio_enum_drivers();
            else if (strcmp(argv[i], "--audio-devices") == 0) {
                if (i + 1 < argc) {
                    if (audio_enum_devices(argv[i + 1]) < 0) return 1;
                } else fprintf(stderr, "Too few arguments\n");
            }
        }
        return 0;
    }

    if (parse_config("../config.conf") < 0) return 1;
    if (audio_init() < 0) return 1;
    if (gui_init() < 0) return 1;

    gui_loop();

    gui_deinit();
    audio_deinit();
}
