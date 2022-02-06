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

#undef DEBOUNCE
#define DEBOUNCE 8

// Tapping
#define PERMISSIVE_HOLD
#define TAPPING_TERM 200

#define LAYER_STATE_8BIT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
//#define COMBO_COUNT 3  // Enable if using combos.
// Unicode
#define UNICODE_CYCLE_PERSIST  false
#define UNICODE_SELECTED_MODES UC_MAC, UC_WINC, UC_WIN
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

#ifdef WPM_ENABLE
#    define SPLIT_WPM_ENABLE
//#    define SPLIT_LAYER_STATE_ENABLE
//#    define SPLIT_LED_STATE_ENABLE
//#    define SPLIT_MODS_ENABLE
#endif

#ifdef OLED_ENABLE
#    ifdef OLED_BRIGHTNESSS
#        undef OLED_BRIGHTNESS
#    endif
#    ifdef OLED_FONT_H
#        undef OLED_FONT_H
#    endif
#    define OLED_FADE_OUT
#    define OLED_FADE_OUT_INTERVAL 5
#    define SPLIT_OLED_ENABLE
#    define OLED_BRIGHTNESS 200
#    define OLED_FONT_H "glcdfont_lily_namnlos.c"
#endif

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 36
#    define MOUSEKEY_WHEEL_MAX_SPEED 4
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 100
#endif

/* key combination for command */
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
