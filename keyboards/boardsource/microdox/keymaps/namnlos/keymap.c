/*
Copyright 2022 Jan Lindblom <jan@namnlos.co>

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

#include QMK_KEYBOARD_H
#include "namnlos.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

extern userspace_config_t userspace_config;
#ifdef WPM_ENABLE
extern uint8_t current_wpm;
#endif // WPM_ENABLE

// Some defines for the keys below
#define CK_ESC LT(_SYMB, KC_ESC)
#ifdef EXTRA_FUNCTION_LAYER
#    define CK_DEL LT(_FUNC, KC_DEL)
#else
#    define CK_DEL MT(MOD_LGUI, KC_DEL)
#endif
#define CK_ENT2 LT(_SYMB, KC_ENT)
#define CK_SPC2 LT(_NUMB, KC_SPC)
#define CK_TAB LT(_LANG, KC_TAB)

#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_BSP1 LT(_LANG, KC_BSPC)

#define ADJUST MO(_ADJST)

#define CK_Z LSFT_T(KC_Z)
#define CK_MINS RSFT_T(SE_MINS)

#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L RALT_T(KC_L)
#define CK_QUOT RCTL_T(SE_QUOT)

#ifdef UNICODE_ENABLE
#    define CK_ENDASH UC(0x2013)
#    define CK_EMDASH UC(0x2014)
#else
#    define CK_ENDASH KC_TRNS
#    define CK_EMDASH KC_TRNS
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,
    CTL_A,   ALT_S,   GUI_D,   SFT_F,   KC_G,         KC_H,    SFT_J,  GUI_K,   ALT_L,   CK_QUOT,
    CK_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,   SE_COMM, SE_DOT,  CK_MINS,
                    CK_DEL, CK_BSP1, CK_ENT2,         CK_SPC2, CK_TAB, CK_ESC
  ),

  [_NUMB] = LAYOUT_split_3x5_3(
    KC_1 ,   KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,       KC_6  ,  KC_7  ,  KC_8   ,  KC_9  ,  KC_0,
    KC_F1,   KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,       KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_PGUP,
    KC_F6,   KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10,       CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN,
                      _______, _______, ADJUST,       _______, _______, _______
  ),

  [_SYMB] = LAYOUT_split_3x5_3(
    SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,      SE_PND,  SE_EURO, SE_QUES, SE_SECT, SE_CURR,
    SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,      SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC,
    SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD,      SE_AMPR, SE_EQL , SE_DQUO, SE_MICR, SE_BSLS,
                      SE_LABK, SE_RABK, _______,      ADJUST,  _______, _______
  ),
  [_ADJST] = LAYOUT_split_3x5_3(
    QK_MAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, CK_OBI,  CG_TOGG,      RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD,
    XXXXXXX, XXXXXXX, KC_CAPS, CK_OBD,  QK_BOOT,      NK_TOGG, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,
                      _______, _______, _______,      _______, _______, _______
  ),
  [_KICAD] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_ESC,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_A,    KC_L,    KC_D,    KC_M,    KC_G,         KC_QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      CK_DEL, CK_BSP1, CK_ENT2,       CK_SPC2,   CK_TAB, CK_ESC
  ),
  [_ADESK] = LAYOUT_split_3x5_3(
    KC_I,    KC_M,    KC_E,    KC_R,    KC_T,         KC_ESC,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_J,         KC_QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_P,    KC_X,    KC_C,    KC_V,    KC_B,         XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      CK_DEL, CK_BSP1, CK_ENT2,       CK_SPC2,   CK_TAB, CK_ESC
  ),
  [_LANG] = LAYOUT_split_3x5_3(
    _______, _______, SE_EURO, SE_GRV , SE_ACUT,         _______, _______, _______, _______, _______,
    SE_ADIA, _______, SE_DIAE, _______, _______,         _______, _______, _______, SE_ARNG, SE_ODIA,
    _______, SE_CIRC, _______, _______, _______,         _______, _______, _______, _______, _______,
                      _______, _______, _______,         _______, _______, _______
  ),
#ifdef EXTRA_FUNCTION_LAYER
  [_FUNC] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
    KC_LCTL, KC_LALT, KC_LGUI, KC_CAPS, XXXXXXX,      XXXXXXX, KC_CAPS, KC_RGUI, KC_LALT, KC_RCTL,
    CK_UNDO, CK_CUT,  CK_COPY, CK_PSTE, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, _______, _______,      _______, _______, _______
  ),
#endif
};
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    } else {
        return OLED_ROTATION_0;
    }
    return rotation;
}

void render_layer_name(uint8_t layer) {
    static const char PROGMEM layer_names[][9] = {
        // clang-format off
        [_LANG] = OLED_RENDER_LAYER_LANG,
        [_ADJST] = OLED_RENDER_LAYER_ADJUST,
        [_FUNC] = OLED_RENDER_LAYER_FUNC
        // clang-format on
    };
#    ifdef OLED_LAYER_COL
    OLED_PLACE_CURSOR_FULL(OLED_LAYER_LINE, OLED_LAYER_COL);
#    else
    OLED_PLACE_CURSOR(OLED_LAYER_LINE);
#    endif
    oled_write_P(layer_names[layer], false);
}

bool render_layer_state_keymap(void) {
    uint8_t top_layer = get_highest_layer(layer_state);
    switch (top_layer) {
        case _LANG:
        case _ADJST:
        case _FUNC:
            render_layer_name(top_layer);
            return false; // return false to prevent userspace level render_layer_state from running.
    }
    return true; // return true and let userspace level render_layer_state run.
}

#    ifdef RENDER_PET
bool render_pet_keymap(void) {
    uint_least8_t top_layer = get_highest_layer(default_layer_state);
    // Turn off the pet for these layers.
    switch (top_layer) {
        default:
            break;
    }
    return true; // Otherwise let userspace render_pet run.
}
#    endif // RENDER_PET

#    ifdef WPM_ENABLE
bool render_wpm_keymap(void) {
    uint_least8_t top_layer = get_highest_layer(layer_state);
    // Don't gather WPM for these layers or if we're blocking it for some reason.
    if (top_layer == _ADJST) {
        return false;
    }
    return true;
}
#    endif // WPM_ENABLE

bool oled_task_non_master_keymap(void) {
    static const char PROGMEM microdox_logo[] = {
        // clang-format off
        // 'MICRODOX', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xff, 0x01, 0xfd, 0x0d, 0x09, 0x91, 0x66, 0x88, 0x88, 0x66, 0x91, 0x09, 0x0d, 0xfd,
        0x01, 0xff, 0x00, 0x00, 0x1f, 0x11, 0x15, 0xf5, 0x05, 0xfd, 0x05, 0x05, 0xf5, 0x15, 0x11, 0x1f,
        0x00, 0xf8, 0x06, 0x02, 0xf9, 0x0d, 0xe5, 0x15, 0x15, 0x15, 0x15, 0x15, 0x11, 0x0f, 0x00, 0xff,
        0x01, 0x01, 0xfd, 0x05, 0x65, 0x95, 0x95, 0x65, 0x09, 0xf9, 0x02, 0xc6, 0x38, 0x00, 0x00, 0xf8,
        0x04, 0x02, 0xfa, 0x09, 0xe5, 0x15, 0x15, 0x15, 0xe5, 0x09, 0xfa, 0x02, 0x04, 0xf8, 0x00, 0xff,
        0x01, 0x01, 0xfd, 0x05, 0xf5, 0x15, 0x15, 0x15, 0xe5, 0x09, 0xf1, 0x02, 0x04, 0xf8, 0x00, 0xf8,
        0x04, 0x02, 0xfa, 0x09, 0xe5, 0x15, 0x15, 0x15, 0xe5, 0x09, 0xfa, 0x02, 0x04, 0xf8, 0x00, 0x1e,
        0x61, 0x81, 0x1d, 0x61, 0x81, 0x3e, 0x40, 0x3e, 0x81, 0x61, 0x1d, 0x81, 0x61, 0x1e, 0x00, 0x00,
        0x00, 0x00, 0xff, 0x00, 0x7f, 0x00, 0x00, 0xff, 0x02, 0x04, 0x04, 0x02, 0xff, 0x00, 0x00, 0x7f,
        0x00, 0xff, 0x00, 0x00, 0xf0, 0x10, 0x50, 0x5f, 0x40, 0x7f, 0x40, 0x40, 0x5f, 0x50, 0x10, 0xf0,
        0x00, 0x3f, 0xc0, 0x80, 0x3f, 0x60, 0x4f, 0x50, 0x50, 0x50, 0x50, 0x50, 0x10, 0xe0, 0x00, 0xff,
        0x00, 0x00, 0x7f, 0x02, 0xfa, 0x0a, 0x0a, 0x0a, 0xfb, 0x02, 0x02, 0x7c, 0x01, 0xfe, 0x00, 0x3f,
        0x40, 0x80, 0xbf, 0x20, 0x4f, 0x50, 0x50, 0x50, 0x4f, 0x20, 0xbf, 0x80, 0x40, 0x3f, 0x00, 0xff,
        0x00, 0x00, 0x7f, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x4f, 0x20, 0x1f, 0x80, 0x40, 0x3f, 0x00, 0x3f,
        0x40, 0x80, 0xbf, 0x20, 0x4f, 0x50, 0x50, 0x50, 0x4f, 0x20, 0xbf, 0x80, 0x40, 0x3f, 0x00, 0xf0,
        0x0c, 0x02, 0x71, 0x08, 0x06, 0xf1, 0x09, 0xf1, 0x06, 0x08, 0x71, 0x02, 0x0c, 0xf0, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00
        // clang-format on
    };
    oled_write_raw_P(microdox_logo, sizeof(microdox_logo));
    return false;
}
#endif // OLED_ENABLE
