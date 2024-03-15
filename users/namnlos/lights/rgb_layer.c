/**
 * Copyright © 2023 Jan Lindblom (@janlindblom)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "rgb_layer.h"

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
const rgblight_segment_t PROGMEM base_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_CYAN});
const rgblight_segment_t PROGMEM symb_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_PURPLE});
const rgblight_segment_t PROGMEM num_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_TEAL});
const rgblight_segment_t PROGMEM move_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_BLUE});
const rgblight_segment_t PROGMEM adjust_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_PINK});
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});
#    ifdef RGBLIGHT_MODS
const rgblight_segment_t PROGMEM shift_layers[]   = RGBLIGHT_LAYER_SEGMENTS({6, 1, HSV_CYAN}, {13, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM control_layers[] = RGBLIGHT_LAYER_SEGMENTS({6, 1, HSV_RED}, {13, 1, HSV_RED});
const rgblight_segment_t PROGMEM alt_layers[]     = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_MAGENTA}, {9, 1, HSV_MAGENTA});
const rgblight_segment_t PROGMEM gui_layers[]     = RGBLIGHT_LAYER_SEGMENTS({6, 1, HSV_YELLOW}, {13, 1, HSV_YELLOW});
#    endif

const rgblight_segment_t *const PROGMEM namnlos_rgb_layers[] = RGBLIGHT_LAYERS_LIST(base_layer, symb_layer, num_layer, move_layer, adjust_layer, capslock_layer
#    ifdef RGBLIGHT_MODS
                                                                                    ,
                                                                                    shift_layers, control_layers, alt_layers, gui_layers
#    endif // RGBLIGHT_MODS
);
#endif // RGBLIGHT_ENABLE && RGBLIGHT_LAYERS
