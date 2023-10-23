/* Copyright © 2023 Jan Lindblom (@janlindblom)
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

#include QMK_KEYBOARD_H
#include "namnlos.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

// Tap Dance definitions
#ifdef TAP_DANCE_ENABLE
enum dances {
    TD_SHFT_CAPS,
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
#    define CK_LSFT TD(TD_SHFT_CAPS)
#else
#    define CK_LSFT KC_LSFT
#endif

// Some defines for the keys below
#define CK_ESC LT(_RAISE, KC_ESC)
#define CK_BSPC LCTL_T(KC_BSPC)
#define CK_ENT1 LT(_LOWER, KC_ENT)
#define CK_DEL LALT_T(KC_DEL)
#define CK_ENT2 LT(_RAISE, KC_ENT)
#define CK_TAB RALT_T(KC_TAB)
#define CK_ADIA RCTL_T(SE_ADIA)
#define CK_QUOT RSFT_T(SE_QUOT)
#define CK_SPC LGUI_T(KC_SPC)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)

#ifdef UNICODEMAP_ENABLE
enum unicode_names {
    NDASH,
    MDASH,
};

const uint32_t PROGMEM unicode_map[] = {
    [NDASH] = 0x2013,
    [MDASH] = 0x2014,
};
// Unicode keys
#    define K_NDASH X(NDASH)
#    define K_MDASH X(MDASH)
#elif UNICODE_ENABLE
#    define K_NDASH UC(0x2013)
#    define K_MDASH UC(0x2014)
#else
#    define K_NDASH KC_TRNS
#    define K_MDASH KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_BASE] = LAYOUT(
        CK_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  SE_ARNG,
        CK_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,  SE_ODIA,  CK_ADIA,
        CK_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,  SE_COMM,   SE_DOT,  SE_MINS,  CK_QUOT,
                                              CK_DEL,   CK_ENT1,  CK_SPC,   CK_ENT2,   CK_TAB
    ),

    [_LOWER] = LAYOUT(
    SK_NOT_EQL,  SE_EXLM,    SE_AT,  SE_LCBR,  SE_RCBR,   SE_PIPE,             SE_PND,  SE_EURO,  SE_QUES,  SE_SECT,  SE_CURR,  SE_DIAE,
        SK_LEQ,  SE_HASH,   SE_DLR,  SE_LPRN,  SE_RPRN,    SE_GRV,            SE_PLUS,  SE_MINS,  SE_SLSH,  SE_ASTR,  SE_PERC,  SE_DQUO,
        SK_GEQ,  SE_PERC,  SE_CIRC,  SE_LBRC,  SE_RBRC,   SE_TILD,            SE_AMPR,   SE_EQL,  SE_LABK,  SE_RABK,  SE_BSLS,  SE_ACUT,
                                               _______,   _______,  _______,  _______,  CK_DRGHT
    ),

    [_RAISE] = LAYOUT(
        SE_SECT,   SE_1,     SE_2,     SE_3,     SE_4,     SE_5,                 SE_6,    SE_7,    SE_8,    SE_9,    SE_0,  KC_MUTE,
        KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,              KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP,  KC_VOLU,
        KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,              CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN,  KC_VOLD,
                                                CK_DLEFT,  _______,  KC_ENT,  _______,  CK_DRGHT
    ),

    [_ADJST] = LAYOUT(
        XXXXXXX,   XXXXXXX, XXXXXXX,   BL_OFF,  BL_DOWN,   BL_TOGG,            BL_BRTG, BL_UP,   BL_ON,   XXXXXXX, XXXXXXX,  XXXXXXX,
        XXXXXXX,  CK_ADESK,CK_KICAD,  XXXXXXX,   SK_BLL, CK_GAMING,            NK_ON,   KO_ON,   AC_ON,   AS_ON,   XXXXXXX,  XXXXXXX,
        XXXXXXX,   UC_WINC,  UC_MAC,  UC_LINX,  XXXXXXX,   QK_BOOT,            NK_OFF,  KO_OFF,  AC_OFF,  AS_OFF,  XXXXXXX,  XXXXXXX,
                                                _______,   _______, _______,   _______,  _______
    ),
    // KiCAD top layer for single hand use.
    [_KICAD] = LAYOUT(
         KC_ESC,     KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,            KC_Y,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  CK_QWERTY,
        KC_LCTL,     KC_A,     KC_L,     KC_D,     KC_M,      KC_G,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                 CK_DEL,   CK_ENT1,  KC_SPC,   CK_ENT2,   CK_TAB
    ),
    // AutoDesk (Fusion 360) top layer for single hand use.
    [_ADESK] = LAYOUT(
         KC_ESC,      KC_I,    KC_M,     KC_E,     KC_R,      KC_T,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  CK_QWERTY,
        KC_LCTL,      KC_A,    KC_S,     KC_D,     KC_F,      KC_J,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_LSFT,      KC_P,    KC_X,     KC_C,     KC_V,      KC_B,            XXXXXXX,  KC_M,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                 CK_DEL,   CK_ENT1,  KC_SPC,   CK_ENT2,   CK_TAB
    ),
    [_GAMING] = LAYOUT(
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  SE_ARNG,
        KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,  SE_ODIA,  SE_ADIA,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,  SE_COMM,   SE_DOT,  SE_MINS,  CK_QUOT,
                                              KC_DEL,    KC_SPC,  CK_SPC,   CK_ENT1,  CK_QWERTY
    )
    // clang-format on
};

// Combos, if enabled
#ifdef COMBO_ENABLE
enum combo_events {
    ZC_COPY,
    XV_PASTE,
    ZX_CUT,
};

const uint16_t PROGMEM copy_combo[]  = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM cut_combo[]   = {KC_Z, KC_X, COMBO_END};

combo_t key_combos[] = {
    [ZC_COPY]  = COMBO_ACTION(copy_combo),
    [XV_PASTE] = COMBO_ACTION(paste_combo),
    [ZX_CUT]   = COMBO_ACTION(cut_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case ZC_COPY:
            if (pressed) {
                tap_code16(LCTL(KC_C));
            }
            break;
        case XV_PASTE:
            if (pressed) {
                tap_code16(LCTL(KC_V));
            }
            break;
        case ZX_CUT:
            if (pressed) {
                tap_code16(LCTL(KC_X));
            }
            break;
    }
}
#endif
