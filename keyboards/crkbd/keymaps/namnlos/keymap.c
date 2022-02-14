/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Jan Lindblom (@janlindblom)

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
// Load Swedish keys and sendstring stuff.
#include "namnlos.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#ifdef RGB_MATRIX_ENABLE
typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_change : 1;
        bool     rgb_matrix_idle_anim : 1;
        uint8_t  rgb_matrix_active_mode : 4;
        uint8_t  rgb_matrix_idle_mode : 4;
        uint8_t  rgb_matrix_active_speed : 8;
        uint8_t  rgb_matrix_idle_speed : 8;
        uint16_t rgb_matrix_idle_timeout : 16;
    };
} user_config_t;

user_config_t   user_config;
static uint32_t hypno_timer;
#endif

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
#define CK_ESC LT(_RAISE, KC_ESC)
#define CK_BSPC MT(MOD_LCTL, KC_BSPC)
#define CK_DEL MT(MOD_LGUI, KC_DEL)
#define CK_SPCL LT(_LOWER, KC_SPC)
#define CK_ENTL MT(MOD_LALT, KC_ENT)
#define CK_ENT2 LT(_RAISE, KC_ENT)
#define CK_SPC2 MT(MOD_RALT, KC_SPC) // LT(_LOWER, KC_SPC)
#define CK_TAB LT(_LOWER, KC_TAB)    // MT(MOD_RALT, KC_TAB)
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
  // clang-format off
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CK_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  SE_ARNG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CK_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, SE_ODIA, CK_ADIA,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CK_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, SE_COMM,  SE_DOT, SE_MINS, CK_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           CK_DEL, CK_ENTL, CK_SPCL,    CK_ENT2, CK_SPC2, CK_TAB
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   SK_NOT_EQL, SE_EXLM,   SE_AT, SE_LCBR, SE_RCBR, SE_PIPE,                       SE_PND, SE_EURO, SE_QUES, SE_SECT, SE_CURR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       SK_LEQ, SE_HASH,  SE_DLR, SE_LPRN, SE_RPRN,  SE_GRV,                      SE_PLUS, SE_MINS, SE_SLSH, SE_ASTR, SE_PERC,CK_EMDASH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       SK_GEQ, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD,                      SE_AMPR,  SE_EQL, SE_SCLN, SE_COLN, SE_BSLS,CK_ENDASH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SE_LABK, SE_RABK, _______,    _______, _______,  SE_DQUO
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      SE_SECT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
  [_ADJST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       QK_RBT, QK_MAKE, XXXXXXX, CG_NORM, XXXXXXX, XXXXXXX,                      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CG_SWAP,  CK_OBI, XXXXXXX,                      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      EH_LEFT, XXXXXXX, XXXXXXX, CG_TOGG,  CK_OBD, QK_BOOT,                      NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EH_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
    // clang-format on
};

#ifdef OLED_ENABLE
#    define OLED_SPACE " "

oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

#    ifdef RGB_MATRIX_ENABLE
const char* rgb_matrix_anim_oled_text(uint8_t mode) {
    switch (mode) {
        // case RGB_MATRIX_TYPING_HEATMAP:
        //     return PSTR("Heat ");
        // case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
        //     return PSTR("Nexus");
        case RGB_MATRIX_SOLID_COLOR:
            return PSTR("Solid");
        // case RGB_MATRIX_CYCLE_ALL:
        //     return PSTR("Cycle");
        // case RGB_MATRIX_RAINBOW_PINWHEELS:
        //     return PSTR("Wheel");
        // case RGB_MATRIX_CYCLE_LEFT_RIGHT:
        //     return PSTR("Wave ");
        default:
            return PSTR("");
    }
}
#    endif

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
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
#endif
    return state;
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJST));
#endif
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJST);
}

bool led_update_keymap(led_t led_state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(4, led_state.caps_lock);
#endif
    return true;
}

#ifdef RGB_MATRIX_ENABLE
extern led_config_t g_led_config;
void                rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_type) {
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
    if (user_config.rgb_layer_change && rgb_matrix_config.enable && (!user_config.rgb_matrix_idle_anim || rgb_matrix_get_mode() != user_config.rgb_matrix_idle_mode)) {
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

void matrix_scan_keymap(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }
    matrix_scan_rgb();
}

void eeconfig_init_keymap(void) {
    rgb_matrix_mode_noeeprom(user_config.rgb_matrix_active_mode);
}
#endif

void suspend_power_down_keymap(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
}

void suspend_wakeup_init_keymap(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
}

void keyboard_post_init_keymap(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef RGBLIGHT_LAYERS
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#    endif
    rgblight_enable();
#endif
#ifdef RGB_MATRIX_ENABLE
    user_config.raw = eeconfig_read_user();
    rgb_matrix_set_defaults();
    rgb_matrix_enable_noeeprom();
#endif
    return;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
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

void render_keyboard_logo(void) {
#if (OLED_COUNT == 2)
    if (is_keyboard_master()) {
        static const char PROGMEM corne_logo[] = {
            // clang-format off
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00,
        0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x00, 0x00, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x01, 0xf0,
        0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0x80, 0x80, 0x80, 0xc0, 0xf0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07,
        0x03, 0x03, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00
            // clang-format on
        };
        oled_set_cursor(0, 0);
        oled_write_raw_P(corne_logo, sizeof(corne_logo));
    }
#endif
}
