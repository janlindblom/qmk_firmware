/* Copyright © 2022 Jan Lindblom (@janlindblom)
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
#include "keymap_swedish_pro_osx_iso.h"

// Tap Dance definitions
#ifdef TAP_DANCE_ENABLE
enum dances {
    TD_SHFT_CAPS,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
#    define CK_LSFT TD(TD_SHFT_CAPS)
#else
#    define CK_LSFT KC_LSFT
#endif

// Some defines for the keys below
#define CK_ESC1 LT(2, KC_ESC)
#define CK_BSPC MT(MOD_LGUI, KC_BSPC)
#define CK_DEL1 MT(MOD_LCTL, KC_DEL)
#define CK_DEL2 MT(MOD_RCTL, KC_DEL)
#define CK_ENT1 LT(1, KC_ENT)
#define CK_ESC2 MT(MOD_RALT, KC_ESC)
#define CK_SPC1 LT(2, KC_SPC)
#define CK_ENT2 LT(1, KC_ENT)
#define CK_SPC2 LT(2, KC_SPC)
#define CK_ARNG MT(MOD_RALT, SE_ARNG)
#define CK_ADIA MT(MOD_RGUI, SE_ADIA)
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_TAB MT(MOD_LALT, KC_TAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BkSp |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|   <   |    |   ¨   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |  '   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  Del | Cmd  |  ↲   | /   ⎵   /       \  ↲   \  |  ⎵   | Esc  | Del  |
 *                   | Ctrl |      | LOWER|/ RAISE /         \ LOWER\ | RAISE| RAlt | Ctrl |
 *                   `----------------------------'           '------''--------------------'
 */

 [0] = LAYOUT(
  CK_ESC1,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS,
   CK_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CK_ARNG,
  CK_BSPC,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, CK_ADIA,
  CK_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, SE_LABK,  SE_DIAE, KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, CK_QUOT,
                          CK_DEL1, KC_MYCM, CK_ENT1, CK_SPC1,  CK_ENT2, CK_SPC2, CK_ESC2, CK_DEL2
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  §   |  ©   |  @   |  £   |  $   |  ∞   |                    |      |  |   |  [   |  ]   |  ≈   |  ±   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ´   |  •   |  Ω   |  É   |  ®   |  †   |                    |  µ   |  Ü   |  ı   |  Œ   |  π   |  ˙   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ≥   | Apple|  ß   |  ∂   |  ƒ   |  ¸   |-------.    ,-------|  ˛   |  √   |  ª   |  ﬁ  |  Ø   |  Æ   |
 * |------+------+------+------+------+------|   ´   |    |   ~   |------+------+------+------+------+------|
 * |  ≤   |  ÷   |      |  Ç   |  ‹   |  ›   |-------|    |-------|  ‘   |  ’   |  ‚   |  …   |  –   |  ™   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      | BkSp |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[1] = LAYOUT(
  SE_SECT, SE_COPY,   SE_AT,  SE_PND,  SE_DLR, SE_INFN,                   _______, SE_PIPE, SE_LBRC, SE_RBRC, SE_AEQL, SE_PLMN,
  SE_ACUT, SE_BULT, SE_OMEG, SE_EACU, SE_REGD, SE_DAGG,                   SE_MICR, SE_UDIA, SE_DLSI,   SE_OE,   SE_PI, SE_DOTA,
  SE_GTEQ, SE_APPL,   SE_SS, SE_PDIF, SE_FHK,  SE_CEDL,                   SE_OGON, SE_SQRT, SE_FORD,   SE_FI, SE_OSTR, SE_AE,
  SE_LTEQ,  SE_DIV, _______, SE_CCED, SE_LSAQ, SE_RSAQ, SE_RABK, SE_TILD, SE_LSQU, SE_RSQU, SE_SLQU, SE_ELLP, SE_NDSH, SE_TM,
                             _______, _______, _______, _______, _______, _______, _______, KC_BSPC
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      | Mute |      |                    | Home | PgUp |  ↑   | PgDn | End  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Stop | Play | VolUp| BriUp|-------.    ,-------| <==  |  ←   |  ↓   |  →   | ==>  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | Prev | Next | VolDn| BriDn|-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[2] = LAYOUT(
  KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, KC_MUTE, _______,                   KC_HOME, KC_PGUP,   KC_UP, KC_PGDN,  KC_END, _______,
  _______, _______, KC_MSTP, KC_MPLY, KC_VOLU, KC_BRIU,                   _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  _______, _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_BRID, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  Win |      |      |RESET |System|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Power |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |Sleep |      |      |      |      |      |-------|    |-------| NKRO |  Mac |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [3] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, CG_NORM, XXXXXXX, XXXXXXX, RESET,   CG_TOGG,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_PWR,  AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, AG_TOGG,                   XXXXXXX, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_SLEP, XXXXXXX, XXXXXXX,KC_CLEAR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, CG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, 1, 2, 3); }

#ifdef OLED_ENABLE
#    define KEYLOG_LEN 6
char     keylog_str[KEYLOG_LEN] = {};
uint32_t log_timer              = 0;
// clang-format off
const char code_to_name[256] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  15,  29, '_', '+', '=', 157,  // 2x
     96,  39,'\'', 159, 158,  21, ',', '.', '-', 190,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,  // 3x
    0xDB,0xDC,0xDD,0xDE,0XDF,  0, 'P',  23,  19, 127,  17,  30,  16,  16,  31,  26,  // 4x
     27,  25,  24, 'N', '/', '*', '-', '+',  23, '1', '2', '3', '4', '5', '6', '7',  // 5x
    '8', '9', '0', '.','\\', 'A',   0, '=', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
     14,  13, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ',   0, ' ', ' ', ' ',  14,  13,  16,  17, ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
     15, 190, 191, 189,  15, 190, 191, 189, ' ', ' ', ' ', ' ', ' ',  24,  26,  24,  // Ex
     25,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,  24,  25,  27,  26, ' ', ' ', ' '   // Fx
};
// clang-format on

