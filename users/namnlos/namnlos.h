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
#pragma once

#ifndef NAMNLOS
#    define NAMNLOS
#endif

#include "quantum.h"
#include "extensions/tap_dance.h"
#include "control/control_idle.h"

#ifdef PROMICRO_LED_STATUS
#    include "lights/status_leds.h"
#endif

#ifdef OLED_ENABLE
#    include "oled/icons.h"
#    include "oled/oled_control.h"
#    include "oled/oled_wpm.h"
#    include "oled/oled_pet.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
#    include "lights/rgb_layer.h"
#endif

enum layers {
    _BASE = 0, // default layer
#ifdef MOUSEKEY_ENABLE
    _MOUSE,
    _LANG,
#else
    _LANG,
#endif
    _SVRK = _LANG,
    _KICAD,  // KiCad base layer
    _ADESK,  // Fusion360 base layer
    _GAMING, // Gaming base layer
    _SYST = _GAMING,
#ifdef EXTRA_FUNCTION_LAYER
    _FUNC,
#endif
    _SYMB, // symbols
    _LOWER = _SYMB,
    _NUMB, // numbers etc
    _RAISE = _NUMB,
    _ADJST, // Adjustments and system
};

#if defined(OS_DETECTION_ENABLE)
#    define LCG(kc) (QK_LCTL | QK_LGUI | (kc))
#endif

//// Combined keys
#define CK_UNDO LCTL(KC_Z)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)

//// Layer keys
#define CK_BASE DF(_BASE)
#define CK_QWERTY CK_BASE     // "Reset", set BASE layer as default
#define CK_KICAD DF(_KICAD)   // KiCad layer switch
#define CK_ADESK DF(_ADESK)   // Autodesk layer switch
#define CK_GAMING DF(_GAMING) // Minecraft layer switch
#define CK_SVORAK DF(_SVRK)   // SVORAK layer switch

// Custom keycodes.
enum custom_keycodes {
    SK_NOT_EQL = SAFE_RANGE,
    SK_LEQ,
    SK_GEQ,

    CK_OBI, // OLED Brightness Increase
    CK_OBD, // OLED Brightness Decrease
#ifdef BACKLIGHT_ENABLE
    CK_BACKLIGHT_LEVEL_REPORT,
    SK_BLL = CK_BACKLIGHT_LEVEL_REPORT,
#endif
    CK_DLEFT,
    CK_DRGHT,
};

void SET_DEFAULT_LAYER(uint8_t layer);
typedef union {
    uint32_t raw;
    struct {
        bool    gaming_mode : 1;
        uint8_t oled_brightness : 8;
    };
} userspace_config_t;
extern userspace_config_t userspace_config;

void matrix_init_keymap(void);
void matrix_init_user(void);
void keyboard_pre_init_keymap(void);
void keyboard_pre_init_user(void);
void eeconfig_init_keymap(void);
void eeconfig_init_user(void);
bool shutdown_keymap(bool jump_to_bootloader);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
bool led_update_keymap(led_t led_state);
bool led_update_user(led_t led_state);

#ifdef OLED_ENABLE
void            OLED_PLACE_CURSOR_FULL(uint8_t row, uint8_t col);
void            OLED_PLACE_CURSOR(uint8_t row);
void            OLED_CLEAR_LINE(void);
bool            oled_task_keymap(void);
bool            oled_task_user(void);
bool            render_layer_state_keymap(void);
void            render_layer_state_user(void);
void            render_keylock_status(void);
void            render_mod_status(uint8_t modifiers);
oled_rotation_t oled_init_keymap(oled_rotation_t rotation);
oled_rotation_t oled_init_user(oled_rotation_t rotation);

#    define OLED_SPACE " "
#    define OLED_NEWLINE "\n"

#    ifdef OLED_VERBOSE
#        define OLED_EMPTY_LINE "          "
#        define OLED_LABEL_WPM "WPM: "
#        define OLED_LABEL_MODS "Mods "

