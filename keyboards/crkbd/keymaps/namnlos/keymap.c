/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Jan Lindblom <jan@namnlos.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum layer_names {
    L_BASE,
    L_LOWER,
    L_RAISE,
    L_ADJUST
};

// Custom keycodes for send_string-stuff.
enum custom_keycodes {
    SK_NOT_EQL = SAFE_RANGE,
    SK_LEQ,
    SK_GEQ,
};

typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_change        : 1;
        bool     rgb_matrix_idle_anim    : 1;
        uint8_t  rgb_matrix_active_mode  : 4;
        uint8_t  rgb_matrix_idle_mode    : 4;
        uint8_t  rgb_matrix_active_speed : 8;
        uint8_t  rgb_matrix_idle_speed   : 8;
        uint16_t rgb_matrix_idle_timeout : 16;
    };
} user_config_t;

user_config_t user_config;
static uint32_t oled_timer = 0;

#ifdef RGB_MATRIX_ENABLE
    static uint32_t hypno_timer;
#endif

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
#endif

// Tap Dance definitions
#ifdef TAP_DANCE_ENABLE
enum dances {
    TD_SHFT_CAPS,
    TD_DOT_COL,
    TD_COM_SCL,
    TD_DASH_USCR,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_COM_SCL]   = ACTION_TAP_DANCE_DOUBLE(KC_COMM, SE_SCLN),
    [TD_DOT_COL]   = ACTION_TAP_DANCE_DOUBLE(KC_DOT, SE_COLN),
    [TD_DASH_USCR] = ACTION_TAP_DANCE_DOUBLE(SE_MINS, S(SE_MINS)),
};
#    define CK_LSFT TD(TD_SHFT_CAPS)
#    define CK_COMM TD(TD_COM_SCL)
#    define CK_DOT TD(TD_DOT_COL)
#    define CK_DASH TD(TD_DASH_USCR)
#else
#    define CK_LSFT KC_LSFT
#    define CK_COMM KC_COMM
#    define CK_DOT KC_DOT
#    define CK_DASH SE_MINS
#endif

// Some defines for the keys below
#define CK_ESC LT(L_RAISE, KC_ESC)
#define CK_BSPC MT(MOD_LCTL, KC_BSPC)
#define CK_DEL MT(MOD_LGUI, KC_DEL)
#define CK_ENT1 MT(MOD_LALT, KC_ENT)
#define CK_SPC1 LT(L_LOWER, KC_SPC)
#define CK_ENT2 LT(L_LOWER, KC_ENT)
#define CK_SPC2 LT(L_RAISE, KC_SPC)
#define CK_TAB MT(MOD_RALT, KC_TAB)
#define CK_ADIA MT(MOD_RCTL, SE_ADIA)
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)

