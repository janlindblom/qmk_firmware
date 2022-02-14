/* Copyright 2021 Jan Lindblom <jan@namnlos.co>
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

#if defined(CONVERT_TO_KB2040) || defined(CONVERT_TO_PROMICRO_RP2040) || defined(CONVERT_TO_BLOK) || defined(CONVERT_TO_RP2040_CE) || defined(CONVERT_TO_ELITE_PI)
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#    ifdef CONVERT_TO_KB2040
#        define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED 25U // Built in LED on KB2040
#    endif
#endif

// Store left/right in EEPROM/Flash
#define EE_HANDS

// Right side is primary/host side
// #define MASTER_RIGHT

#undef DEBOUNCE
#define DEBOUNCE 15

#ifndef OLED_TIMEOUT
#    define OLED_TIMEOUT 60000
#endif

#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 7

#ifndef OLED_ENABLE
#    define OLED_ENABLE
#endif

#ifdef OLED_DISABLE_TIMEOUT
#    undef OLED_DISABLE_TIMEOUT
#endif

#ifndef OLED_TIMEOUT
#    define OLED_TIMEOUT 60000
#endif

#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 7

#ifdef OLED_COUNT
#    undef OLED_COUNT
#endif
#define OLED_COUNT 2

// Windows Unicode support
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_MACOS, UNICODE_MODE_LINUX

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    if defined(CONVERT_TO_KB2040) || defined(CONVERT_TO_PROMICRO_RP2040) || defined(CONVERT_TO_BLOK) || defined(CONVERT_TO_RP2040_CE) || defined(CONVERT_TO_ELITE_PI)
#        define RGBLIGHT_EFFECT_RAINBOW_MOOD
#        define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#        define RGBLIGHT_EFFECT_SNAKE
#        define RGBLIGHT_EFFECT_KNIGHT
#        define RGBLIGHT_EFFECT_CHRISTMAS
#        define RGBLIGHT_EFFECT_STATIC_GRADIENT
#        define RGBLIGHT_EFFECT_ALTERNATING
#        define RGBLIGHT_EFFECT_TWINKLE
#    endif
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL 150
#    endif
#    define RGBLIGHT_SPLIT
#endif

/* RGB matrix support */
#ifdef RGB_MATRIX_ENABLE
#    undef DRIVER_LED_TOTAL
#    define DRIVER_LED_TOTAL RGBLED_NUM // Number of LEDs
#    undef RGB_MATRIX_SPLIT
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#endif
