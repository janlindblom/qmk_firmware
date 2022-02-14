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

extern userspace_config_t userspace_config;
#ifdef WPM_ENABLE
extern uint8_t current_wpm;
#endif // WPM_ENABLE

// Tap Dance definitions
#ifdef TAP_DANCE_ENABLE
enum dances {
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
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_BSP2 LT(_MOUSE, KC_BSPC)
#define CK_KOTG KEY_OVERRIDE_TOGGLE
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
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |Esc/NUM |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Bsp|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  | Ä/Ctrl |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | ⇧/Caps |   Z  |   X  |   C  |   V  |   B  | Tab  |Paste |  | PgDn | Bspc |   N  |   M  | ,  ; | .  : | -  _ | '* / ⇧ |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  Adj | Del  | LAlt/| Space| Esc  |  | Enter| Space| Tab  | Bspc | Bspc |
 *                        |      | GUI  | Enter| SYMB | NUM  |  | SYMB | NUM  | AltGr|      | MOVE |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT_split_3x6_5(
     CK_ESC , KC_Q ,  KC_W   ,  KC_E ,   KC_R,   KC_T ,                                         KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , SE_ARNG,
     CK_BSPC, KC_A ,  KC_S   ,  KC_D ,   KC_F,   KC_G ,                                         KC_H,   KC_J ,  KC_K ,   KC_L ,SE_ODIA, CK_ADIA,
     CK_LSFT, KC_Z ,  KC_X   ,  KC_C ,   KC_V,   KC_B ,  KC_TAB,CK_PSTE,     KC_PGDN, KC_BSPC,  KC_N,   KC_M ,SE_COMM,  SE_DOT,SE_MINS, CK_QUOT,
                               ADJUST, CK_DEL, CK_ENT1, CK_SPC1, CK_ESC,     CK_ENT2, CK_SPC2,CK_TAB, CK_BSP2, ADJUST
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   !=   |  !   |  @   |  {   |  }   |  |   |                              |   £  |  €   |  ?   |  §   |  ¤   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   <=   |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ---   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   >=   |  %   |  ^   |  [   |  ]   |  ~   |      | Copy |  | PgUp |   "  |   &  |  =   |  ,   |  :   |  \   |  --    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  <   |  >   |      |      |      |  |      |      |      | Del  |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMB] = LAYOUT_split_3x6_5(
   SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                                      SE_PND, SE_EURO, SE_QUES, SE_SECT, SE_CURR, KC_TRNS,
       SK_LEQ, SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,                                     SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC, CK_EMDASH,
       SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD, _______, CK_COPY, KC_PGUP, SE_DQUO, SE_AMPR, SE_EQL , SE_LABK, SE_RABK, SE_BSLS, CK_ENDASH,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL , _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1   | 2    | 3    | 4    |  5   |                              |  6   |  7   |  8   |  9   |  0   |Ply/Pau |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   F1   |  F2  |  F3  |  F4  |  F5  |  F6  |                              | Left | Down |  Up  | Right| PgUp | Vol Up |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   F7   |  F8  |  F9  | F10  | F11  | F12  |      |      |  |      |      |WLeft |WRight| Home | End  | PgDn | Vol Dn |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMB] = LAYOUT_split_3x6_5(
      _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                      KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_MPLY,
      KC_F1,    KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,                                     KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP, KC_VOLU,
      KC_F7,    KC_F8 ,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______, CK_CUT,  _______, _______, CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN, KC_VOLD,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Mouse Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |ScrlUp|      |      |                              |      |      | M Up |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |ScrlLt|ScrlDn|ScrlRt|      |                              |      |M Left|M Down|M Rght|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |M Btn1|M Btn2|  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOUSE] = LAYOUT_split_3x6_5(
      _______, _______, _______, KC_WH_U, _______, _______,                                    _______, _______, KC_MS_U, _______,  _______, _______,
      _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______,                                    _______, KC_MS_L, KC_MS_D, KC_MS_R,  _______, _______,
      _______, _______, _______, _______, _______, _______,KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______, _______,  _______, _______,
                                 _______, _______, KC_BTN1,KC_BTN2, KC_BTN3, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJST] = LAYOUT_split_3x6_5(
      EH_LEFT,  QK_MAKE,  XXXXXXX,   CG_NORM, XXXXXXX,   XXXXXXX,                                       RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW, RGB_M_TW, EH_RGHT,
      KC_KICAD, KC_ADESK, XXXXXXX,   CG_SWAP,  CK_OBI, KC_GAMING,                                       RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, RGB_SPI,
      XXXXXXX,  XXXXXXX,  XXXXXXX,   CG_TOGG,  CK_OBD,   QK_BOOT, _______, _______, KC_QWERTY, _______, NK_TOGG, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, RGB_SPD,
                                     _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______
    ),
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
    [_KICAD] = LAYOUT_split_3x6_5(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_A,    KC_L,    KC_D,    KC_M,    KC_G,                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,   KC_Y, KC_QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, KC_DEL,  CK_ENT1, CK_SPC1, CK_ESC,   CK_ENT2, CK_SPC2, CK_TAB,  CK_BSP2, _______
    ),

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
    [_ADESK] = LAYOUT_split_3x6_5(
        KC_ESC,  KC_I,    KC_M,    KC_E,    KC_R,    KC_T,                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_J,                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, KC_P,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,  KC_M,   KC_QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, KC_DEL,  CK_ENT1, CK_SPC1,  CK_ESC,   CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2, _______
    ),

