/**
This is the c configuration file for the keymap.

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2022 Jan Lindblom (@janlindblom)

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

//#define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

// #define COMBO_COUNT 3  // Enable if using combos.

#ifdef OLED_ENABLE
#    ifdef OLED_COUNT
#        undef OLED_COUNT
#    endif
#    define OLED_COUNT 2
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LAYERS

#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGB_DISABLE_TIMEOUT 600000 // number of milliseconds to wait until rgb automatically turns off
#    define RGBLIGHT_DEFAULT_HUE 106
#    define RGBLIGHT_SLEEP
#    undef RGBLED_NUM
#    define RGBLED_NUM 54 // Number of LEDs
#    undef DRIVER_LED_TOTAL
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT \
        { 27, 27 }
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 12
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_DEFAULT_SPD 10
#    ifndef RGBLIGHT_LAYERS
#        define RGBLIGHT_EFFECT_STATIC_GRADIENT
#        define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_GRADIENT
#        define RGBLIGHT_EFFECT_BREATHE_MAX 120
#    else
#        define RGBLIGHT_MAX_LAYERS 5
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_DISABLE_TIMEOUT 600000     // number of milliseconds to wait until rgb automatically turns off
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
#    undef RGBLED_NUM
#    define RGBLED_NUM 54 // Number of LEDs
#    undef DRIVER_LED_TOTAL
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT \
        { 27, 27 }

#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 12
#    define RGB_MATRIX_VAL_STEP 10
#    define RGB_MATRIX_SPD_STEP 10

#    define DISABLE_RGB_MATRIX_ALPHAS_MODS
// #    define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define DISABLE_RGB_MATRIX_BREATHING
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_VAL
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL

#    define DISABLE_RGB_MATRIX_CYCLE_ALL
#    define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define DISABLE_RGB_MATRIX_DUAL_BEACON
#    define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#    define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define DISABLE_RGB_MATRIX_RAINDROPS
#    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN

// #    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

#    define DISABLE_RGB_MATRIX_SPLASH
#    define DISABLE_RGB_MATRIX_MULTISPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
#    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_ANIMATION_SPEED_DEFAULT UINT8_MAX / 2
#    define RGB_MATRIX_ANIMATION_SPEED_SLOW RGB_MATRIX_ANIMATION_SPEED_DEFAULT / 4
#    define RGB_MATRIX_ANIMATION_SPEED_SLOWER RGB_MATRIX_ANIMATION_SPEED_SLOW / 3
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
