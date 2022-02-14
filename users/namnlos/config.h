/**
 * Copyright © 2022 Jan Lindblom (@janlindblom)
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

// Some stuff that I generally define
// #define DYNAMIC_KEYMAP_LAYER_COUNT 4 // to be defined on keymap level
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
#define ENABLE_COMPILE_KEYCODE
#define CRC8_OPTIMIZE_SPEED

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define KEYBOARD_SLEEP_TIMEOUT 120000u

/* If we enable mouse keys, we will end up with more than 8 layers,
   subsequently, if we don't need mousekeys we can save some space by switching
   to 8 bit layer state.
*/
#if defined(MOUSEKEY_ENABLE) || defined(EXTRA_FUNCTION_LAYER)
#    undef LAYER_STATE_8BIT
#    define LAYER_STATE_16BIT
#else
#    define LAYER_STATE_8BIT
#endif

#if defined(UNICODE_ENABLED) || defined(UNICODEMAP_ENABLED)
#    define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_LINUX, UNICODE_MODE_MACOS
#endif

#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

#ifdef SPLIT_KEYBOARD
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_LED_STATE_ENABLE
#    define SPLIT_MODS_ENABLE
#    ifdef WPM_ENABLE
#        define SPLIT_WPM_ENABLE
#    endif
#    ifdef OLED_ENABLE
#        define SPLIT_OLED_ENABLE
#    endif
#endif

#if defined(PROMICRO_LED_STATUS)
#    ifdef __AVR__
#        define LED_CAPS_LOCK_PIN D5 // Enable pin D5 as the Caps Lock pin
#        ifndef LED_PIN_ON_STATE
#            define LED_PIN_ON_STATE 0
#        endif
#    endif
#elif (defined(BACKLIGHT_LED_STATUS) && defined(BACKLIGHT_ENABLE))
#    define BACKLIGHT_CAPS_LOCK
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    ifdef RGBLIGHT_LAYERS
#        define RGBLIGHT_LAYERS_RETAIN_VAL
#    endif
#    ifdef SPLIT_KEYBOARD
#        define RGBLIGHT_SPLIT
#    endif
#endif

#ifdef OLED_ENABLE
#    ifndef OLED_COUNT
#        define OLED_COUNT 1
#    endif

#    ifndef OLED_BRIGHTNESS
#        define OLED_BRIGHTNESS 200u
#    endif

#    ifdef OLED_FONT_H
#        undef OLED_FONT_H
#    endif

#    define OLED_FONT_H "oled/oled_font.h"
#    define OLED_FONT_END 255

#    ifdef CUSTOM_OLED_SLEEP
#        ifndef OLED_DISABLE_TIMEOUT
#            define OLED_DISABLE_TIMEOUT
#        endif
#    else
#        ifndef OLED_TIMEOUT
#            define OLED_TIMEOUT 60000
#        endif
#    endif

#    ifdef OLED_DRIVER_SH1107
#        ifndef OLED_IC_SH1107
#            define OLED_IC_SH1107 2
#        endif
#        ifndef OLED_UPDATE_INTERVAL
#            define OLED_UPDATE_INTERVAL 75
#        endif
#        define OLED_DISPLAY_CUSTOM
#        ifndef OLED_IC_SH1107
#            define OLED_IC_SH1107 2
#        endif
#        ifndef OLED_DISPLAY_64X128
#            define OLED_DISPLAY_64X128
#        endif
#        ifdef OLED_IC
#            undef OLED_IC
#        endif
#        define OLED_IC OLED_IC_SH1107
#        ifndef OLED_DISPLAY_WIDTH
#            define OLED_DISPLAY_WIDTH 64
#        endif
#        ifndef OLED_DISPLAY_HEIGHT
#            define OLED_DISPLAY_HEIGHT 128
#        endif
#        ifndef OLED_MATRIX_SIZE
#            define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#        endif
#        ifndef OLED_BLOCK_TYPE
#            define OLED_BLOCK_TYPE uint16_t
#        endif
#        ifndef OLED_BLOCK_COUNT
#            define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#        endif
#        ifndef OLED_BLOCK_SIZE
#            define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#        endif
#        ifndef OLED_COM_PINS
#            define OLED_COM_PINS COM_PINS_ALT
#        endif
#        ifndef OLED_SOURCE_MAP
#            define OLED_SOURCE_MAP \
                { 0, 8, 16, 24, 32, 40, 48, 56 }
#        endif
#        ifndef OLED_TARGET_MAP
#            define OLED_TARGET_MAP \
                { 56, 48, 40, 32, 24, 16, 8, 0 }
#        endif
#    endif
#endif
