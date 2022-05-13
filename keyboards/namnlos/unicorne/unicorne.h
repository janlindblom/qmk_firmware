/*
Copyright 2022 Jan Lindblom, Namnlos Custom Keyboards (@janlindblom)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define UNUSED_PINS

// clang-format off

#define LAYOUT_unicorne( \
    K00, K01, K02, K03, K04,      K22, K21, K20, K19, K18, \
    K05, K06, K07, K08, K09,      K27, K26, K25, K24, K23, \
    K10, K11, K12, K13, K14,      K32, K31, K30, K29, K28, \
              K15, K16, K17,      K35, K34, K33 \
) \
{ \
    {   K00,   K01, K02, K03, K04,     K22,   K21, K20, K19, K18 }, \
    {   K05,   K06, K07, K08, K09,     K27,   K26, K25, K24, K23 }, \
    {   K10,   K11, K12, K13, K14,     K32,   K31, K30, K29, K28 }, \
    { KC_NO, KC_NO, K15, K16, K17,   KC_NO, KC_NO, K35, K34, K33 } \
}
// clang-format on

#define LAYOUT LAYOUT_unicorne