#        if defined(OLED_DISPLAY_128X128) || defined(OLED_DISPLAY_128X64) || defined(OLED_DISPLAY_64X128) || (OLED_DISPLAY_WIDTH > 32)
#            define OLED_LABEL_LOCKS "Locks:"
#            define OLED_LABEL_LAYER "Layer:"
#        else
#            define OLED_LABEL_LOCKS "Locks"
#            define OLED_LABEL_LAYER "Layer"
#        endif // OLED_DISPLAY_128X128 || OLED_DISPLAY_128X64 || OLED_DISPLAY_64X128
#    else
#        define OLED_EMPTY_LINE "     "
#    endif // OLED_VERBOSE
#    define OLED_LABEL_WPM "\x10 "
#    if defined(OLED_DISPLAY_128X128) || defined(OLED_DISPLAY_128X64) || defined(OLED_DISPLAY_64X128)
#        define OLED_RENDER_LAYOUT_QWERTY "QWERTY"
#        define OLED_RENDER_LAYOUT_ADESK "Fusion360"
#        define OLED_RENDER_LAYOUT_KICAD "KiCad"
#        define OLED_RENDER_LAYOUT_GAMING "Gaming"
#        define OLED_RENDER_LAYOUT_SVORAK "Svorak"
#        define OLED_RENDER_LAYER_LOWER "Lower"
#        define OLED_RENDER_LAYER_SYMB "Symbols"
#        define OLED_RENDER_LAYER_NUMB "Numbers"
#        define OLED_RENDER_LAYER_RAISE "Raise"
#        define OLED_RENDER_LAYER_ADJUST "Adjust"
#        define OLED_RENDER_LAYER_MOUSE "Mouse"
#        define OLED_RENDER_LAYER_LANG "Language"
#        define OLED_RENDER_LAYER_FUNC "Functions"
#        define OLED_RENDER_LAYER_UNDEFINED "Undefined"
#        define OLED_RENDER_LAYER_NAME_LENGTH 10
#        if defined(OLED_DISPLAY_64X128) && defined(OLED_VERTICAL)
#            define PET_LINE 0
#            define OLED_LAYER_LINE 0
#            define OLED_LAYER_COL 2
#            define OLED_MODS_LINE 1
#            define OLED_KEYLOCK_LINE 2
#            define OLED_WPM_LINE 4
#            define OLED_STATUS_LINE 5
#            define OLED_MAGIC_LINE 3
#        elif defined(OLED_DISPLAY_128X128) || defined(OLED_DISPLAY_128X64)
#            define PET_LINE 0
#            define OLED_LAYER_LINE 0
#            define OLED_LAYER_COL 1
#            define OLED_MODS_LINE 2
#            define OLED_MODS_COL 1
#            define OLED_KEYLOCK_LINE 4
#            define OLED_KEYLOCK_COL 1
#            define OLED_WPM_LINE 7
#            define OLED_WPM_COL 1
#            define OLED_STATUS_LINE 7
#            define OLED_STATUS_COL 1
#            define OLED_MAGIC_LINE 6
#            define OLED_MAGIC_COL 16
#        else
#            define OLED_LAYER_LINE 0
#            define OLED_LAYER_COL 1
#            define OLED_MODS_LINE 2
#            define OLED_MODS_COL 1
#            define OLED_KEYLOCK_LINE 4
#            define OLED_KEYLOCK_COL 1
#            define OLED_WPM_LINE 6
#            define OLED_WPM_COL 1
#            define OLED_STATUS_LINE 5
#            define OLED_STATUS_COL 1
#            define OLED_MAGIC_LINE 2
#            define OLED_MAGIC_COL 13
#            define PET_LINE 1
#        endif
#    else // This is a limited width display (like a 32x128 OLED)
#        define OLED_RENDER_LAYOUT_QWERTY "QWRTY"
#        define OLED_RENDER_LAYOUT_ADESK "Fusio"
#        define OLED_RENDER_LAYOUT_KICAD "KiCad"
#        define OLED_RENDER_LAYOUT_GAMING "Game "
#        define OLED_RENDER_LAYOUT_SVORAK "SVRAK"
#        define OLED_RENDER_LAYER_LOWER "Lower"
#        define OLED_RENDER_LAYER_SYMB "Symb "
#        define OLED_RENDER_LAYER_NUMB "Numb "
#        define OLED_RENDER_LAYER_RAISE "Raise"
#        define OLED_RENDER_LAYER_ADJUST "Adjst"
#        define OLED_RENDER_LAYER_MOUSE "Mouse"
#        define OLED_RENDER_LAYER_LANG "Lang "
#        define OLED_RENDER_LAYER_FUNC "Func "
#        define OLED_RENDER_LAYER_UNDEFINED "Undef"
#        define OLED_RENDER_LAYER_NAME_LENGTH 6
#        ifdef OLED_EMPTY_LINE
#            undef OLED_EMPTY_LINE
#        endif
#        define OLED_EMPTY_LINE "     "
#        define PET_LINE 0
#        define OLED_LAYER_LINE 0
#        define OLED_MODS_LINE 3
#        define OLED_KEYLOCK_LINE 6
#        define OLED_WPM_LINE 9
#        define OLED_STATUS_LINE 9
#        define OLED_MAGIC_LINE 10
#    endif
#endif // OLED_ENABLE

#ifdef __AVR__
#    define CAPS_WORD_LED_PIN B0
#    //define CAPS_LOCK_LED_PIN B0
#endif
