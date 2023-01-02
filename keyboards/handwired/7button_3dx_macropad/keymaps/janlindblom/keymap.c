// Copyright 2022 Jan Lindblom (@janlindblom)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgblight.h"
#include "action_layer.h"

#define RGB_KICAD 0x31, 0x4C, 0xB0
#define HSV_KICAD 227, 72, 69
#define RGB_ADESK 0xFF, 0x6B, 0x01
#define HSV_ADESK 25, 100, 100

enum layers { _BASE, _KICAD, _ADESK, _ADJST };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * ┌───┬───┬───┐
     * │Vo-│Vo+│Mut│
     * ├───┼───┼───┼───┐
     * │Ply│Prv│Nxt│L1 │
     * └───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_VOLD, KC_VOLU, KC_MUTE,
        KC_MPLY, KC_MPRV, KC_MNXT, DF(1)
    ),
    /*
     * ┌───┬───┬───┐
     * │ A │ E │ T │
     * ├───┼───┼───┼───┐
     * │ X │ R │ M │L2 │
     * └───┴───┴───┴───┘
     */
    [_KICAD] = LAYOUT(
        KC_A,    KC_E,    KC_T,
        KC_X,    KC_R,    KC_M,    DF(2)
    ),
    /*
     * ┌───┬───┬───┐
     * │ L │ C │ M │
     * ├───┼───┼───┼───┐
     * │ R │ P │ E │L3 │
     * └───┴───┴───┴───┘
     */
    [_ADESK] = LAYOUT(
        KC_L,    KC_C,    KC_M,
        KC_R,    KC_P,    KC_E,    DF(3)
    ),
    /*
     * ┌───┬───┬───┐
     * │R+ │BL │   │
     * ├───┼───┼───┼───┐
     * │R- │RGB│RST│L0 │
     * └───┴───┴───┴───┘
     */
    [_ADJST] = LAYOUT(
        RGB_VAI, BL_TOGG, KC_NO,
        RGB_VAD, RGB_TOG, QK_BOOT, DF(0)
    ),
    // clang-format on
};

const rgblight_segment_t PROGMEM layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_WHITE});
const rgblight_segment_t PROGMEM layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_KICAD});
const rgblight_segment_t PROGMEM layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_ADESK});
const rgblight_segment_t PROGMEM layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_RED});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer1_layer, layer2_layer, layer3_layer, layer4_layer);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _KICAD));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADESK));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJST));
    return state;
}
