/* Copyright 2021 Sam Mohr <sam@mohr.codes>
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
#include "quantum.h"

enum layers {
    _MAIN = 0,
    _SYM_LMOD,
    _NUM_RMOD,
    _NAV,
    _FN
};

// layer controls
#define LMOD    OSL(_SYM_LMOD)
#define RMOD    OSL(_NUM_RMOD)
#define SPC_NAV LT(_NAV, KC_SPC)
#define L_FN    LT(_FN, KC_L)

// one-shot mods
#define LSFT_ OSM(MOD_LSFT)
#define RSFT_ OSM(MOD_RSFT)
#define LALT_ OSM(MOD_LALT)
#define RALT_ OSM(MOD_RALT)
#define LCTL_ OSM(MOD_LCTL)
#define RCTL_ OSM(MOD_RCTL)
#define LGUI_ OSM(MOD_LGUI)
#define RGUI_ OSM(MOD_RGUI)
#define RSG_  OSM(MOD_RSFT | MOD_RGUI)
#define RAG_  OSM(MOD_RALT | MOD_RGUI)
#define RCA_  OSM(MOD_RCTL | MOD_RALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
                    KC_F, KC_M, KC_P, KC_V,         KC_SCLN,  KC_DOT, KC_SLSH, S(KC_QUOT),
        KC_Z, KC_R, KC_S, KC_N, KC_T, KC_B,         KC_COMM,  KC_A,   KC_E,    KC_C,       KC_I, KC_QUOT,
              KC_X, KC_G, KC_H, KC_D, KC_K,         KC_MINUS, KC_U,   KC_O,    KC_W,       KC_Y,
                                LMOD, SPC_NAV,      L_FN,     RMOD
    ),

    [_SYM_LMOD] = LAYOUT(
                            C(S(KC_TAB)), C(KC_TAB), KC_CAPS, KC_NO,        S(KC_GRV),  S(KC_LBRC), S(KC_RBRC), S(KC_3),
        KC_NO, A(KC_LEFT),  LALT_,        LCTL_,     LSFT_,   KC_PSCR,      S(KC_COMM), S(KC_9),    S(KC_0),    S(KC_DOT), KC_BSLS, S(KC_1),
               A(KC_RIGHT), C(KC_W),      C(KC_Q),   LGUI_,   KC_NO,        KC_GRAVE,   KC_LBRC,    KC_RBRC,    S(KC_2),   S(KC_5),
                                                     KC_NO,   KC_NO,        KC_BSPC,    KC_ENTER
    ),

    [_NUM_RMOD] = LAYOUT(
                             KC_7,  KC_8,  KC_9,   S(KC_8),        KC_NO, KC_CAPS, KC_NO, KC_NO,
        S(KC_SLSH), S(KC_4), KC_1,  KC_2,  KC_3,   KC_EQL,         KC_NO, RSFT_,   RCTL_, RALT_,   KC_NO, KC_NO,
                    S(KC_6), KC_4,  KC_5,  KC_6,   S(KC_EQL),      KC_NO, RGUI_,   RSG_,  C(KC_C), KC_NO,
                                           KC_DOT, KC_0,           KC_NO, KC_NO
    ),

    [_NAV] = LAYOUT(
                          KC_VOLD, KC_VOLU, KC_MNXT,  KC_MUTE,      RALT_,  G(KC_D),     G(S(KC_D)), G(KC_Q),
        KC_MPRV, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MPLY,      RAG_,   G(KC_LEFT),  G(KC_DOWN), G(KC_UP), G(KC_RIGHT), KC_NO,
                 KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_MSTP,      RCTL_,  G(KC_ENTER), G(KC_O),    G(KC_N),  RCA_,
                                            KC_NO,    KC_NO,        KC_DEL, RSFT_
    ),

    [_FN] = LAYOUT(
                      KC_F7, KC_F8, KC_F9, KC_F10,      KC_NO, KC_BRID, KC_BRIU, KC_NO,
        KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F11,      KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,
               KC_NO, KC_F4, KC_F5, KC_F6, KC_F12,      KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,
                                    KC_NO, KC_NO,       KC_NO, KC_NO
    ),
};

enum combos {
    MV_J,
    MP_Q,
    GL_ESCAPE,
    LD_TAB,
};

const uint16_t PROGMEM j_combo[] = {KC_M, KC_V, COMBO_END};
const uint16_t PROGMEM q_combo[] = {KC_M, KC_P, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_H, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [MV_J]       = COMBO(j_combo, KC_J),
    [MP_Q]       = COMBO(q_combo, KC_Q),
    [GL_ESCAPE]  = COMBO(escape_combo, KC_ESC),
    [LD_TAB]     = COMBO(tab_combo, KC_TAB),
};

const key_override_t ampersand_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_7));
const key_override_t pipe_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, S(KC_BSLS));

const key_override_t **key_overrides = (const key_override_t *[]){
    &ampersand_override,
    &pipe_override,
    NULL
};
