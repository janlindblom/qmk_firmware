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

enum layers {
    _MAIN = 0,
    _SYM,
    _NAV,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_Z,         KC_C,         KC_Y,          KC_W,             KC_K,    KC_X,    KC_L,           KC_U,         KC_COMM,      KC_Q,
        LSFT_T(KC_R), LALT_T(KC_S), LCTL_T(KC_I),  LT(_SYM, KC_T),   KC_G,    KC_M,    LT(_SYM, KC_N), RCTL_T(KC_E), RALT_T(KC_A), RSFT_T(KC_O),
        KC_J,         KC_F,         KC_P,          LGUI_T(KC_D),     KC_B,    KC_V,    RGUI_T(KC_H),   KC_QUOT,      KC_DOT,       KC_SLSH,
                                    KC_ENT,        LT(_NAV, KC_SPC), KC_BTN1, KC_BTN3, KC_RSFT,        KC_BSPC
    ),

    [_SYM] = LAYOUT(
        KC_DLR,  KC_7,   KC_8,   KC_9,    S(KC_8),   S(KC_GRV), KC_LBRC,    KC_RBRC,    S(KC_3), S(KC_5),
        KC_EXLM, KC_1,   KC_2,   KC_3,    KC_EQL,    KC_GRV,    S(KC_9),    S(KC_0),    KC_MINS, S(KC_BSLS),
        S(KC_6), KC_4,   KC_5,   KC_6,    S(KC_EQL), S(KC_7),   S(KC_LBRC), S(KC_RBRC), S(KC_2), KC_BSLS,
                         KC_DOT, KC_0,    KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    ),

    [_NAV] = LAYOUT(
        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,  KC_MUTE, KC_NO,   KC_NO,         KC_NO,         KC_NO,       KC_NO,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MPLY, G(KC_O), S(G(KC_DOWN)), C(G(KC_DOWN)), C(G(KC_UP)), S(G(KC_UP)), 
        KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_MSTP, KC_NO,   G(KC_LEFT),    G(KC_DOWN),    G(KC_UP),    G(KC_RIGHT),
                          KC_NO,   KC_NO,    KC_TRNS, KC_TRNS, KC_TRNS,       KC_DEL
    ),

    [_FN] = LAYOUT(
        KC_NO, KC_F7, KC_F8, KC_F9, KC_F10,  KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F1, KC_F2, KC_F3, KC_F11,  KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F4, KC_F5, KC_F6, KC_F12,  KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
                      KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO
    ),
};

enum combos {
    TW_TAB,
    YK_NT,
    CK_LT,
    HQ_MINS,
    FP_ESC,
    YW_LAUNCH,
    LC_QUIT,
    CY_COLON,
    CU_SCLN,
    QD_BTN2,
};

const uint16_t PROGMEM tab_combo[] = {KC_W, KC_T, COMBO_END};
const uint16_t PROGMEM next_tab_combo[] = {KC_Y, KC_K, COMBO_END};
const uint16_t PROGMEM last_tab_combo[] = {KC_C, KC_K, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {KC_H, KC_QUOT, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM launch_combo[] = {KC_Y, KC_W, COMBO_END};
const uint16_t PROGMEM quit_combo[] = {KC_L, KC_COMM, COMBO_END};
const uint16_t PROGMEM colon_combo[] = {KC_C, KC_Y, COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {KC_COMM, KC_U, COMBO_END};
const uint16_t PROGMEM button_2_combo[] = {KC_QUOT, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [TW_TAB]    = COMBO(tab_combo, KC_TAB),
    [YK_NT]     = COMBO(next_tab_combo, C(KC_TAB)),
    [CK_LT]     = COMBO(last_tab_combo, C(S(KC_TAB))),
    [HQ_MINS]   = COMBO(minus_combo, KC_MINS),
    [FP_ESC]    = COMBO(escape_combo, KC_ESC),
    [YW_LAUNCH] = COMBO(launch_combo, G(KC_SLSH)),
    [LC_QUIT]   = COMBO(quit_combo, G(KC_Q)),
    [CY_COLON]  = COMBO(colon_combo, S(KC_SCLN)),
    [CU_SCLN]   = COMBO(semicolon_combo, KC_SCLN),
    [QD_BTN2]   = COMBO(button_2_combo, KC_BTN2),
};
