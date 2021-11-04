/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2021 Jan Lindblom <jan@namnlos.io>

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

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#define LAYER_STATE_8BIT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
//#define COMBO_COUNT 3  // Enable if using combos.
#define UNICODE_SELECTED_MODES UC_WINC
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 27
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif

// Underglow
/*
#ifdef RGBLIGHT_ENABLE
#undef RGBLED_NUM
#define RGBLED_NUM 14    // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#endif
*/

#ifdef OLED_ENABLE
#    undef OLED_BRIGHTNESS
#    define OLED_BRIGHTNESS 128
#endif

#ifdef COMMAND_ENABLE
#    define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
#endif
