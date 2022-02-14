/**
 * Copyright © 2022 Jan Lindblom (@janlindblom)
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

// Store left/right in EEPROM/Flash
#define EE_HANDS

// Right side is primary/host side
#define MASTER_RIGHT

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

#undef DEBOUNCE
#define DEBOUNCE 12

// #define COMBO_COUNT 3  // Enable if using combos.
#define UNICODE_SELECTED_MODES UC_WINC, UC_MAC, UC_LNX

#ifdef OLED_COUNT
#    undef OLED_COUNT
#endif
#define OLED_COUNT 2

/* We only use underglow and the per key LEDs have been bypassed by wiring past
   them.
*/
#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    undef RGBLED_SPLIT
#    define RGBLED_NUM 8
#    define RGBLED_SPLIT \
        { 4, 4 } // underglow only
#    ifdef RGBLIGHT_LAYERS
#        define RGBLIGHT_MAX_LAYERS 8
#    endif
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_SLEEP

#    undef RGBLIGHT_EFFECT_BREATHING
#    undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif

#ifdef RGB_MATRIX_ENABLE
#    undef RGB_MATRIX_ENABLE
/*
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#    undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_BREATHING
*/
#endif

#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
