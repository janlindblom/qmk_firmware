/*
 * Copyright 2022 Jan Lindblom (@janlindblom)
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
    BASE,    // default layer
    SYMB,    // symbols
    NUMB,    // numbers etc
    SYST,    // system
    LANG,    // language
    ADJUST,
};

enum tap_dances {
  TD_Q_ESC
};

enum keycodes {
    CK_EACT = SAFE_RANGE,
};

#ifdef TAP_DANCE_ENABLE
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for ESC
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(SE_Q, KC_ESC)};
#    define CK_Q TD(TD_Q_ESC)
#else
#    define CK_Q SE_Q
#endif

// Layer toggles
#define CK_ENT LT(SYMB, KC_ENT)
#define CK_SPC LT(NUMB, KC_SPC)
#define CK_BSPC LT(NUMB, KC_BSPC)
#define CK_TAB LT(SYMB, KC_TAB)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)

// Secondary layers
#define CK_SYST MO(SYST)
#define CK_LANG MO(LANG)

// Homerow mods
#define CK_A LGUI_T(KC_A)
#define CK_S LALT_T(KC_S)
#define CK_D LCTL_T(KC_D)
#define CK_F LSFT_T(KC_F)

#define CK_J RSFT_T(KC_J)
#define CK_K RCTL_T(KC_K)
#define CK_L RALT_T(KC_L)
#define CK_LABK RGUI_T(SE_LABK)

#define CK_X ALGR_T(KC_X)
#define CK_DOT ALGR_T(SE_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x5_2(
//  Q        W        E        R        T            Y        U        I        O        P
    CK_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
//  A        S        D        F        G            H        J        K        L        <
    CK_A,    CK_S,    CK_D,    CK_F,    KC_G,        KC_H,    CK_J,    CK_K,    CK_L,    CK_LABK,
//  Z        X        C        V        B            N        M        ,        .        -
    KC_Z,    CK_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    SE_COMM, CK_DOT,  SE_MINS,
                             CK_BSPC, CK_ENT,    CK_SPC,  CK_TAB
    ),
    [SYMB] = LAYOUT_split_3x5_2(
/*  \!          @      {        }        |            £        €        ?        §        ¤       */
    SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,     SE_PND,  SE_EURO, SE_QUES, SE_SECT, SE_CURR,
//  #         $       (        )        '            +        -        /        *        %
    SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN, SE_QUOT,     SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC,
/*  %        ^        [        ]        "            &        =        ;        :        \\       */
    SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_DQUO,     SE_AMPR, SE_EQL,  SE_SCLN, SE_COLN, SE_BSLS,
                               CK_SYST, CK_LANG,     CK_SYST, CK_LANG
    ),
    [NUMB] = LAYOUT_split_3x5_2(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,    CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN,
                             CK_LANG, CK_SYST,    CK_LANG, CK_SYST
    ),
    [SYST] = LAYOUT_split_3x5_2(
    KC_ESC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MUTE,  KC_NO,
    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_BRIU,  KC_MPRV,  KC_MNXT,  KC_VOLU,  KC_NO,
    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_BRID,  KC_MSTP,  KC_MPLY,  KC_VOLD,  KC_NO,
                         _______,  _______,    _______,  _______
    ),
    [LANG] = LAYOUT_split_3x5_2(
//  Ä         Å         É        `          `
    SE_ADIA,  SE_ARNG,  CK_EACT,  SE_GRV,   SE_ACUT,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,
//                      ¨                                                                   Ö
    KC_NO,    KC_NO,    SE_DIAE,  KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,  KC_NO,  SE_ODIA,
//            ^                                                                             ~
    KC_NO,    SE_CIRC,  KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,  KC_NO,  SE_TILD,
                                  _______,  KC_ALGR,    _______,  KC_ALGR
    ),
    [ADJUST] = LAYOUT_split_3x5_2(
    KC_NO,  KC_NO,  KC_NO,  EH_RGHT,    KC_NO,             KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,             KC_NO,   KC_NO,   KC_NO,   EH_LEFT,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    RESET,             KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,
                            _______,  _______,           _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, SYMB, NUMB, ADJUST); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_EACT:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_EQL) "e");
        }
        break;
    }
    return true;
};