#    ifdef WPM_ENABLE
// WPM-responsive animation stuff here
#        define OLED_SLEEP_FRAMES 2
#        define OLED_SLEEP_SPEED 10  // below this wpm value your animation will idle
#        define OLED_WAKE_FRAMES 2                // uncomment if >1
#        define OLED_WAKE_SPEED OLED_SLEEP_SPEED  // below this wpm value your animation will idle
#        define OLED_KAKI_FRAMES 3
#        define OLED_KAKI_SPEED 30  // above this wpm value typing animation to trigger
#        define OLED_ANIM_SIZE 128 // number of bytes in array, minimize for adequate firmware size, max is 1024
#        define OLED_ANIM_MAX_FRAMES 3

#        if (OLED_SLEEP_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_WAKE_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_KAKI_FRAMES > OLED_ANIM_MAX_FRAMES)
#            error frame size too large
#        endif

static uint8_t  animation_frame     = 0;
static uint8_t  animation_type      = 0;
static uint16_t anim_frame_duration = 500;
static uint32_t anim_timer          = 0;

void render_kitty(void) {
    // Images credit j-inc(/James Incandenza) and pixelbenny.
    // Credit to obosob for initial animation approach.
    // heavily modified by @drashna because he's a glutton for punishment
    // modified again by @janlindblom for no particular reason

    // clang-format off
    static const char PROGMEM animation[3][OLED_ANIM_MAX_FRAMES][OLED_ANIM_SIZE] = {
        // sleep frames
        {
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
                    0xa8, 0x48, 0xa8, 0x18, 0x08, 0x00, 0x00, 0x00,
                    0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03,
                    0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x80,
                    0x44, 0x84, 0x06, 0x05, 0x04, 0x80, 0x40, 0x20,
                    0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20,
                    0x18, 0x04, 0x04, 0x02, 0x7a, 0x86, 0x01, 0x80,
                    0x80, 0x01, 0x03, 0x05, 0x07, 0x01, 0x00, 0x00,
                    0x80, 0x83, 0x45, 0xfa, 0x3c, 0xe0, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08,
                    0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28,
                    0x28, 0x29, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39,
                    0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x22, 0x22, 0x3a, 0x2a, 0x26, 0x22, 0x80, 0xc0,
                    0x80, 0x00, 0x24, 0x34, 0x2c, 0xe4, 0x60, 0x10,
                    0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38,
                    0x04, 0x02, 0x02, 0x01, 0x79, 0x87, 0x01, 0x80,
                    0x81, 0x83, 0x05, 0x05, 0x03, 0x01, 0x00, 0x00,
                    0x80, 0x43, 0x05, 0xfa, 0x3c, 0xe0, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08,
                    0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28,
                    0x28, 0x28, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39,
                    0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00
            }
        },
        // wake frames
        {
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80,
                    0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x7f, 0x80, 0x40, 0x40, 0x5c, 0x00, 0x01,
                    0x41, 0x01, 0x00, 0x5c, 0x40, 0x40, 0x80, 0x7f,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x00,
                    0x80, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10,
                    0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80,
                    0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x7f, 0x90, 0x12, 0x0a, 0x02, 0xf4, 0x09,
                    0x0d, 0xf1, 0x04, 0x02, 0x0a, 0x12, 0x90, 0x7f,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x01,
                    0x81, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10,
                    0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08
            }
        },
        // kaki frames
        {
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40,
                    0x80, 0x80, 0x80, 0x00, 0xfc, 0x84, 0x08, 0x08,
                    0x10, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x60,
                    0x80, 0x00, 0x00, 0x91, 0xa1, 0x80, 0x00, 0x00,
                    0x22, 0x84, 0x40, 0x50, 0x48, 0xc1, 0x3e, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x41, 0x82, 0xe2, 0x12, 0x0a, 0x06, 0x00,
                    0x80, 0x88, 0x4f, 0x02, 0x22, 0xe2, 0x9f, 0x40,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10,
                    0x14, 0x14, 0x1f, 0x1a, 0x0a, 0x0a, 0x04, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0xf0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x06, 0x1a, 0x22, 0xc2, 0x04, 0x04,
                    0x04, 0x07, 0x00, 0xc0, 0x20, 0x10, 0x80, 0x80,
                    0x01, 0x01, 0x02, 0xfc, 0xfe, 0x02, 0x3c, 0x20,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d,
                    0x55, 0x50, 0x94, 0xf0, 0x10, 0x09, 0x08, 0x00,
                    0x80, 0x00, 0x06, 0x09, 0x1b, 0xee, 0x00, 0x00,
                    0x00, 0x00, 0x81, 0xfe, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c,
                    0x14, 0x16, 0x15, 0x14, 0x14, 0x14, 0x14, 0x08
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x80, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x20, 0x40,
                    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x01,
                    0x02, 0x04, 0x04, 0x03, 0x80, 0x40, 0x40, 0x20,
                    0x00, 0x01, 0x02, 0x8c, 0x70, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d,
                    0x55, 0x50, 0x94, 0xf0, 0x10, 0x0a, 0x0e, 0x1d,
                    0x95, 0x24, 0x24, 0x27, 0x13, 0xe1, 0x01, 0x01,
                    0x01, 0x01, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00
                ,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c,
                    0x14, 0x14, 0x17, 0x14, 0x14, 0x14, 0x14, 0x08
            }
        }
    };
    // clang-format on

    void animation_phase(void) {
        if (get_current_wpm() <= OLED_SLEEP_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_SLEEP_FRAMES;
            animation_type      = 0;
            anim_frame_duration = 500;
        } else if (get_current_wpm() > OLED_WAKE_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_WAKE_FRAMES;
            animation_type      = 1;
            anim_frame_duration = 800;
        } else if (get_current_wpm() >= OLED_KAKI_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_KAKI_FRAMES;
            animation_type      = 2;
            anim_frame_duration = 500;
        }
    }

    oled_write_raw_P(animation[animation_type][animation_frame], OLED_ANIM_SIZE);

    if (timer_elapsed32(anim_timer) > anim_frame_duration) {
        anim_timer = timer_read32();
        animation_phase();
    }
}

