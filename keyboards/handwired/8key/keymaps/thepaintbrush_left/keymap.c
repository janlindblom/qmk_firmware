// Copyright 2023 Jan Lindblom (@janlindblom)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ S │ T │ R │ A │
     * ├───┼───┼───┼───┤
     * │ O │ I │ Y │ E │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_S,   KC_T,   KC_R,   KC_A,
        KC_O,   KC_I,   KC_Y,   KC_E
    )
};
