/* Copyright 2021 Jan Lindblom <jan@robotika.ax>
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

#include "keymap_nordic.h"

enum layers {
    BASE,
    RAISE,
    LOWER,
    _SYSTEM,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_RAISE,
    KC_LOWER,
};

#define KC_LOWER TT(LOWER)
#define KC_RAISE TT(RAISE)

// Tap Dance declarations
enum {
    PG_UP,
    PG_DN,
    DEL_INS,
    ESC_PIPE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [PG_DN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
    [PG_UP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
    [DEL_INS] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS),
    [ESC_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, NO_LESS),
};

#define CK_ESC TD(ESC_PIPE)
#define CK_LCTRL MT(MOD_LCTL, KC_LEFT)
#define CK_LALT MT(MOD_LALT, KC_RGUI)
#define CK_LSPC MT(MOD_LSFT, KC_SPC)
#define CK_DELINS TD(DEL_INS)
#define CK_RENT MT(MOD_RSFT, KC_ENT)
#define CK_RALT MT(MOD_RALT, KC_APP)
#define CK_RCTRL MT(MOD_RCTL, KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT(
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   Å  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   '  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |  L   |  Ö   |  Ä   |
 * |------+------+------+------+------+------|  Down |    |  Up   |------+------+------+------+------+------|
 * |L_Ctrl|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  ,   |  .   |  -   |R_Ctrl|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                    | Del  | Lower| Alt | / Space /       \ Enter\  |  Alt |Raise | Bksp |
 *                    | Ins  |      | Win |/ Shift /         \ Shift\ | Menu |      |      |
 *                    `---------------------------'           '------'---------------------'
 */
    CK_ESC, KC_1, KC_2,   KC_3,     KC_4,    KC_5,                             KC_6, KC_7,      KC_8,    KC_9,   KC_0,    NO_PLUS,
    KC_TAB, KC_Q, KC_W,   KC_E,     KC_R,    KC_T,                             KC_Y, KC_U,      KC_I,    KC_O,   KC_P,    NO_AM,
   NO_APOS, KC_A, KC_S,   KC_D,     KC_F,    KC_G,                             KC_H, KC_J,      KC_K,    KC_L,   NO_AE,   NO_OSLH,
  CK_LCTRL, KC_Z, KC_X,   KC_C,     KC_V,    KC_B, TD(PG_DN),      TD(PG_UP),  KC_N, KC_M,      KC_COMM, KC_DOT, NO_MINS, CK_RCTRL,
            XXXXXXX, CK_DELINS, KC_LOWER, CK_LALT,   CK_LSPC,      CK_RENT, CK_RALT, KC_RAISE,  KC_BSPC, XXXXXXX
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |   ^  |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |  Up  |      |      |      |                    |   #  |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  Lt  |  Dn  |  Rt  |      |  ¨   |-------.    ,-------|   &  |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |  *   |  +   |  /   |  ´   |-------|    |-------|   $  |   0  |   ;  |   :  |   -  |      |
 * `----------------------------------------/       /      \      \-----------------------------------------'
 *           |      |      |      |      | /       /        \      \  |      |      |      |      |
 *           |      |      |      |      |/       /          \      \ |      |      |      |      |
 *           `-----------------------------------'            '------''---------------------------'
 */
[LOWER] = LAYOUT(
  _______,   KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                         NO_CIRC,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  _______, XXXXXXX,   KC_UP,  XXXXXXX, XXXXXXX, XXXXXXX,                         KC_HASH,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, NO_QUOT,                         NO_AMPR,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_PAST,  KC_PPLS, KC_PSLS, NO_ACUT, _______,       _______,  NO_DLR,    KC_0, NO_SCLN, NO_COLN, KC_PMNS, _______,
                    _______,  _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RESET |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /     \      \-----------------------------------------'
 *            |      |      |      |      | /      /       \      \  |      |      |      |      |
 *            |      |      |      |      |/      /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[RAISE] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  RESET,   _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* SYSTEM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |QWERTY|      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_SYSTEM] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RESET,   XXXXXXX, KC_QWERTY, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    _______,   _______, _______, _______, _______,     _______, _______, _______, _______, _______
  )
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("Lotus"), false);
    oled_write_P(PSTR("  58 "), false);
    oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
    // Print lock status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("Lock "), false);
    oled_write_P(PSTR("Caps "), led_usb_state.caps_lock);
    oled_write_P(PSTR("Num  "), led_usb_state.num_lock);
    oled_write_P(PSTR("Scrl "), led_usb_state.scroll_lock);
    oled_write_P(PSTR("\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(BASE);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            if (get_mods() & MOD_MASK_CTRL) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_VOLD);
            }

        } else {
            if (get_mods() & MOD_MASK_CTRL) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_VOLU);
            }
        }
    }
    return true;
}

#endif

#ifdef RGBLIGHT_LAYERS

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_RED},
    {6, 6, HSV_RED}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_CYAN},
    {6, 6, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_PURPLE},
    {6, 6, HSV_PURPLE}
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_GREEN},
    {6, 6, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer     // Overrides other layers
);
#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#endif
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, led_state.caps_lock);
#endif
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(1, layer_state_cmp(state, BASE));
#endif
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(2, layer_state_cmp(state, RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, LOWER));
#endif
    return update_tri_layer_state(state, RAISE, LOWER, _SYSTEM);
}