void render_wpm_graph(uint8_t max_lines_graph, uint8_t vertical_offset) {
    static uint16_t timer   = 0;
    static uint8_t  x       = OLED_DISPLAY_HEIGHT - 1;
    uint8_t         currwpm = get_current_wpm();
    float           max_wpm = OLED_WPM_GRAPH_MAX_WPM;

    if (timer_elapsed(timer) > OLED_WPM_GRAPH_REFRESH_INTERVAL) {                   // check if it's been long enough before refreshing graph
        x = (max_lines_graph - 1) - ((currwpm / max_wpm) * (max_lines_graph - 1));  // main calculation to plot graph line
        for (uint8_t i = 0; i <= OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS - 1; i++) {    // first draw actual value line
            oled_write_pixel(3, x + i + vertical_offset, true);
        }
#        ifdef OLED_WPM_GRAPH_VERTICAL_LINE
        static uint8_t vert_count = 0;
        if (vert_count == OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL) {
            vert_count = 0;
            while (x <= (max_lines_graph - 1)) {
                oled_write_pixel(3, x + vertical_offset, true);
                x++;
            }
        } else {
            for (uint8_t i = (max_lines_graph - 1); i > x; i--) {
                if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                    oled_write_pixel(3, i + vertical_offset, true);
                }
            }
            vert_count++;
        }
#        else
        for (int i = (max_lines_graph - 1); i > x; i--) {
            if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                oled_write_pixel(3, i + vertical_offset, true);
            }
        }