#ifdef UNICODE_ENABLE
#    define EM_DASH 0x2014
#    define EN_DASH 0x2013
#    define CK_ENDASH UC(EN_DASH)
#    define CK_EMDASH UC(EM_DASH)
#else
#    define CK_ENDASH KC_TRNS
#    define CK_EMDASH KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CK_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  SE_ARNG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CK_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, SE_ODIA, CK_ADIA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CK_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, CK_COMM,  CK_DOT, CK_DASH, CK_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           CK_DEL, CK_ENT1, CK_SPC1,    CK_ENT2, CK_SPC2, CK_TAB
                                      //`--------------------------'  `--------------------------'

  ),

  [L_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                       SE_PND, SE_EURO, SE_QUES, SE_SECT, SE_CURR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       SK_LEQ, SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,                      SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC,CK_EMDASH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD,                      SE_AMPR,  SE_EQL, _______, _______, SE_BSLS, CK_ENDASH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SE_LABK, SE_RABK,  KC_ENT,     KC_SPC, SE_DQUO,  KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_MENU, _______, KC_ENT,    KC_SPC, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef WPM_ENABLE
bool wpm_keycode_user(uint16_t keycode) {
    return true;
}
#endif

#ifdef OLED_ENABLE
#    define OLED_SPACE " "

#    ifdef WPM_ENABLE
// WPM-responsive animation stuff here
#        define FRAMES 2
#        define SLEEP_SPEED 10  // below this wpm value your animation will idle
#        define KAKI_SPEED 40  // above this wpm value typing animation to triggere
#        define ANIM_SIZE 128  // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer          = 0;
uint16_t anim_frame_duration = 500;
uint8_t  current_sleep_frame = 0;
uint8_t  current_wake_frame  = 0;
uint8_t  current_kaki_frame  = 0;

// clang-format off
void render_kitty(void) {
    // Images credit j-inc(/James Incandenza) and pixelbenny. Credit to obosob for initial animation approach.
    static const char PROGMEM sleep[FRAMES][ANIM_SIZE] = {{
                                                                    // 'sleep1', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xa8, 0x48, 0xa8, 0x18, 0x08, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x80, 0x44, 0x84, 0x06, 0x05, 0x04, 0x80, 0x40, 0x20, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x18, 0x04, 0x04, 0x02, 0x7a, 0x86, 0x01, 0x80, 0x80, 0x01, 0x03, 0x05, 0x07, 0x01, 0x00, 0x00, 0x80, 0x83, 0x45, 0xfa, 0x3c, 0xe0, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28, 0x28, 0x29, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39, 0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00,
                                                                },
                                                                {// 'sleep2', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x3a, 0x2a, 0x26, 0x22, 0x80, 0xc0, 0x80, 0x00, 0x24, 0x34, 0x2c, 0xe4, 0x60, 0x10, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38, 0x04, 0x02, 0x02, 0x01, 0x79, 0x87, 0x01, 0x80, 0x81, 0x83, 0x05, 0x05, 0x03, 0x01, 0x00, 0x00, 0x80, 0x43, 0x05, 0xfa, 0x3c, 0xe0, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28, 0x28, 0x28, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39, 0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00
                                                                }};
    static const char PROGMEM wake[FRAMES][ANIM_SIZE]   = {{
                                                                  // 'mati2', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80, 0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x40, 0x40, 0x5c, 0x00, 0x01, 0x41, 0x01, 0x00, 0x5c, 0x40, 0x40, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x00, 0x80, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08
                                                                },
                                                                {// 'mati3', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80, 0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x90, 0x12, 0x0a, 0x02, 0xf4, 0x09, 0x0d, 0xf1, 0x04, 0x02, 0x0a, 0x12, 0x90, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x01, 0x81, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08
                                                                }};
    static const char PROGMEM kaki[3][ANIM_SIZE]   = {{
                                                                  // 'jare2', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x80, 0x80, 0x00, 0xfc, 0x84, 0x08, 0x08, 0x10, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x60, 0x80, 0x00, 0x00, 0x91, 0xa1, 0x80, 0x00, 0x00, 0x22, 0x84, 0x40, 0x50, 0x48, 0xc1, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x41, 0x82, 0xe2, 0x12, 0x0a, 0x06, 0x00, 0x80, 0x88, 0x4f, 0x02, 0x22, 0xe2, 0x9f, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1a, 0x0a, 0x0a, 0x04, 0x00
                                                              },
                                                              {
                                                                  // 'kaki1', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x06, 0x1a, 0x22, 0xc2, 0x04, 0x04, 0x04, 0x07, 0x00, 0xc0, 0x20, 0x10, 0x80, 0x80, 0x01, 0x01, 0x02, 0xfc, 0xfe, 0x02, 0x3c, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d, 0x55, 0x50, 0x94, 0xf0, 0x10, 0x09, 0x08, 0x00, 0x80, 0x00, 0x06, 0x09, 0x1b, 0xee, 0x00, 0x00, 0x00, 0x00, 0x81, 0xfe, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c, 0x14, 0x16, 0x15, 0x14, 0x14, 0x14, 0x14, 0x08
                                                              },
                                                              {// 'kaki2', 32x32px
                                                                    0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x01, 0x02, 0x04, 0x04, 0x03, 0x80, 0x40, 0x40, 0x20, 0x00, 0x01, 0x02, 0x8c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d, 0x55, 0x50, 0x94, 0xf0, 0x10, 0x0a, 0x0e, 0x1d, 0x95, 0x24, 0x24, 0x27, 0x13, 0xe1, 0x01, 0x01, 0x01, 0x01, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00,
                                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c, 0x14, 0x14, 0x17, 0x14, 0x14, 0x14, 0x14, 0x08,
                                                                }};

    // clang-format on
    // assumes 1 frame prep stage
    void animation_phase(void) {
        if (get_current_wpm() <= SLEEP_SPEED) {
            anim_frame_duration = 500;
            current_sleep_frame = (current_sleep_frame + 1) % FRAMES;
            oled_write_raw_P(sleep[abs(1 - current_sleep_frame)], ANIM_SIZE);
        }
        if (get_current_wpm() > SLEEP_SPEED) {
            anim_frame_duration = 800;
            current_wake_frame  = (current_wake_frame + 1) % FRAMES;
            oled_write_raw_P(wake[abs(1 - current_wake_frame)], ANIM_SIZE);
        }
        if (get_current_wpm() >= KAKI_SPEED) {
            anim_frame_duration = 500;
            current_kaki_frame  = (current_kaki_frame + 1) % 3;
            oled_write_raw_P(kaki[abs(2 - current_kaki_frame)], ANIM_SIZE);
        }
    }
    if (timer_elapsed32(anim_timer) > anim_frame_duration) {
        anim_timer = timer_read32();
        animation_phase();
    }
}
#    else
void render_kitty(void) { return; }
#    endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

#    ifdef RGB_MATRIX_ENABLE
const char *rgb_matrix_anim_oled_text(uint8_t mode) {
    switch (mode) {
        //case RGB_MATRIX_TYPING_HEATMAP:
        //    return PSTR("Heat ");
        //case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
        //    return PSTR("Nexus");
        case RGB_MATRIX_SOLID_COLOR:
            return PSTR("Solid");
        //case RGB_MATRIX_CYCLE_ALL:
        //    return PSTR("Cycle");
        //case RGB_MATRIX_RAINBOW_PINWHEELS:
        //    return PSTR("Wheel");
        //case RGB_MATRIX_CYCLE_LEFT_RIGHT:
        //    return PSTR("Wave ");
        default:
            return PSTR("");
    }
}
#    endif

void oled_render_layer_state(void) {
    oled_write_P(PSTR("LAYR:"), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case L_BASE:
            oled_write_ln_P(PSTR("BASE "), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case L_ADJUST:
            oled_write_ln_P(PSTR("ADJST"), false);
            break;
    }
}

void oled_render_keylock_state(uint8_t led_usb_state) {
    oled_write_P(PSTR("LOCK:"), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
    oled_write_P(PSTR("  \n"), false);
}

void oled_render_mod_state(uint8_t modifiers) {
    oled_write_P(PSTR("MODS:"), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR(" \n"), false);
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }

    if (is_keyboard_master()) {
#    ifdef WPM_ENABLE
        render_kitty();
        oled_set_cursor(0, 5);
#    else
        static const char PROGMEM font_logo[11] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x20, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0x20, 0};
        oled_write_P(font_logo, false);
#    endif
        oled_render_layer_state();
        oled_render_mod_state(get_mods());
        oled_render_keylock_state(host_keyboard_leds());
#    ifdef RGB_MATRIX_ENABLE
        oled_write_P(PSTR("\n"), false);
        oled_write_P(PSTR("\n"), false);

        if (rgb_matrix_config.enable) {
            if (user_config.rgb_matrix_idle_anim) {
                oled_write_P(rgb_matrix_anim_oled_text(user_config.rgb_matrix_active_mode), false);
                oled_write_P(rgb_matrix_anim_oled_text(user_config.rgb_matrix_idle_mode), false);
            } else {
                oled_write_P(PSTR("\n"), false);
                oled_write_P(rgb_matrix_anim_oled_text(rgb_matrix_get_mode()), false);
            }
        } else {
            oled_write_P(PSTR("\n"), false);
            oled_write_P(PSTR("\n"), false);
        }
#    endif
        oled_advance_page(true);
    } else {
        oled_render_logo();
#    ifdef RGB_MATRIX_ENABLE
        if (user_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode) {
            oled_scroll_left();  // Turns on scrolling
        } else {
            oled_scroll_off();
        }
#    endif
    }
}
#endif

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM base_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 54, HSV_CYAN});
const rgblight_segment_t PROGMEM symb_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 54, HSV_PURPLE});
const rgblight_segment_t PROGMEM num_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 54, HSV_AZURE});
const rgblight_segment_t PROGMEM adjust_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 54, HSV_PINK});
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 54, HSV_RED});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(base_layer, symb_layer, num_layer, adjust_layer, capslock_layer);
#endif

layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, L_BASE));
#endif
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, L_BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, L_RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, L_LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, L_ADJUST));
#endif
    return state;
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(4, led_state.caps_lock);
#endif
    return true;
}

#ifdef RGB_MATRIX_ENABLE
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void check_default_layer(uint8_t type) {
    switch (get_highest_layer(default_layer_state)) {
        case L_BASE:
            rgb_matrix_layer_helper(HSV_AZURE, type);
            break;
        default:
            rgb_matrix_layer_helper(HSV_RED, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
  if (
    user_config.rgb_layer_change && rgb_matrix_config.enable &&
      (!user_config.rgb_matrix_idle_anim || rgb_matrix_get_mode() != user_config.rgb_matrix_idle_mode)
  )
    {
        switch (get_highest_layer(layer_state)) {
            case L_LOWER:
                rgb_matrix_layer_helper(HSV_PURPLE, LED_FLAG_UNDERGLOW);
                break;
            case L_RAISE:
                rgb_matrix_layer_helper(HSV_GOLDENROD, LED_FLAG_UNDERGLOW);
                break;
            case L_ADJUST:
                rgb_matrix_layer_helper(HSV_CORAL, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(LED_FLAG_UNDERGLOW);
                break;
            }
        }
    }
}

void rgb_matrix_update_current_mode(uint8_t mode, uint8_t speed) {
    rgb_matrix_config.speed = speed;
    rgb_matrix_mode_noeeprom(mode);
    eeconfig_update_user(user_config.raw);
}

void rgb_matrix_update_dynamic_mode(uint8_t mode, uint8_t speed, bool active) {
    if (active) {
        user_config.rgb_matrix_active_speed = speed;
        user_config.rgb_matrix_active_mode  = mode;
    } else {
        user_config.rgb_matrix_idle_speed = speed;
        user_config.rgb_matrix_idle_mode  = mode;
    }
}

void rgb_matrix_update_mode(uint8_t mode, uint8_t speed, bool active) {
    if (user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_dynamic_mode(mode, speed, active);
    }
    if (active || !user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_current_mode(mode, speed);
    }
}

void rgb_matrix_set_defaults(void) {
    rgb_matrix_config.enable = 1;
    rgb_matrix_sethsv_noeeprom(HSV_AZURE);

    user_config.rgb_layer_change        = false;
    user_config.rgb_matrix_idle_anim    = true;
    user_config.rgb_matrix_idle_timeout = 60000;

    rgb_matrix_update_dynamic_mode(RGB_MATRIX_BREATHING, RGB_MATRIX_ANIMATION_SPEED_SLOWER, false);
    rgb_matrix_update_dynamic_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE, RGB_MATRIX_ANIMATION_SPEED_DEFAULT, true);

    eeprom_update_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
}

void matrix_scan_rgb(void) {
    if (user_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == user_config.rgb_matrix_active_mode && timer_elapsed32(hypno_timer) > user_config.rgb_matrix_idle_timeout) {
        if (user_config.rgb_layer_change) {
            rgb_matrix_layer_helper(0, 0, 0, LED_FLAG_UNDERGLOW);
        }
        rgb_matrix_update_current_mode(user_config.rgb_matrix_idle_mode, user_config.rgb_matrix_idle_speed);
    }
}

void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }
    matrix_scan_rgb();
}

