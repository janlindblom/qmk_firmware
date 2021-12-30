#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _MOVE,
  _ADJUST,
};

// Custom keycodes for send_string-stuff.
enum custom_keycodes {
    SK_NOT_EQL = SAFE_RANGE,
    SK_LEQ,
    SK_GEQ,
};

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
#define CK_ESC LT(_RAISE, KC_ESC)
#define CK_BSPC MT(MOD_LCTL, KC_BSPC)
#define CK_DEL MT(MOD_LGUI, KC_DEL)
#define CK_ENT1 MT(MOD_LALT, KC_ENT)
#define CK_SPC1 LT(_LOWER, KC_SPC)
#define CK_ENT2 LT(_LOWER, KC_ENT)
#define CK_SPC2 LT(_RAISE, KC_SPC)
#define CK_TAB MT(MOD_RALT, KC_TAB)
#define CK_ADIA MT(MOD_RCTL, SE_ADIA)
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_BSP2 LT(_MOVE, KC_BSPC)

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

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BkSp |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------| Paste |    | PgDn  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |  '   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  Del | ↲/ALT|  ⎵   | /   ⎋   /       \  ↲   \  |  ⎵   |  ⭾  | BkSp |
 *                   |  GUI |      | LOWER|/ RAISE /         \ LOWER\ | RAISE| AltGr|      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  SE_SECT,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS,
  CK_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG,
  CK_BSPC,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA,
  CK_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, CK_PSTE,  KC_PGDN,  KC_N,    KC_M,    CK_COMM, CK_DOT,  CK_DASH, CK_QUOT,
                           CK_DEL, CK_ENT1, CK_SPC1,  CK_ESC,  CK_ENT2,  CK_SPC2, CK_TAB,  CK_BSP2
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ≠   |  !   |  @   |  {   |  }   |  |   |                    |  £   |  €   |  ?   |  §   |  ¤   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ≤   |  #   |  $   |  (   |  )   |  `   |-------.    ,-------|  +   |  -   |  /   |  *   |  %   |  —   |
 * |------+------+------+------+------+------|  Copy |    | PgUp  |------+------+------+------+------+------|
 * |  ≥   |  %   |  ^   |  [   |  ]   |  ~   |-------|    |-------|  &   |  =   |      |      |  \   |  –   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  <   |  >   |  ;   | /   =   /       \   =  \  |  ;   |      | DEL  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                   SE_PND,  SE_EURO, SE_QUES, SE_SECT, SE_CURR, _______,
  SK_LEQ,     SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,                   SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC, CK_EMDASH,
  SK_GEQ,     SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD, CK_COPY, KC_PGUP, SE_AMPR, SE_EQL,  _______, _______, KC_RCBR, KC_PIPE,
                                SE_LABK, SE_RABK, SE_SCLN, SE_EQL,  SE_EQL,  SE_SCLN, _______, KC_DEL
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down | Up   |Right | PgUp |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------| <==  | ==>  | Home | End  | PgDn |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Menu |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MPLY,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,   KC_PGUP, KC_VOLU,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN, KC_VOLD,
                             KC_MENU, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_MOVE] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_R, KC_WH_U,                   XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, KC_BTN1, KC_BTN2, _______,  _______, _______, _______ \
  )
};

#ifdef WPM_ENABLE
bool wpm_keycode_user(uint16_t keycode) {
    return true;
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _MOVE);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE
#    ifdef WPM_ENABLE
// WPM-responsive animation stuff here
#        define FRAMES 2
#        define SLEEP_SPEED 10  // below this wpm value your animation will idle
#        define KAKI_SPEED 30  // above this wpm value typing animation to triggere
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
#ifdef WPM_ENABLE
        return OLED_ROTATION_270;
#else
        return OLED_ROTATION_180;
#endif
    }
    return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("LAYR:"), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("BASE "), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case _MOVE:
            oled_write_ln_P(PSTR("MOVE "), false);
            break;
        case _ADJUST:
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

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_mod_state(get_mods());
        oled_render_keylock_state(host_keyboard_leds());
        oled_advance_page(true);
    } else {
#    ifdef WPM_ENABLE
        oled_set_cursor(0, 8);
        render_kitty();
        oled_set_cursor(0, 13);
        uint8_t n = get_current_wpm();
        char    wpm_counter[4];
        wpm_counter[3] = '\0';
        wpm_counter[2] = '0' + n % 10;
        wpm_counter[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
        wpm_counter[0] = n / 10 ? '0' + n / 10 : ' ';
        oled_write_P(PSTR("WPM: "), false);
        oled_write(wpm_counter, false);
#    else
        oled_render_logo();
#    endif
    }
}
#endif // OLED_ENABLE

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
}
