/**
 * @file keymap.c
 * @author Jan Lindblom (jan@robotika.ax)
 * @brief Custom nordic/Swedish keymap with OLED support
 * @version 0.1
 * @date 2021-07-25
 */

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#define BASE 0  // default layer
#define SYMB 1  // symbols
#define NUMB 2  // numbers etc
#define MOVE 3  // motion

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

// Some defines for the keys below
#define CK_ESC LT(NUMB, KC_ESC)
#define CK_BSPC MT(MOD_LCTL, KC_BSPC)
#define CK_DEL MT(MOD_LGUI, KC_DEL)
#define CK_ENT1 MT(MOD_LALT, KC_ENT)
#define CK_SPC1 LT(SYMB, KC_SPC)
#define CK_ENT2 LT(SYMB, KC_ENT)
#define CK_SPC2 LT(NUMB, KC_SPC)
#define CK_TAB MT(MOD_RALT, KC_TAB)
#define CK_ADIA MT(MOD_RCTL, SE_ADIA)
#define CK_QUOT MT(MOD_RSFT, SE_QUOT)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_BSP2 LT(MOVE, KC_BSPC)

#define EM_DASH 0x2014
#define EN_DASH 0x2013

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
     *
     * ,--------------------------------------------.                         ,-------------------------------------------.
     * | NUMB/⎋  |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |   Å    |
     * |---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |Ctrl/BkSp|   A  |   S  |  D   |   F  |   G  |      |           | BkSp |   H  |   J  |   K  |   L  |   Ö  | Ctrl/Ä |
     * |---------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
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
    [BASE] = LAYOUT_gergo(
         CK_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                               KC_Y,    KC_U,   KC_I,     KC_O,    KC_P, SE_ARNG,
        CK_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_TRNS,                           KC_BSPC,   KC_H,    KC_J,   KC_K,     KC_L, SE_ODIA, CK_ADIA,
        CK_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_TRNS, CK_PSTE,         KC_PGDN, KC_EQL,    KC_N,    KC_M, CK_COMM,  CK_DOT, CK_DASH, CK_QUOT,
                                             CK_DEL, CK_ENT1, CK_SPC1,  CK_ESC,         CK_ENT2, CK_SPC2, CK_TAB, CK_BSP2),
    /* Keymap 1: Symbols layer
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |    ≠   |  !   |  @   |  {   |  }   |  |   |                         |   £  |  €   |  ?   | §/½  |   ¤  |        |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |    ≤   |  #   |  $   |  (   |  )   |  `   |      |           |   ”  |   +  |  -   |  /   |  *   |  %   |   —    |
     * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
     * |    ≥   |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |   &  |  =   |  ,   |  :   |  \   |   –    |
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
        SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                                              SE_PND, SE_EURO, SE_QUES, SE_SECT, SE_CURR, KC_TRNS,
            SK_LEQ, SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV, SE_SECT,                           SE_DQUO, SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC, UC(EM_DASH),
            SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD, SE_CURR, CK_COPY,         KC_PGUP, KC_TRNS, SE_AMPR, SE_EQL, KC_COMM, SE_COLN, SE_BSLS, UC(EN_DASH),
                                                SE_LABK, SE_RABK, SE_SCLN, SE_EQL,         SE_EQL, SE_SCLN, KC_TRNS, KC_DEL),
    /* Keymap 2: Pad/Function layer
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   |   ⏯   |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |   F1   |  F2  |  F3  |  F4  |  F5  | F6   |      |           |      | LEFT | DOWN |  UP  | RIGHT|   ⇞  |   🕪    |
     * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
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
    [NUMB] = LAYOUT_gergo(
        KC_TRNS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MPLY,
        KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                           KC_TRNS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP, KC_VOLU,
        KC_TRNS,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  CK_CUT,         KC_TRNS, KC_TRNS, CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN, KC_VOLD,
                                            KC_MENU, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    /* Mouse control
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |        |      |      |  su  |      |      |                         |      |      |  up  |      |      |        |
     * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
     * |        |      |  sl  |  sd  |  sr  |  su  |      |           |      |      |  le  |  dn  |  ri  |      |        |
     * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
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

    [MOVE] = LAYOUT_gergo(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_U, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_WH_U, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

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
// clang-format on

#ifdef OLED_ENABLE

#define OLED_SPACE " "

// This part is mainly adapted from users/drashna/oled_stuff.c
#define OLED_RENDER_LAYER_NAME  "\nLAYER"
#define OLED_RENDER_LAYER_BASE  "Base "
#define OLED_RENDER_LAYER_LOWER "Lower"
#define OLED_RENDER_LAYER_RAISE "Raise"
#define OLED_RENDER_LAYER_MOVE  "Move "

#define OLED_RENDER_LOCK_NAME "\nLOCK"
#define OLED_RENDER_LOCK_NUML "Num "
#define OLED_RENDER_LOCK_CAPS "Caps"
#define OLED_RENDER_LOCK_SCLK "Scrl"

#define OLED_RENDER_MODS_NAME "\nMODS "
#define OLED_RENDER_MODS_SFT  "Shift"
#define OLED_RENDER_MODS_CTL  "Ctrl "
#define OLED_RENDER_MODS_ALT  "Alt  "
#define OLED_RENDER_MODS_GUI  "GUI  "

void render_layer_state(void) {
    oled_write_P(PSTR(OLED_RENDER_LAYER_NAME), false);
    if (layer_state_is(NUMB)) {
        oled_write_P(PSTR(OLED_RENDER_LAYER_RAISE), false);
    } else if (layer_state_is(SYMB)) {
        oled_write_P(PSTR(OLED_RENDER_LAYER_LOWER), false);
    } else if (layer_state_is(MOVE)) {
        oled_write_P(PSTR(OLED_RENDER_LAYER_MOVE), false);
    } else {
        oled_write_P(PSTR(OLED_RENDER_LAYER_BASE), false);
    }
    //oled_write_P(PSTR(OLED_SPACE), false);
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
    oled_write_P(PSTR(OLED_SPACE), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR(OLED_SPACE), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_P(PSTR(OLED_SPACE), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
    oled_advance_page(true);
}

void render_mod_status(uint8_t modifiers) {
    static const char PROGMEM mod_status[5][3] = {{0xD5, 0xD6, 0}, {0xDB, 0xDC, 0}, {0xD9, 0xDA, 0}, {0xD7, 0xD8, 0}, {0xD7, 0xD8, 0}};
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
    oled_write_P(mod_status[0], (modifiers & MOD_MASK_SHIFT));
    oled_write_P(mod_status[!keymap_config.swap_lctl_lgui ? 3 : 4], (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR(OLED_SPACE), false);
    oled_write_P(mod_status[2], (modifiers & MOD_MASK_ALT));
    oled_write_P(mod_status[1], (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(OLED_SPACE), false);
}

void render_status(void) {
    render_layer_state();
    render_mod_status(get_mods());
    render_keylock_status(host_keyboard_leds());
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_90;
}

void oled_task_user(void) {
    static const char PROGMEM font_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0
    };
    oled_write_P(font_logo, false);

    render_status();
}
//     static const char PROGMEM font_logo[] = {
//         0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//         0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
// 		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
// 	oled_write_P(font_logo, false);

// }
#endif
