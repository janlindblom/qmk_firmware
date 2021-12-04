/*
Copyright 2021 TweetyDaBird

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

#include "config_common.h"

#define TAPPING_FORCE_HOLD

#define LAYER_STATE_8BIT
//#define COMBO_COUNT 3  // Enable if using combos.
#define UNICODE_SELECTED_MODES UC_WINC
#define IGNORE_MOD_TAP_INTERRUPT


#ifdef OLED_ENABLE
#    undef OLED_BRIGHTNESS
#    define OLED_BRIGHTNESS 128
#endif

#ifdef COMMAND_ENABLE
#    define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
#endif
