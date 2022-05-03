/*
 * Copyright 2022 Jan Lindblom (@janlindblom)
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
#pragma once

#undef DEBOUNCE
#define DEBOUNCE 12

#define LAYER_STATE_8BIT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
//#define COMBO_COUNT 3  // Enable if using combos.
#define UNICODE_SELECTED_MODES UC_WINC, UC_MAC, UC_LNX

#undef OLED_BRIGHTNESS
#define OLED_BRIGHTNESS 80
//#define OLED_DISPLAY_64X128
#ifdef OLED_FADE_OUT
#    undef OLED_FADE_OUT
#endif

#define RENDER_KITTY
