// Copyright 2022 @janlindblom
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

// Seniply layout
// https://stevep99.github.io/seniply

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_MINS,
                          LT(3,KC_TAB), KC_LSFT,     KC_SPC,  LT(1,KC_ENT)
    ),
    [1] = LAYOUT_split_3x5_2(
    SE_EXLM, SE_AT,   SE_SCLN, SE_COLN, SE_UNDS,     SE_EQL,  KC_7,    KC_8,    KC_9,    SE_PLUS,
    SE_BSLS, SE_PIPE, SE_LCBR, SE_LPRN, SE_LBRC,     SE_ASTR, KC_4,    KC_5,    KC_6,    SE_MINS,
    KC_NO,   KC_NO,   SE_RCBR, SE_RPRN, SE_RBRC,     KC_0,    KC_1,    KC_2,    KC_3,    SE_SLSH,
                               _______, MO(2),       _______, _______
    ),
    [2] = LAYOUT_split_3x5_2(
    RALT(KC_1), RALT(KC_2), RALT(KC_3), RALT(KC_4), KC_BRIU,     KC_NO,   SE_AMPR, SE_GRV,  SE_TILD, KC_NO,
    KC_MUTE,    KC_VOLD,    KC_MPLY,    KC_VOLU,    KC_BRID,     KC_NO,   SE_DLR,  SE_PERC, SE_CIRC, SE_UNDS,
    KC_EJCT,    KC_MPRV,    KC_MSTP,    KC_MNXT,    KC_NO,       KC_NO,   SE_EXLM, SE_AT,   SE_HASH, KC_NO,
                                           _______, _______,     _______, _______
    ),
    [3] = LAYOUT_split_3x5_2(
    KC_ESC,        LALT(KC_LEFT), LCTL(KC_F),    LALT(KC_RGHT), KC_INS,            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_CAPS,
    OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_RALT),     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
    LCTL(KC_Z),    LCTL(KC_X),    LCTL(KC_C),    KC_TAB,        LCTL(KC_V),        KC_ENT,  KC_BSPC, KC_RCTL, KC_LALT, KC_APP,
                                                       _______, _______,           _______, MO(4)
    ),
    [4] = LAYOUT_split_3x5_2(
    KC_NO,         KC_NO,         RCS(KC_F),     KC_PSCR,       KC_NO,             KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_NO,
    OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_RALT),     KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_NO,
    RCS(KC_Z),     RCS(KC_X),     RCS(KC_C),     LSFT(KC_TAB),  RCS(KC_V),         KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_NO,
                                                       _______, _______,           _______, _______
    ),
    [5] = LAYOUT_split_3x5_2(
    KC_NO,  KC_NO,  KC_NO,  EH_RGHT,    KC_NO,             KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,             KC_NO,   KC_NO,   EH_LEFT,   KC_NO,   KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    RESET,             KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,
                            _______,  _______,           _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 3, 5);
}
