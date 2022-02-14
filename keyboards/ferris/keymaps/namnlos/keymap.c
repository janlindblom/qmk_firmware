/*
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

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum layers {
    _BASE = 0,// default layer
    _SYMB,    // symbols
    _NUMB,    // numbers etc
    _SYST,    // system
    _LANG,    // language
    _ADJUST,
};

enum tap_dances {
  TD_Q_ESC
};

enum keycodes {
    CK_EACT = SAFE_RANGE,
    SK_NOT_EQL,
    SK_LEQ,
    SK_GEQ,
};

#ifdef TAP_DANCE_ENABLE
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for ESC
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)};
#    define CK_Q TD(TD_Q_ESC)
#else
#    define CK_Q SE_Q
#endif

#ifdef UNICODE_ENABLE
#    define CK_ENDASH UC(0x2013)
#    define CK_EMDASH UC(0x2014)
#else
#    define CK_ENDASH KC_TRNS
#    define CK_EMDASH KC_TRNS
#endif

#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)

// Layer toggles
#define CK_ENT LT(_SYMB, KC_ENT)
#define CK_SPC LT(_NUMB, KC_SPC)
#define CK_BSPC LT(_SYST, KC_BSPC)
#define CK_TAB LT(_LANG, KC_TAB)

// Homerow mods
#define CK_A LGUI_T(KC_A)
#define CK_S LALT_T(KC_S)
#define CK_D LCTL_T(KC_D)
#define CK_F LSFT_T(KC_F)

#define CK_J RSFT_T(KC_J)
#define CK_K RCTL_T(KC_K)
#define CK_L RALT_T(KC_L)
#define CK_ODIA RGUI_T(SE_ODIA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    CK_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    CK_A,    CK_S,    CK_D,    CK_F,    KC_G,        KC_H,    CK_J,    CK_K,    CK_L,    CK_ODIA,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_MINS,
                             CK_BSPC, CK_ENT,      CK_SPC,  CK_TAB
    ),
    [_SYMB] = LAYOUT(
/*  \!          @      {        }        |            £        €        ?        §        ¤       */
    SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,     SE_PND,  SE_EURO, SE_QUES, SE_SECT, SE_CURR,
//  #         $       (        )        '            +        -        /        *        %
    SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN, SE_QUOT,     SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC,
/*  %        ^        [        ]        "            &        =        ;        :        \\       */
    SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_DQUO,     SE_AMPR, SE_EQL,  SE_SCLN, SE_COLN, SE_BSLS,
                               _______, _______,     SE_LABK, SE_RABK
    ),
    [_NUMB] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,    CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN,
                             _______, _______,    _______, _______
    ),
    [_SYST] = LAYOUT(
    KC_ESC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MUTE,  KC_NO,
    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_BRIU,  KC_MPRV,  KC_MNXT,  KC_VOLU,  KC_NO,
    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_BRID,  KC_MSTP,  KC_MPLY,  KC_VOLD,  KC_NO,
                           _______,  KC_ENT,   KC_SPC,   KC_DEL
    ),
    [_LANG] = LAYOUT(
//  Ä         Å         É        `          ´           Y         U         I         O         P
    SE_ADIA,  SE_ARNG,  CK_EACT,   SE_GRV,  SE_ACUT,    _______,  _______,  _______,  _______,  _______,
//  A         S         ¨         F         G           H         J         K         L         Ö
    KC_A,     KC_S,     SE_DIAE,  KC_F,     KC_G,       KC_H,     KC_J,     KC_K,     KC_L,     SE_ODIA,
//  Z         ^         C         V         B           N         M         ,         .         ~
    _______,  SE_CIRC,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  SE_TILD,
                                  KC_ALGR,  _______,    _______,  _______
    ),
    [_ADJUST] = LAYOUT(
    KC_NO,  KC_NO,  KC_NO,  EH_RGHT,    KC_NO,             KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,             KC_NO,   KC_NO,   KC_NO,   EH_LEFT,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    RESET,             KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,
                            _______,  _______,           _______, _______
    )
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    setPinOutput(D5);
    setPinOutput(B0);
    switch (get_highest_layer(state)) {
        case _SYMB:
            writePinLow(D5); // Light up LED at B0
            break;
        case _NUMB:
            writePinLow(B0); // Light up LED at D5
            break;
        default: //  for any other layers, or the default layer
            // Turn both LEDs off.
            writePinHigh(B0);
            writePinHigh(D5);
            break;
    }

    return update_tri_layer_state(state, _SYMB, _NUMB, _ADJUST);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_EACT:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_EQL) "e");
        }
        break;
    case SK_NOT_EQL:
            if (record->event.pressed) {
                SEND_STRING("!=");
            }
            break;
        case SK_LEQ:
            if (record->event.pressed) {
                SEND_STRING("<=");
            }
            break;
        case SK_GEQ:
            if (record->event.pressed) {
                SEND_STRING(">=");
            }
            break;
    }
    return true;
};