    [_GAMING] = LAYOUT_split_3x6_5(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                             KC_Y,    KC_U,   KC_I,     KC_O,    KC_P, KC_MUTE,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, KC_BRIU, KC_VOLU,
        KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX, XXXXXXX,   KC_QWERTY, XXXXXXX,   KC_N,    KC_M, SE_COMM,  SE_DOT, KC_BRID, KC_VOLD,
                                   _______, CK_DEL,  KC_SPC, CK_ENT3,  CK_ESC,     CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2, _______
    ),
};
// clang-format on

#ifdef OLED_ENABLE
void render_layer_name(uint_fast8_t layer) {
    static const char PROGMEM layer_names[][10] = {
        // clang-format off
        [_KICAD] = OLED_RENDER_LAYOUT_KICAD,
        [_ADESK] = OLED_RENDER_LAYOUT_ADESK,
        [_GAMING] = OLED_RENDER_LAYOUT_GAMING
        // clang-format on
    };
    OLED_PLACE_CURSOR(0);
    oled_write_P(layer_names[layer], false);
}

bool render_layer_state_keymap(void) {
    userspace_config.raw         = eeconfig_read_user();
    userspace_config.gaming_mode = false;
    uint_least8_t top_layer      = get_highest_layer(default_layer_state);
    switch (top_layer) {
        case _KICAD:
        case _ADESK:
            render_layer_name(top_layer);
            break;
        case _GAMING:
            // Catch gaming layers to set gaming_mode true and break to return false.
            userspace_config.gaming_mode = true;
            eeconfig_update_user(userspace_config.raw);
            render_layer_name(top_layer);
            break;
        default:
            oled_write_P(PSTR("           "), false);
            return true; // return true and let userspace level render_layer_state run.
    }
    eeconfig_update_user(userspace_config.raw);
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

void render_kyria_logo(void) {
#    if defined(CONVERT_TO_KB2040) || defined(CONVERT_TO_PROMICRO_RP2040) || defined(CONVERT_TO_BLOK) || defined(CONVERT_TO_RP2040_CE) || defined(CONVERT_TO_ELITE_PI)
    // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
    // clang-format on
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
#    endif
}

bool oled_task_non_master_keymap(void) {
#    if defined(CONVERT_TO_KB2040) || defined(CONVERT_TO_PROMICRO_RP2040) || defined(CONVERT_TO_BLOK) || defined(CONVERT_TO_RP2040_CE) || defined(CONVERT_TO_ELITE_PI)
    render_kyria_logo();
#    endif
    return false;
}
#endif // OLED_ENABLE