void eeconfig_init_user(void) {
    user_config.raw = 0;
    rgb_matrix_mode_noeeprom(user_config.rgb_matrix_active_mode);
    keyboard_init();
}

void suspend_power_down_keymap(void) {
    oled_off();
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    oled_on();
    rgb_matrix_set_suspend_state(false);
}
#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef RGBLIGHT_LAYERS
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#    endif
    rgblight_enable();
#endif
    user_config.raw = eeconfig_read_user();
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_defaults();
    rgb_matrix_enable_noeeprom();
#endif
    return;
}

// Custom send_string keys
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    //static uint8_t saved_mods   = 0;
    //uint16_t       temp_keycode = keycode;

#ifdef OLED_ENABLE
    oled_timer = timer_read32();
#endif
    switch (keycode) {
        case SK_NOT_EQL:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING("!=");
            }
            break;
        case SK_LEQ:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING("<=");
            }
            break;
        case SK_GEQ:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(">=");
            }
            break;
    }

#ifdef RGB_MATRIX_ENABLE
    if (user_config.rgb_matrix_idle_anim) {
        hypno_timer = timer_read32();
        if (rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode) {
            rgb_matrix_update_current_mode(user_config.rgb_matrix_active_mode, user_config.rgb_matrix_active_speed);
            if (!user_config.rgb_layer_change) {
                rgb_matrix_layer_helper(0, 0, 0, LED_FLAG_UNDERGLOW);
            }
        }
    }
#endif
    return true;
}
