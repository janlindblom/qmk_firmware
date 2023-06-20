/**
 * Copyright © 2022 Jan Lindblom (@janlindblom)
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

#include "namnlos.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

extern userspace_config_t userspace_config;

// Tap Dance definitions
#ifdef TAP_DANCE_ENABLE
enum {
    TD_SHFT_CAPS,
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
#    define CK_LSFT TD(TD_SHFT_CAPS)
#else
#    define CK_LSFT KC_LSFT
#endif

// Some defines for the keys below
#define CK_ESC LT(_NUMB, KC_ESC)
#define CK_BSPC MT(MOD_LCTL, KC_BSPC)
#define CK_DEL MT(MOD_LGUI, KC_DEL)
#define CK_ENT1 MT(MOD_LALT, KC_ENT)
#define CK_SPC1 LT(_SYMB, KC_SPC)
#define CK_ENT2 LT(_SYMB, KC_ENT)
#define CK_SPC2 LT(_NUMB, KC_SPC)
#define CK_TAB MT(MOD_RALT, KC_TAB)
#define CK_ADIA MT(MOD_RCTL, SE_ADIA)
#define CK_MINS MT(MOD_RCTL, SE_MINS)
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_BSP2 LT(_MOUSE, KC_BSPC)
#define CK_ENT3 LT(_SYMB, KC_ENT)

#define ADJUST MO(_ADJST)

#ifdef UNICODE_ENABLE
#    define CK_ENDASH UC(0x2013)
#    define CK_EMDASH UC(0x2014)
#else
#    define CK_ENDASH KC_TRNS
#    define CK_EMDASH KC_TRNS
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
     *
     * ,--------------------------------------------.                         ,-------------------------------------------.
     * | NUMB/⎋  |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |   Å    |
     * |---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |Ctrl/BkSp|   A  |   S  |  D   |   F  |   G  |      |           | BkSp |   H  |   J  |   K  |   L  |   Ö  | Ctrl/Ä |
     * |---------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * | ⇧/Caps  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | , ;  | . :  | - _  | ⇧ / '* |
     * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *                    .----------.   .-------.                                 .-----------.   .-----.
     *                    |  Win/Del |   |  ↲/ALT|                                 | ⭾/AltGr |    |BKSP |
     *                    '----------'   '-------'                                 `-----------.   '-----'
     *                                        ,-------.                      ,-------.
     *                                        | Paste |                      |   ⇟   |
     *                                 ,------|-------|                      |-------|------.
     *                                 | SYMB | NUMB  |                      | SYMB  | NUMB |
     *                                 |   ⎵  |  ⎋    |                      |   ↲   |   ⎵  |
     *                                 |      |       |                      |       |      |
     *                                 `--------------'                      `--------------'
     */
    [_BASE] = LAYOUT(
         CK_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                               KC_Y,    KC_U,   KC_I,     KC_O,    KC_P, SE_ARNG,
        CK_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, _______,                           KC_BSPC,   KC_H,    KC_J,   KC_K,     KC_L, SE_ODIA, CK_ADIA,
        CK_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, _______, CK_PSTE,         KC_PGDN, KC_EQL,    KC_N,    KC_M, SE_COMM,  SE_DOT, SE_MINS, CK_QUOT,
                                             CK_DEL, CK_ENT1, CK_SPC1,  CK_ESC,         CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2),
    /* Keymap 1: Symbols layer
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |    ≠   |  !   |  @   |  {   |  }   |  |   |                         |   £  |  €   |  ?   |  §   |   ¤  |   ¨    |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |    ≤   |  #   |  $   |  (   |  )   |  `   |      |           |   ”  |   +  |  -   |  /   |  *   |  ´   |   —    |
     * |--------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * |    ≥   |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |   &  |  =   |  <   |  >   |  \   |   –    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *                        .------.   .------.                                 .------.   .-----.
     *                        |      |   |      |                                 |      |   | Del |
     *                        '------'   '------'                                 `------.   '-----'
     *                                        ,-------.                     ,-------.
     *                                        |  Copy |                     |   ⇞   |
     *                                 ,------|-------|                     |-------|------.
     *                                 |      |       |                     |       |      |
     *                                 |      |       |                     |       |      |
     *                                 |      |       |                     |       |      |
     *                                 `--------------'                     `--------------'
     */
    [_SYMB] = LAYOUT(
        SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                                              SE_PND, SE_EURO, SE_QUES, SE_SECT, SE_CURR, SE_DIAE,
            SK_LEQ, SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV, XXXXXXX,                           SE_DQUO, SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_ACUT, CK_EMDASH,
            SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD, XXXXXXX, CK_COPY,         KC_PGUP, XXXXXXX, SE_AMPR,  SE_EQL, SE_LABK, SE_RABK, SE_BSLS, CK_ENDASH,
                                               _______, _______, _______,  _______,        _______, _______, _______, KC_DEL),
    /* Keymap 2: Pad/Function layer
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   |  MUTE  |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |   F1   |  F2  |  F3  |  F4  |  F5  | F6   |      |           |      | LEFT | DOWN |  UP  | RIGHT|   ⇞  |   🕪    |
     * |--------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * |   F7   |  F8  |  F9  | F10  | F11  | F12  |      |           |      | <==  |  ==> | Home | End  |   ⇟  |   🕩    |
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
    [_NUMB] = LAYOUT(
        _______,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MUTE,
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, XXXXXXX,                           _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP, KC_VOLU,
        KC_F11,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,  CK_CUT,         _______, _______, CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN, KC_VOLD,
                                           _______, _______, _______, _______,         _______, _______, _______, _______),
    /* Adjustments and system
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |        |QMKmke|      |      |      |      |                         |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |        |AuDesk|      |      |      |OLEDB+|      |           |      |      |      |KiCAD |      |      |        |
     * |--------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * |        |      |      |      |      |OLEDB-|      |           |      |      |      |      |      |      |        |
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
     */
    [_ADJST] = LAYOUT(
        XXXXXXX, QK_MAKE,  XXXXXXX, CG_NORM, QK_BOOT, XXXXXXX,                                                 XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, CK_ADESK,CK_SVORAK,CG_SWAP, CK_OBI,  CK_GAMING, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, CK_KICAD, KC_MSTP, KC_MPLY, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, CG_TOGG, CK_OBD,  XXXXXXX,   XXXXXXX, XXXXXXX,         CK_QWERTY, XXXXXXX, NK_TOGG, XXXXXXX,  XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX,
                                             _______, _______, _______, _______,           _______, _______, _______, _______),
    /* Mouse control
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |        |      |      |  su  |      |      |                         |      |      |  up  |      |      |        |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |        |      |  sl  |  sd  |  sr  |  su  |      |           |      |      |  le  |  dn  |  ri  |      |        |
     * |--------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * |        |      |      |      |      |  sd  |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *                        .------.   .------.                                 .------.   .-----.
     *                        |      |   |      |                                 |      |   |     |
     *                        '------'   '------'                                 `------.   '-----'
     *                                        ,-------.       ,-------.
     *                                        |       |       |       |
     *                                 ,------|-------|       |-------|------.
     *                                 |      |       |       |       |      |
     *                                 |  m1  |  m2   |       |       |      |
     *                                 |      |       |       |       |      |
     *                                 `--------------'       `--------------'
     */

    [_MOUSE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX,                                             XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_R, KC_WH_U, XXXXXXX,                           XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, KC_BTN1, KC_BTN2,         _______, _______, _______, _______),
    /* Svorak
     *
     * ,--------------------------------------------.                         ,-------------------------------------------.
     * | NUMB/⎋  |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |   Å    |
     * |---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |Ctrl/BkSp|   A  |   S  |  D   |   F  |   G  |      |           | BkSp |   H  |   J  |   K  |   L  |   Ö  | Ctrl/Ä |
     * |---------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * | ⇧/Caps  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | , ;  | . :  | - _  | ⇧ / '* |
     * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *                    .----------.   .-------.                                 .-----------.   .-----.
     *                    |  Win/Del |   |  ↲/ALT|                                 | ⭾/AltGr |    |BKSP |
     *                    '----------'   '-------'                                 `-----------.   '-----'
     *                                        ,-------.                      ,-------.
     *                                        | Paste |                      |   ⇟   |
     *                                 ,------|-------|                      |-------|------.
     *                                 | SYMB | NUMB  |                      | SYMB  | NUMB |
     *                                 |   ⎵  |  ⎋    |                      |   ↲   |   ⎵  |
     *                                 |      |       |                      |       |      |
     *                                 `--------------'                      `--------------'
     */
    [_SVRK] = LAYOUT(
         CK_ESC, SE_ARNG, SE_ADIA, SE_ODIA,    KC_P,    KC_Y,                                               KC_F,    KC_G,   KC_C,     KC_R,    KC_L, SE_COMM,
        CK_BSPC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I, _______,                           KC_BSPC,   KC_D,    KC_H,   KC_T,     KC_N,    KC_S, CK_MINS,
        CK_LSFT,  SE_DOT,    KC_Q,    KC_J,    KC_K,    KC_X, _______, CK_PSTE,         KC_PGDN, XXXXXXX,   KC_B,    KC_M,   KC_W,     KC_V,    KC_Z, CK_QUOT,
                                             CK_DEL, CK_ENT1, CK_SPC1,  CK_ESC,         CK_ENT2, CK_SPC2, CK_TAB, CK_QWERTY),
    /*
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |  Esc   |  Q   |  W   |  E   |  R   |  T   |                         |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |  Ctrl  |  A   |  L   |  D   |  M   |  G   |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * |  Shift |  Z   |  X   |  C   |  V   |  B   |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *                        .------.   .------.                                 .------.   .-----.
     *                        | Del  |   | ↲/ALT|                                 |      |   |     |
     *                        '------'   '------'                                 `------.   '-----'
     *                                        ,-------.       ,-------.
     *                                        |   Y   |       |QWERTY |
     *                                 ,------|-------|       |-------|------.
     *                                 |      |       |       |       |      |
     *                                 |      |       |       |       |      |
     *                                 |      |       |       |       |      |
     *                                 `--------------'       `--------------'
     */
    [_KICAD] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_A,    KC_L,    KC_D,    KC_M,    KC_G,    XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,  KC_Y,           CK_QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_DEL,  CK_ENT1, CK_SPC1,  CK_ESC,         CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2),

    /*
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |  Esc   |  I   |  M   |  E   |  R   |  T   |                         |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |  Ctrl  |  A   |  S   |  D   |  F   |  J   |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |------|------+------+------+------+------+--------|
     * |  Shift |  P   |  X   |  C   |  V   |  B   |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *                        .------.   .------.                                 .------.   .-----.
     *                        | Del  |   | ↲/ALT|                                 |      |   |     |
     *                        '------'   '------'                                 `------.   '-----'
     *                                        ,-------.       ,-------.
     *                                        |   M   |       |QWERTY |
     *                                 ,------|-------|       |-------|------.
     *                                 |      |       |       |       |      |
     *                                 |      |       |       |       |      |
     *                                 |      |       |       |       |      |
     *                                 `--------------'       `--------------'
     */
    [_ADESK] = LAYOUT(
        KC_ESC,  KC_I,    KC_M,    KC_E,    KC_R,    KC_T,                                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_J,    XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, KC_P,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,  KC_M,           CK_QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             KC_DEL, CK_ENT1, CK_SPC1,  CK_ESC,         CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2),

    [_GAMING] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                   KC_Y,    KC_U,   KC_I,     KC_O,    KC_P, KC_MUTE,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G, XXXXXXX,                               KC_BSPC,KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, KC_BRIU, KC_VOLU,
        KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX, XXXXXXX,           CK_QWERTY, XXXXXXX,   KC_N,    KC_M, SE_COMM,  SE_DOT, KC_BRID, KC_VOLD,
                                            CK_DEL,  KC_SPC, CK_ENT3,  CK_ESC,           CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2),
};
// clang-format on

