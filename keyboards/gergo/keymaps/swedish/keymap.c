/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#define BASE 0  // default layer
#define SYMB 1  // symbols
#define NUMB 2  // numbers/motion

// Blank template at the bottom

// Custom keycodes for send_string-stuff.
enum custom_keycodes {
    SK_NOT_EQL = SAFE_RANGE,
    SK_LEQ,
    SK_GEQ,
};

enum customKeycodes { URL = 1 };

enum dances {
    TD_SHFT_CAPS,
    TD_DOT_COL,
    TD_COM_SCL,
    TD_DASH_USCR,
};

// clang-format off

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_COM_SCL] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, SE_SCLN),
    [TD_DOT_COL] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, SE_COLN),
    [TD_DASH_USCR] = ACTION_TAP_DANCE_DOUBLE(SE_MINS, S(SE_MINS)),
};

#define U_ENDASH 0x2013 // –
#define U_EMDASH 0x2014 // —

// Custom send_string keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SK_NOT_EQL:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("!=");
        } else {
            // when keycodeis released
        }
        break;
        case SK_LEQ:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("<=");
        } else {
            // when keycodeis released
        }
        break;
        case SK_GEQ:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(">=");
        } else {
            // when keycodeis released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------.                         ,-------------------------------------------.
 * | NUMB/⎋  |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |Ctrl/BkSp|   A  |   S  |  D   |   F  |   G  |  H   |           | BkSp |   H  |   J  |   K  |   L  |   Ö  | Ctrl/Ä |
 * |---------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * | ⇧/Caps  |   Z  |   X  |   C  |   V  |   B  |  ⭾  |           |      |   N  |   M  | , ;  | . :  | - _  | ⇧ / '* |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .-----------.   .-----.
 *                    |  Win/Del |   |  ↲/ALT|                                 | ⭾/AltGr |    |BKSP |
 *                    '----------'   '-------'                                 `-----------.   '-----'
 *                                        ,-------.                      ,-------.
 *                                        | Paste |                      |   ⇟   |
 *                                 ,------|-------|                      |-------|------.
 *                                 | SYMB | NUMB  |                      | SYMB  | NUMB |
 *                                 |   ⎵  |  ⎋   |                      |   ↲   |   ⎵  |
 *                                 |      |      |                      |       |      |
 *                                 `-------------'                      `--------------'
 */
[BASE] = LAYOUT_gergo(
     LT(NUMB, KC_ESC), KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                                         KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    SE_ARNG,
MT(MOD_LCTL, KC_BSPC), KC_A,  KC_S,   KC_D,   KC_F, KC_G, KC_H,                         KC_BSPC,  KC_H, KC_J,  KC_K,    KC_L,   SE_ODIA, MT(MOD_RCTL, SE_ADIA),
     TD(TD_SHFT_CAPS), KC_Z,  KC_X,   KC_C,   KC_V, KC_B, KC_TAB, KC_PSTE,     KC_PGDN, KC_TRNS,  KC_N, KC_M,  TD(TD_COM_SCL), TD(TD_DOT_COL), TD(TD_DASH_USCR), MT(MOD_RSFT, SE_QUOT),
 MT(MOD_LGUI, KC_DEL), MT(MOD_LALT, KC_ENT), LT(SYMB, KC_SPC), LT(NUMB, KC_ESC),   LT(SYMB, KC_ENT), LT(NUMB, KC_SPC), MT(MOD_RALT, KC_TAB), KC_BSPC
    ),
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |    ≠   |  !   |  @   |  {   |  }   |  |   |                         |   £  |  €   |  ?   |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |    ≤   |  #   |  $   |  (   |  )   |  `   |  §/½ |           |   "  |   +  |  -   |  /   |  *   |  %   |   —    |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |    ≥   |  %   |  ^   |  [   |  ]   |  ~   |  ¤   |           |      |   &  |  =   |  ,   |  :   |  \   |   –    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |  <   |   |   >  |                                 |      |   | Del |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |  Copy |                     |   ⇞   |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |   ;  |   =   |                     |   =   |   ;  |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[SYMB] = LAYOUT_gergo(
    SK_NOT_EQL, SE_EXLM, SE_AT,   SE_LCBR, SE_RCBR, SE_PIPE,                                             SE_PND, SE_EURO, SE_QUES, KC_TRNS, KC_TRNS, KC_TRNS,
    SK_LEQ, SE_HASH, SE_DLR,  SE_LPRN, SE_RPRN, SE_GRV,  SE_SECT,                          SE_DQUO, SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC, UC(U_EMDASH),
    SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD, SE_CURR, KC_COPY,        KC_PGUP, KC_TRNS, SE_AMPR, SE_EQL,  KC_COMM, SE_COLN, SE_BSLS, UC(U_ENDASH),
                                         SE_LABK, SE_RABK, SE_SCLN, SE_EQL,        SE_EQL,  SE_SCLN, KC_TRNS, KC_DEL
    ),
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   |   ⏯    |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |  F1  | F2   | F3   | F4   | F5   | F6   |           |      | LEFT | DOWN |  UP  | RIGHT|   ⇞  |   🕪    |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  F7  | F8   | F9   | F10  | F11  | F12  |           |      | <==  |  ==> | Home | End  |   ⇟  |   🕩    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        | Menu |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |  Cut  |                     |       |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[NUMB] = LAYOUT_gergo(
    KC_TRNS,  KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MPLY,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, KC_VOLU,
    KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CUT,     KC_TRNS, KC_TRNS, C(KC_LEFT), C(KC_RGHT), KC_HOME, KC_END, KC_PGDN, KC_VOLD,
                                        KC_MENU, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

/* Keymap template
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
[NPAD] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
 */
