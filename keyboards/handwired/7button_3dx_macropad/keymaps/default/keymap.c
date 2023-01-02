// Copyright 2022 Jan Lindblom (@janlindblom)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgblight/rgblight.h"
#include "keycodes.h"

enum layers {
    // clang-format off
    _BASE,
    _MACROS,
    _ADJST
    // clang-format on
};

enum custom_keycodes {
    // clang-format off
    CK_CP_PST = SAFE_RANGE,
    CK_CT_PST
    // clang-format on
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * ┌───┬───┬───┐
     * │Esc│Sft│Del│
     * ├───┼───┼───┼───┐
     * │Ctl│Spc│Hom│L2 │
     * └───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_ESC, KC_LSFT,  KC_DEL,
        KC_LCTL, KC_SPC, KC_HOME, DF(1)
    ),
    /*
     * ┌───┬───┬───┐
     * │C+N│C+S│CCV│
     * ├───┼───┼───┼───┐
     * │CXV│Nxt│Prv│L1 │
     * └───┴───┴───┴───┘
     */
    [_MACROS] = LAYOUT(
        QK_MACRO_0, QK_MACRO_1, CK_CP_PST,
        CK_CT_PST,  KC_MNXT,    KC_MPRV,   DF(2)
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

const rgblight_segment_t PROGMEM layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_BLUE});
const rgblight_segment_t PROGMEM layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_RED});
const rgblight_segment_t PROGMEM layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_GREEN});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer1_layer, layer2_layer, layer3_layer);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _MACROS));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJST));
    return state;
}

bool buffer = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case CK_CP_PST:
        case CK_CT_PST:
            if (record->event.pressed) {
                if (buffer) {
                    SEND_STRING(SS_LCTL("v"));
                } else {
                    if (keycode == CK_CP_PST) {
                        SEND_STRING(SS_LCTL("c"));
                    } else if (keycode == CK_CT_PST) {
                        SEND_STRING(SS_LCTL("x"));
                    }
                }
                buffer = !buffer;
            }
            break;
    }
    return true;
};