void render_layer_name(uint_fast8_t layer) {
    static const char PROGMEM layer_names[][6] = {
        // clang-format off
        [_KICAD] = OLED_RENDER_LAYOUT_KICAD,
        [_ADESK] = OLED_RENDER_LAYOUT_ADESK,
        [_GAMING] = OLED_RENDER_LAYOUT_GAMING
        // clang-format on
    };
#ifdef OLED_LAYER_COL
    OLED_PLACE_CURSOR_FULL(OLED_LAYER_LINE, OLED_LAYER_COL);
#else
    OLED_PLACE_CURSOR(OLED_LAYER_LINE);
#endif
    oled_write_P(layer_names[layer], false);
}

#ifdef OLED_ENABLE
bool render_layer_state_keymap(void) {
    uint_least8_t top_layer = get_highest_layer(default_layer_state);
    switch (top_layer) {
        case _KICAD:
        case _ADESK:
            render_layer_name(top_layer);
            break;
        case _GAMING:
            render_layer_name(top_layer);
            break;
        default:
            return true; // return true and let userspace level render_layer_state run.
    }
    return false; // return false to prevent userspace level render_layer_state from running.
}

#    ifdef RENDER_PET
bool render_pet_keymap(void) {
    uint_least8_t top_layer = get_highest_layer(default_layer_state);
    // Turn off the pet for these layers.
    switch (top_layer) {
        case _KICAD:
        case _ADESK:
            return false;
        default:
            return true; // Otherwise let userspace render_pet run.
    }
}
#    endif // RENDER_PET

