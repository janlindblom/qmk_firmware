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

enum layers {
    BASE,    // default layer
    SYMB,    // symbols
    NUMB,    // numbers etc
    SYST,
    ADJUST,  // motion
};

enum tap_dances {
  TD_Q_ESC
};

#ifdef TAP_DANCE_ENABLE
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for ESC
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};
#endif

#define CK_ENT LT(SYMB, KC_ENT)
#define CK_SPC LT(NUMB, KC_SPC)
#define CK_BSPC LT(NUMB, KC_BSPC)
#define CK_TAB LT(SYMB, KC_TAB)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_Q TD(TD_Q_ESC)
#define CK_SYST MO(SYST)

// Homerow mods
#define CK_A LGUI_T(KC_A)
#define CK_S LALT_T(KC_S)
#define CK_D LCTL_T(KC_D)
#define CK_F LSFT_T(KC_F)
#define CK_J LSFT_T(KC_J)
#define CK_K LCTL_T(KC_K)
#define CK_L LALT_T(KC_L)
#define CK_QOUT LGUI_T(SE_QUOT)
#define CK_X ALGR_T(KC_X)
#define CK_DOT ALGR_T(SE_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x5_2(
    CK_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    CK_A,    CK_S,    CK_D,    CK_F,    KC_G,        KC_H,    CK_J,    CK_K,    CK_L,    CK_QOUT,
    KC_Z,    CK_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    SE_COMM, CK_DOT,  SE_MINS,
                               CK_BSPC, CK_ENT,    CK_SPC,  CK_TAB
    ),
    [SYMB] = LAYOUT_split_3x5_2(
    SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,     SE_PND,  SE_EURO, SE_QUES, SE_SECT, SE_CURR,
    SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,     SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC,
    SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD,     SE_AMPR, SE_EQL,  KC_COMM, SE_COLN, SE_BSLS,
                               CK_SYST, _______,     CK_SYST, _______
    ),
    [NUMB] = LAYOUT_split_3x5_2(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,    CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN,
                             _______, CK_SYST,    _______, CK_SYST
    ),
    [SYST] = LAYOUT_split_3x5_2(
    KC_ESC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MUTE,  KC_NO,
    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_BRIU,  KC_MPRV,  KC_MNXT,  KC_VOLU,  KC_NO,
    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_BRID,  KC_MSTP,  KC_MPLY,  KC_VOLD,  KC_NO,
                                  _______,  _______,    _______,  _______
    ),
    [ADJUST] = LAYOUT_split_3x5_2(
    KC_NO,  KC_NO,  KC_NO,  EH_RGHT,    KC_NO,             KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,             KC_NO,   KC_NO,   KC_NO,   EH_LEFT,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    RESET,             KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,
                            _______,  _______,           _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, SYMB, NUMB, ADJUST); }
