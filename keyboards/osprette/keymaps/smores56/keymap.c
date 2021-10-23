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
#define FN      OSL(_FN)
#define SPC_NAV LT(_NAV, KC_SPC)

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
                     KC_P,  KC_L,  KC_C, KC_F,         KC_SLSH,  KC_DOT, KC_QUOT, KC_SCLN,
        KC_V, KC_R,  KC_N,  KC_T,  KC_S, KC_D,         KC_COMM,  KC_A,   KC_E,    KC_I,    KC_H, KC_Q,
              KC_Z,  KC_B,  KC_M,  KC_G, KC_W,         KC_MINUS, KC_U,   KC_O,    KC_Y,    KC_K,
                                   LMOD, SPC_NAV,      RSFT_,    RMOD
    ),

    [_SYM_LMOD] = LAYOUT(
                        KC_NO,   C(S(KC_TAB)), C(KC_TAB),  KC_NO,            S(KC_LBRC), KC_DEL,   S(KC_RBRC), S(KC_GRV),
        KC_CAPS, LSFT_, LALT_,   LCTL_,        LGUI_,      KC_PSCR,          S(KC_9),    KC_BSPC,  S(KC_0),    S(KC_COMM), S(KC_3), S(KC_2),
                 KC_NO, C(KC_W), C(KC_Q),      A(KC_LEFT), A(KC_RIGHT),      KC_LBRC,    KC_ENTER, KC_RBRC,    S(KC_DOT),  KC_BSLS,
                                               KC_NO,      KC_NO,            KC_TRNS,    FN
    ),

    [_NUM_RMOD] = LAYOUT(
                             KC_7,  KC_8,  KC_9,   S(KC_8),        KC_NO, RSG_,    KC_NO,   KC_NO,
        S(KC_BSLS), S(KC_7), KC_1,  KC_2,  KC_3,   KC_EQL,         KC_NO, RGUI_,   RCTL_,   RALT_,   RSFT_, KC_NO,
                    S(KC_4), KC_4,  KC_5,  KC_6,   S(KC_EQL),      KC_NO, C(KC_C), C(KC_D), C(KC_V), KC_NO,
                                           KC_DOT, KC_0,           KC_NO, KC_NO
    ),

    [_NAV] = LAYOUT(
                          KC_VOLD, KC_VOLU, KC_MNXT,  KC_MUTE,      RALT_,   G(KC_D),     G(S(KC_D)), G(KC_Q),
        KC_MPRV, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MPLY,      RAG_,    G(KC_LEFT),  G(KC_DOWN), G(KC_UP), G(KC_RIGHT), KC_NO,
                 KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_MSTP,      RCTL_,   G(KC_ENTER), G(KC_O),    G(KC_N),  KC_NO,
                                            KC_NO,    KC_NO,        KC_TRNS, RCA_
    ),

    [_FN] = LAYOUT(
                      KC_F7, KC_F8, KC_F9, KC_F10,      KC_NO,   KC_BRID, KC_BRIU, KC_NO,
        KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F11,      KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,
               KC_NO, KC_F4, KC_F5, KC_F6, KC_F12,      KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                                    KC_NO, KC_NO,       KC_TRNS, KC_NO
    ),
};

enum combos {
    PC_J,
    BG_X,
    BM_ESCAPE,
    MG_TAB,
    DQ_GRAVE,
    QS_PERCENT,
};

const uint16_t PROGMEM j_combo[] = {KC_P, KC_C, COMBO_END};
const uint16_t PROGMEM x_combo[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_B, KC_M, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_M, KC_G, COMBO_END};
const uint16_t PROGMEM grave_combo[] = {KC_DOT, KC_QUOT, COMBO_END};
const uint16_t PROGMEM percent_combo[] = {KC_QUOT, KC_SCLN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [PC_J]       = COMBO(j_combo, KC_J),
    [BG_X]       = COMBO(x_combo, KC_X),
    [BM_ESCAPE]  = COMBO(escape_combo, KC_ESC),
    [MG_TAB]     = COMBO(tab_combo, S(KC_TAB)),
    [DQ_GRAVE]   = COMBO(grave_combo, KC_GRAVE),
    [QS_PERCENT] = COMBO(percent_combo, S(KC_5)),
};

const key_override_t question_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_SLSH));
const key_override_t exclamation_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, S(KC_1));
const key_override_t forward_slash_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, S(KC_6));

const key_override_t **key_overrides = (const key_override_t *[]){
    &question_mark_override,
    &exclamation_mark_override,
    &forward_slash_override,
    NULL
};