#        endif
        oled_pan(false);  // then move the entire graph one pixel to the right
        timer = timer_read();  // refresh the timer for the next iteration
    }
}
#    else
void render_kitty(void) { return; }
void render_wpm_graph(uint8_t max_lines_graph, uint8_t vertical_offset) { return; }
#    endif // WPM_ENABLE

void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode &= 0xFF;
    }
    if (keycode > 0xFF) {
        return;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;
    log_timer                  = timer_read32();
}

void update_log(void) {
    if (timer_elapsed32(log_timer) > 750) {
        add_keylog(0, NULL);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

const char *read_logo(void);

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("BASE "), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("ADJST"), false);
            break;
    }
}

void oled_render_keylock_state(led_t led_state) {
    oled_write_P(PSTR("Locks"), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_P(PSTR("S"), led_state.scroll_lock);
    oled_write_P(PSTR("\n"), false);
}

void oled_render_mod_state(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Mods"), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("\n"), false);
}

char mode_icon[11];

char *read_mode_icon(bool swap, bool nkro) {
    // clang-format off
    static char logo[][4][3] = {
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x4E, 0x4B, 0}, {0x52, 0x4F, 0}}, {{0x20, 0x20, 0}, {0x20, 0x20, 0}}};
    // clang-format on
    uint8_t     swap_index   = 0;
    uint8_t     nkro_index   = 3;
    if (swap) {
        swap_index = 1;
    }
    if (nkro) {
        nkro_index = 2;
    }
    snprintf(mode_icon, sizeof(mode_icon), "%s %s%s %s", logo[swap_index][0], logo[nkro_index][0], logo[swap_index][1], logo[nkro_index][1]);
    return mode_icon;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        update_log();
#    ifdef WPM_ENABLE
        render_kitty();
        oled_set_cursor(0, 4);
#    endif
        oled_write(read_mode_icon(keymap_config.swap_lctl_lgui, keymap_config.nkro), false);
        oled_render_layer_state();
        oled_render_mod_state(get_mods());
        oled_write_P(PSTR("\n"), false);
        oled_render_keylock_state(host_keyboard_led_state());
        oled_write_ln(keylog_str, false);
    } else {
        oled_write(read_logo(), false);
    }
    return true;
}
#endif  // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        add_keylog(keycode, record);
    }
#endif
    switch (keycode) {
        case KC_MYCM:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui == true) {
                    register_code(KC_LCMD);
                } else {
                    register_code(KC_LWIN);
                }
            } else {
                if (keymap_config.swap_lctl_lgui == true) {
                    unregister_code(KC_LCMD);
                } else {
                    unregister_code(KC_LWIN);
                }
            }
            return false;
        default:
            break;
    }
    return true;
}
