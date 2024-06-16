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

    config.c: Configuration parsing

*/

#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <confuse.h>

char *audio_driver = NULL;
char *audio_device = NULL;
long int samp_rate = 0;
long int block_size = 0;

int
parse_config(char *file)
{
    audio_driver = strdup("pulseaudio");
    audio_device = strdup("");
    long int samp_rate = 48000;
    long int block_size = 1024;

    cfg_opt_t opts[] = {
		CFG_SIMPLE_STR("audio_driver", &audio_driver),
		CFG_SIMPLE_STR("audio_device", &audio_device),
		CFG_SIMPLE_INT("samp_rate", &samp_rate),
		CFG_SIMPLE_INT("block_size", &block_size),
		CFG_END()
	};
	cfg_t *cfg;

    cfg = cfg_init(opts, 0);
    int ret = cfg_parse(cfg, file);
	if (ret == CFG_FILE_ERROR) {
        fprintf(stderr, "Error reading config: %s\n", strerror(errno));
        cfg_free(cfg);
        return -1;
    } else if (ret == CFG_PARSE_ERROR) {
        fprintf(stderr, "Error parsing config\n");
        cfg_free(cfg);
        return -1;
    }

    cfg_free(cfg);
    return 0;
}
