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

#ifndef _SOURCES_H
#define _SOURCES_H

#define PI          3.1415926535897932384626

typedef struct {
    enum { SOURCE_SINE } type;
    float ff, a, p;
} vco_t;

typedef struct vcolist_node_s {
    vco_t data;
    struct vcolist_node_s *next; 
} vcolist_node_t;

float vco_sample(float t, float f, vco_t *vco);

#endif /* _SOURCES_H */