uint8_t render_icon_keymap(void) {
    uint_least8_t top_layer = get_highest_layer(default_layer_state);
    // Catch these layers and return the icon for them.
    switch (top_layer) {
        case _KICAD:
            return ICON_KICAD;
        case _ADESK:
            return ICON_AUTODESK;
        default:
            return 0; // Otherwise return 0 to prevent any icon rendering.
    }
}

#    ifdef WPM_ENABLE
bool render_wpm_keymap(void) {
    uint_least8_t top_layer = get_highest_layer(default_layer_state);
    // Don't gather WPM for these layers or if we're blocking it for some reason.
    if ((top_layer == _GAMING) || (top_layer == _KICAD) || (top_layer == _ADESK)) {
        return false;
    }
    return true;
}
#    endif // WPM_ENABLE

oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}
#endif // OLED_ENABLE

// Combos, if enabled
#ifdef COMBO_ENABLE
enum combo_events {
    ZC_COPY,
    XV_PASTE,
    ZX_CUT,
};

const uint16_t PROGMEM copy_combo[]  = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM cut_combo[]   = {KC_Z, KC_X, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [ZC_COPY]  = COMBO_ACTION(copy_combo),
    [XV_PASTE] = COMBO_ACTION(paste_combo),
    [ZX_CUT]   = COMBO_ACTION(cut_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case ZC_COPY:
            if (pressed) {
                tap_code16(LCTL(KC_C));
            }
            break;
        case XV_PASTE:
            if (pressed) {
                tap_code16(LCTL(KC_V));
            }
            break;
        case ZX_CUT:
            if (pressed) {
                tap_code16(LCTL(KC_X));
            }
            break;
    }
}
#endif // COMBO_ENABLE
