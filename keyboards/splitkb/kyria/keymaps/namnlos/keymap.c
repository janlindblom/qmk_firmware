/* Copyright 2021 Jan Lindblom <jan@namnlos.io>
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
#include <math.h>

enum layers {
    _BASE = 0,
    _SYMB = 1,
    _NUM = 2,
    _MOVE = 3,
    _ADJUST = 4,
};

// Custom keycodes for send_string-stuff.
enum custom_keycodes {
    SK_NOT_EQL = SAFE_RANGE,
    SK_LEQ,
    SK_GEQ,
};

// Custom send_string keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    return true;
};

#define NUM      MO(_NUM)
#define SYM      MO(_SYMB)
#define NAV      MO(_MOVE)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

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
#define CK_LSFT TD(TD_SHFT_CAPS)
#define CK_COMM TD(TD_COM_SCL)
#define CK_DOT TD(TD_DOT_COL)
#define CK_DASH TD(TD_DASH_USCR)
#else
#define CK_LSFT KC_LSFT
#define CK_COMM KC_COMM
#define CK_DOT KC_DOT
#define CK_DASH SE_MINS
#endif

#define CK_ESC LT(_NUM, KC_ESC)
#define CK_BSPC MT(MOD_LCTL, KC_BSPC)
#define CK_DEL MT(MOD_LGUI, KC_DEL)
#define CK_ENT1 MT(MOD_LALT, KC_ENT)
#define CK_SPC1 LT(_SYMB, KC_SPC)
#define CK_ENT2 LT(_SYMB, KC_ENT)
#define CK_SPC2 LT(_NUM, KC_SPC)
#define CK_TAB MT(MOD_RALT, KC_TAB)
#define CK_ADIA MT(MOD_RCTL, SE_ADIA)
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_BSP2 LT(_MOVE, KC_BSPC)

#define EM_DASH 0x2014
#define EN_DASH 0x2013

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |Esc/NUM |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Bsp|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | ⇧/Caps |   Z  |   X  |   C  |   V  |   B  | Tab  |Paste |  | PgDn | Bspc |   N  |   M  | ,  ; | .  : | -  _ |  '  *  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  Adj | Del  | LAlt/| Space| Esc  |  | Enter| Space| Tab  | Bspc | Bspc |
 *                        |  ust | GUI  | Enter| SYMB | NUM  |  | SYMB | NUM  | AltGr|      | MOVE |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
     CK_ESC , KC_Q ,  KC_W   ,  KC_E ,   KC_R,   KC_T ,                                         KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , SE_ARNG,
     CK_BSPC, KC_A ,  KC_S   ,  KC_D ,   KC_F,   KC_G ,                                         KC_H,   KC_J ,  KC_K ,   KC_L ,SE_ODIA, CK_ADIA,
     CK_LSFT, KC_Z ,  KC_X   ,  KC_C ,   KC_V,   KC_B ,  KC_TAB,CK_PSTE,     KC_PGDN, KC_BSPC,  KC_N,   KC_M ,CK_COMM,  CK_DOT,CK_DASH, CK_QUOT,
                               ADJUST, CK_DEL, CK_ENT1, CK_SPC1, CK_ESC,     CK_ENT2, CK_SPC2,CK_TAB, CK_BSP2,CK_BSP2
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
    [_SYMB] = LAYOUT(
   SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                                      SE_PND, SE_EURO, SE_QUES, SE_SECT, SE_CURR, KC_TRNS,
       SK_LEQ, SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,                                     SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC, UC(EM_DASH),
       SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD, _______, CK_COPY, KC_PGUP, SE_DQUO, SE_AMPR, SE_EQL , KC_COMM, SE_COLN, SE_BSLS, UC(EN_DASH),
                                 SE_LABK, SE_RABK, _______, _______, _______, _______, _______, _______, KC_DEL , _______
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
    [_NUM] = LAYOUT(
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
    [_MOVE] = LAYOUT(
      _______, _______, _______, KC_WH_U, _______, _______,                                    _______, _______, KC_MS_U, _______,  _______, _______,
      _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______,                                    _______, KC_MS_L, KC_MS_D, KC_MS_R,  _______, _______,
      _______, _______, _______, _______, _______, _______,KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______, _______,  _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
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
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};

#ifdef WPM_ENABLE
char wpm_str[10];

bool wpm_keycode_user(uint16_t keycode) {
	return true;
}
#endif

#ifdef OLED_ENABLE
// WPM-responsive animation stuff here
#define IDLE_FRAMES 5
#define IDLE_SPEED 40 // below this wpm value your animation will idle


#define TAP_FRAMES 2
#define TAP_SPEED 60 // above this wpm value typing animation to triggere

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 128 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;

static const int8_t PROGMEM nodes[8][3] = {
    {-16, -16, -16},
    {-16, -16, 16},
    {-16, 16, -16},
    {-16, 16, 16},
    {16, -16, -16},
    {16, -16, 16},
    {16, 16, -16},
    {16, 16, 16}
    };

static const uint8_t edges[12][2] = {
    {0, 1}, {1, 3}, {3, 2},
    {2, 0}, {4, 5}, {5, 7},
    {7, 6}, {6, 4}, {0, 4},
    {1, 5}, {2, 6}, {3, 7}
    };

static void rotate_cube(float angleX, float angleY) {
    float sinX = sin(angleX);
	float cosX = cos(angleX);
	float sinY = sin(angleY);
	float cosY = cos(angleY);
    for (size_t i = 0; i < (sizeof(nodes) / sizeof(nodes[0])); i++) {
        int8_t node[3] = &nodes[i];
        int8_t x = node[0];
		int8_t y = node[1];
		int8_t z = node[2];
		node[0] = x * cosX - z * sinX;
		node[2] = z * cosX + x * sinX;
		z = node[2];
		node[1] = y * cosY - z * sinY;
		node[2] = z * cosY + y * sinY;

        nodes[i] = *node;
    }

}

static void draw_line(int8_t x0, int8_t y0, int8_t x1, int8_t y1) {
    int8_t dx = abs(x1 - x0);
	int8_t dy = abs(y1 - y0);
    int8_t sx = -1;
    int8_t sy = -1;
	if (x0 < x1) {
		sx = 1;
	}
	if (y0 < y1) {
		sy = 1;
	}
	int8_t err = dx - dy;

    do {
        //img.Set(x0, y0, col)
        int8_t e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
    } while (!(x0 == x1 && y0 == y1));
}

static void render_cube(void) {
    rotate_cube(M_PI / 4, atan(sqrt(2)));
    for (uint8_t frame = 0; frame < 360; frame++) {
        for (size_t i = 0; i < (sizeof(edges) / sizeof(edges[0])); i++) {
            uint8_t edge[2] = *edges[i];
			int8_t xy1[2] = *nodes[edge[0]];
			int8_t xy2[2] = *nodes[edge[1]];
			draw_line(xy1[0], xy1[1], xy2[0], xy2[1]);
		}
		rotate_cube(M_PI/180, 0);
	}
}

// Images credit j-inc(/James Incandenza) and pixelbenny. Credit to obosob for initial animation approach.
static void render_anim(void) {
    render_cube();
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x60,
        0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x0c, 0x06, 0x03, 0x81, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x03, 0x06, 0x04, 0x0c, 0x18, 0x10, 0x18, 0x08, 0xf8, 0x00, 0x00, 0x00,
        0x00, 0x3e, 0x23, 0x20, 0x20, 0x20, 0x30, 0x10, 0x10, 0x10, 0x30, 0x21, 0x21, 0x63, 0x43, 0x42,
        0xc0, 0x80, 0x88, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x73, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x05, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x06, 0x04, 0x0c, 0x08, 0x0b, 0x08, 0x00
        },
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x60, 0x30, 0x10, 0x08, 0x04, 0x04, 0x06, 0x01, 0x01, 0x06,
        0x04, 0x0c, 0x08, 0x18, 0x10, 0x30, 0x20, 0x40, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0x00,
        0xe0, 0x98, 0x04, 0x03, 0x01, 0x80, 0x80, 0x80, 0x80, 0x84, 0x86, 0x80, 0x08, 0x18, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x78, 0x87, 0x00, 0x00,
        0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02,
        0x02, 0x02, 0x0e, 0x3e, 0x20, 0x20, 0x20, 0x10, 0x10, 0x18, 0x18, 0x10, 0x10, 0x33, 0x3e, 0x00
        },
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x60,
        0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x0c, 0x06, 0x03, 0x81, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x03, 0x06, 0x04, 0x0c, 0x18, 0x10, 0x18, 0x08, 0xf8, 0x00, 0x00, 0x00,
        0x00, 0x3e, 0x23, 0x20, 0x20, 0x20, 0x30, 0x10, 0x10, 0x10, 0x30, 0x21, 0x21, 0x63, 0x43, 0x42,
        0xc0, 0x80, 0x88, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x73, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x05, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x06, 0x04, 0x0c, 0x08, 0x0b, 0x08, 0x00
        },
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x60, 0x30, 0x10, 0x08, 0x04, 0x04, 0x06, 0x01, 0x01, 0x06,
        0x04, 0x0c, 0x08, 0x18, 0x10, 0x30, 0x20, 0x40, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0x00,
        0xe0, 0x98, 0x04, 0x03, 0x01, 0x80, 0x80, 0x80, 0x80, 0x84, 0x86, 0x80, 0x08, 0x18, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x78, 0x87, 0x00, 0x00,
        0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02,
        0x02, 0x02, 0x0e, 0x3e, 0x20, 0x20, 0x20, 0x10, 0x10, 0x18, 0x18, 0x10, 0x10, 0x33, 0x3e, 0x00
        },
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x60,
        0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x0c, 0x06, 0x03, 0x81, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x03, 0x06, 0x04, 0x0c, 0x18, 0x10, 0x18, 0x08, 0xf8, 0x00, 0x00, 0x00,
        0x00, 0x3e, 0x23, 0x20, 0x20, 0x20, 0x30, 0x10, 0x10, 0x10, 0x30, 0x21, 0x21, 0x63, 0x43, 0x42,
        0xc0, 0x80, 0x88, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x73, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x05, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x06, 0x04, 0x0c, 0x08, 0x0b, 0x08, 0x00
        }
    };
    static const char PROGMEM prep[][ANIM_SIZE] = {
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x30, 0x18, 0x0c, 0x38,
        0x60, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xf8, 0x18, 0x0c, 0x0c, 0x38, 0x0c, 0x06, 0x03, 0x01, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x06, 0x04, 0x08, 0x18, 0x30, 0x18, 0x18, 0xf8, 0x00, 0x00,
        0x00, 0x07, 0x0c, 0x18, 0x18, 0x10, 0x10, 0x10, 0x20, 0x60, 0x61, 0x41, 0x42, 0xc2, 0x86, 0x84,
        0x80, 0x00, 0x00, 0x18, 0x10, 0xfc, 0x02, 0x02, 0x04, 0x1c, 0x00, 0x00, 0x3e, 0xe1, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
        0x01, 0x03, 0x03, 0x02, 0x06, 0x07, 0x06, 0x0c, 0x0c, 0x0c, 0x10, 0x10, 0x30, 0x20, 0x3f, 0x00
        }
    };
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x30, 0x18, 0x0c, 0x38,
        0x60, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xfe, 0xfe, 0x80, 0xc0, 0x60, 0x18, 0x0c, 0x02, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x06, 0x04, 0x08, 0x10, 0x10, 0x18, 0x08, 0xfc, 0x00, 0x00,
        0xf9, 0xff, 0xe3, 0xe0, 0xc0, 0x40, 0x60, 0x20, 0x20, 0x60, 0x41, 0x40, 0xc3, 0x82, 0x86, 0x04,
        0x00, 0x00, 0x00, 0x18, 0x18, 0xfc, 0x06, 0x06, 0x04, 0x38, 0x00, 0x00, 0x1c, 0xe7, 0x00, 0x00,
        0xf0, 0xfc, 0x03, 0x00, 0x01, 0x07, 0x7c, 0x78, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x01, 0x03, 0x02, 0x02, 0x06, 0x07, 0x04, 0x0c, 0x08, 0x08, 0x18, 0x10, 0x30, 0x21, 0x3f, 0x38
        },
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x60, 0x30, 0x18, 0x0c, 0x38,
        0x60, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xe0, 0xf8, 0x04, 0x04, 0x0c, 0x3c, 0x06, 0x03, 0x01, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 0x0c, 0x18, 0x98, 0x08, 0x0c, 0xfc, 0x00, 0x00,
        0x03, 0x07, 0x04, 0x0c, 0x08, 0x08, 0x18, 0x10, 0x10, 0x30, 0x20, 0x20, 0x61, 0x43, 0x43, 0xc2,
        0x80, 0x80, 0x80, 0x8c, 0x80, 0x00, 0x00, 0xe0, 0xf8, 0x7e, 0x3f, 0x1f, 0x1f, 0x7d, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0x70,
        0x30, 0x38, 0x19, 0x0f, 0x1e, 0x1c, 0x79, 0xf8, 0xe8, 0xc4, 0x84, 0x08, 0x08, 0x18, 0x1f, 0x1c
        },
    };

    //assumes 1 frame prep stage
    void animation_phase(void) {
        if(get_current_wpm() <=IDLE_SPEED){
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES-1)-current_idle_frame)], ANIM_SIZE);
         }
         if(get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED){
             oled_write_raw_P(prep[0], ANIM_SIZE);
         }
         if(get_current_wpm() >=TAP_SPEED){
             current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
             oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
         }
    }
    if(get_current_wpm() != 000) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress
        if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

void oled_task_user(void) {
    // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on
    if (is_keyboard_master()) {
        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev 1.4\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Symbol\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Number\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("Move\n"), false);
                break;
            case 4:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ?    PSTR("Num  ") : PSTR("     "), false);
        oled_write_P(led_usb_state.caps_lock ?   PSTR("Caps ") : PSTR("     "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("Scrl ") : PSTR("     "), false);
#    ifdef WPM_ENABLE
        uint8_t n = get_current_wpm();
        wpm_str[3] = '\0';
        wpm_str[2] = '0' + n % 10;
        wpm_str[1] = '0' + (n /= 10) % 10;
        wpm_str[0] = '0' + n / 10 ;
        oled_write_P(PSTR("\nWPM: "), false);
        oled_write(wpm_str, false);
#    endif
    } else {
        // Non-master side
#    ifdef WPM_ENABLE
        render_anim();
#    else
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
}
#endif

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_CYAN}
);
const rgblight_segment_t PROGMEM symb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_GREEN}
);
const rgblight_segment_t PROGMEM move_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_BLUE}
);
const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_PINK}
);
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    symb_layer,
    num_layer,
    move_layer,
    adjust_layer,
    capslock_layer
);
#endif

layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
#endif
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYMB));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, _MOVE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
#endif
    return state;
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_enable();
#endif
    return;
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(5, led_state.caps_lock);
#endif
    return true;
}
