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

    sources.c: Audio sources

*/

#include "sources.h"

#include <math.h>

double
source_sample(double t, source_t *source)
{
    switch (source->type) {
        case SOURCE_SINE: {
            return source->a * sin((2.0f * PI * source->f * t) + source->p);
        } break;
    }
}
