/* Copyright 2022 @janlindblom
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
  _QWERTY,
  _LOWER,
  _RAISE
};

enum tap_dances {
  TD_Q_ESC
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for ESC
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

#define KC_CTSC RCTL_T(SE_SCLN)
#define KC_CTLA LCTL_T(KC_A)
#define KC_LSHZ LSFT_T(KC_Z)
#define KC_RLSH RSFT_T(SE_MINS)
#define KC_SPM2 LT(_RAISE, KC_SPC)
#define KC_BSM1 LT(_LOWER, KC_BSPC)
#define KC_GUTA RGUI_T(KC_TAB)
#define KC_CLGV LCTL_T(SE_GRV)

#define KC_QTAP TD(TD_Q_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* QWERTY */
                   KC_W, KC_E, KC_R,    KC_T,         KC_Y,    KC_U,   KC_I,    KC_O,
 KC_QTAP, KC_CTLA, KC_S, KC_D, KC_F,    KC_G,         KC_H,    KC_J,   KC_K,    KC_L,   KC_CTSC, KC_P,
          KC_LSHZ, KC_X, KC_C, KC_V,    KC_B,         KC_N,    KC_M,   KC_COMM, KC_DOT, KC_RLSH,
                               KC_CLGV, KC_BSM1,      KC_SPM2, KC_GUTA
  ),

  [_LOWER] = LAYOUT( /* [> LOWER <] */
                   KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,
    KC_1, KC_ESC,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, SE_QUOT, KC_0,
          _______, _______, _______, KC_BTN1, KC_BTN2,      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                                     _______, _______,      _______, _______
  ),

  [_RAISE] = LAYOUT( /* [> RAISE <] */
                    KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,
    KC_F1, KC_TAB,  _______, _______, _______, _______,      SE_MINS, SE_EQL,  SE_LBRC, SE_RBRC, SE_PIPE, KC_F10,
           _______, _______, _______, _______, _______,      SE_UNDS, SE_PLUS, _______, _______, RESET,
                                      _______, _______,      _______, _______
  )
};
