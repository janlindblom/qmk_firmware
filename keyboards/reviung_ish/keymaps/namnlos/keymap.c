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
#include "namnlos.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

extern keymap_config_t keymap_config;

// Tap Dance definitions
#ifdef TAP_DANCE_ENABLE
enum dances {
    TD_CAPS,
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock, Thrice for Caps Word
    // clang-format off
    [TD_CAPS] = ACTION_TAP_DANCE_TRIPLE(KC_LSFT, KC_CAPS, CW_TOGG)
    // clang-format on
};

#    define CK_LSFT TD(TD_CAPS)
#else
#    define CK_LSFT KC_LSFT
#endif

// Some defines for the keys below
#define CK_ESC LT(_RAISE, KC_ESC)
#define CK_BSPC LCTL_T(KC_BSPC)
#define CK_ENT1 LT(_LOWER, KC_ENT)
#define CK_DEL LALT_T(KC_DEL)
#define CK_ENT2 LT(_RAISE, KC_ENT)
#define CK_TAB RALT_T(KC_TAB)
#define CK_ADIA RCTL_T(SE_ADIA)
#define CK_QUOT RSFT_T(SE_QUOT)
#define CK_SPC LGUI_T(KC_SPC)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
#define CK_CUT LCTL(KC_X)
#define CK_COPY LCTL(KC_C)
#define CK_PSTE LCTL(KC_V)
#define CK_ADJST MO(_ADJST)

#ifdef UNICODEMAP_ENABLE
enum unicode_names {
    NDASH,
    MDASH,
};

const uint32_t PROGMEM unicode_map[] = {
    [NDASH] = 0x2013,
    [MDASH] = 0x2014,
};
// Unicode keys
#    define K_NDASH X(NDASH)
#    define K_MDASH X(MDASH)
#elif UNICODE_ENABLE
#    define K_NDASH UC(0x2013)
#    define K_MDASH UC(0x2014)
#else
#    define K_NDASH KC_TRNS
#    define K_MDASH KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_BASE] = LAYOUT(
        SE_SECT,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     SE_PLUS,
        CK_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     SE_ARNG,
        CK_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     CK_PSTE,  KC_H,     KC_J,     KC_K,     KC_L,     SE_ODIA,  CK_ADIA,
        CK_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_N,     KC_M,     SE_COMM,  SE_DOT,   SE_MINS,  CK_QUOT,
                                      KC_LGUI,  CK_DEL,   CK_ENT1,  CK_SPC,   CK_ENT2,  CK_TAB,   CK_ADJST
    ),
     [_LOWER] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
      SK_NOT_EQL, SE_EXLM,  SE_AT,    SE_LCBR,  SE_RCBR,  SE_PIPE,            SE_PND,   SE_EURO,  SE_QUES,  SE_SECT,  SE_CURR,  SE_DIAE,
        SK_LEQ,   SE_HASH,  SE_DLR,   SE_LPRN,  SE_RPRN,  SE_GRV,   CK_COPY,  SE_PLUS,  SE_MINS,  SE_SLSH,  SE_ASTR,  SE_PERC,  SE_DQUO,
        SK_GEQ,   SE_PERC,  SE_CIRC,  SE_LBRC,  SE_RBRC,  SE_TILD,            SE_AMPR,  SE_EQL,   SE_LABK,  SE_RABK,  SE_BSLS,  SE_ACUT,
                                      _______,  _______,  _______,  _______,  _______,  K_NDASH,  K_MDASH
    ),
    [_RAISE] = LAYOUT(
        QK_LEAD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  KC_MPLY,
        _______,  _______,  _______,  _______,  _______,  _______,  CK_CUT,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_PGUP,  KC_VOLU,
        _______,  _______,  _______,  _______,  _______,  _______,            CK_WLFT,  CK_WRGT,  KC_HOME,  KC_END,   KC_PGDN,  KC_VOLD,
                                      _______,  KC_BSPC,  _______,  KC_ENT,   _______,  _______,  _______
    ),
    [_ADJST] = LAYOUT(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_RBT,  XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        UC_LINX,  AS_ON,    AC_ON,    CG_SWAP,  XXXXXXX, XXXXXXX,             NK_ON,    KO_ON,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        UC_MAC,   AS_OFF,   AC_OFF,   CG_NORM,  XXXXXXX, KC_GAMING, XXXXXXX,  NK_OFF,   KO_OFF,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        UC_WINC,  AS_TOGG,  AC_TOGG,  CG_TOGG,  XXXXXXX, QK_BOOT,             NK_TOGG,  KO_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),
    [_GAMING] = LAYOUT(
        SE_SECT,  SE_1,     SE_2,     SE_3,     SE_4,     SE_5,               SE_6,     SE_7,     SE_8,     SE_9,     SE_0,     SE_PLUS,
        CK_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     SE_ARNG,
        CK_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,   KC_QWERTY,  KC_H,     KC_J,     KC_K,     KC_L,     SE_ODIA,  CK_ADIA,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_N,     KC_M,     SE_COMM,  SE_DOT,   SE_MINS,  CK_QUOT,
                                      KC_CAPS,  KC_DEL,   KC_ENT,   KC_SPC,   CK_ENT1,  KC_TAB,   _______
    )
    // clang-format on
};

#ifdef KEY_OVERRIDE_ENABLE
// Make Alt + Esc => Alt + Tab
const key_override_t alt_tab_override = ko_make_with_layers_negmods_and_options(MOD_BIT(KC_LEFT_ALT), KC_ESC, KC_TAB, ~0, 0, ko_option_activation_required_mod_down | ko_option_activation_trigger_down | ko_option_no_unregister_on_other_key_down);
#    if defined(UNICODEMAP_ENABLE) || defined(UNICODE_ENABLE)
// Make Shift + - on the LOWER layer produce - (endash)
const key_override_t ndash_override = ko_make_with_layers(MOD_MASK_SHIFT, SE_BSLS, K_NDASH, (1 << _LOWER));
// Make Shift + Alt + - on the LOWER layer produce — (emdash)
const key_override_t mdash_override = ko_make_with_layers(MOD_MASK_SA, SE_BSLS, K_MDASH, (1 << _LOWER));
#    endif

const key_override_t **key_overrides = (const key_override_t *[]) {
    &alt_tab_override,
#    if defined(UNICODEMAP_ENABLE) || defined(UNICODE_ENABLE)
        &ndash_override, &mdash_override,
#    endif
        NULL // Null terminate the array of overrides!
};
#endif // KEY_OVERRIDE_ENABLE

#ifdef DEFERRED_EXEC_ENABLE
#    ifdef __AVR__
#        define STATUS_BLINK_PIN B0
#        define BLINK_DELAY 150
uint8_t counter_one       = 1;
uint8_t counter_two       = 2;
bool    blink_twice       = true;
bool    initial_pin_state = false;

deferred_token blink_once_token  = INVALID_DEFERRED_TOKEN;
deferred_token blink_twice_token = INVALID_DEFERRED_TOKEN;

uint32_t blink_toggle_callback(uint32_t trigger_time, void *cb_arg) {
    bool twice = cb_arg == NULL ? false : true;
    setPinOutput(STATUS_BLINK_PIN);
    togglePin(STATUS_BLINK_PIN);
    uint8_t return_delay = 0;

    if (twice) {
        if (counter_two > 0) {
            return_delay = BLINK_DELAY;
            counter_two--;
        }
    }

    return return_delay;
}

void stop_prior_task(deferred_token blink_token) {
    if (blink_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(blink_token);
        setPinOutput(STATUS_BLINK_PIN);
        writePin(STATUS_BLINK_PIN, initial_pin_state ? 1 : 0);
    } else {
        initial_pin_state = readPin(STATUS_BLINK_PIN);
    }
}

void perform_first_led_toggle(void) {
    setPinOutput(STATUS_BLINK_PIN);
    togglePin(STATUS_BLINK_PIN);
}
#    endif
#endif

void blink_led_once(void) {
#ifdef DEFERRED_EXEC_ENABLE
    stop_prior_task(blink_once_token);
    counter_one = 1;
    perform_first_led_toggle();
    blink_once_token = defer_exec(BLINK_DELAY, blink_toggle_callback, NULL);
#endif
}

void blink_led_twice(void) {
#ifdef DEFERRED_EXEC_ENABLE
    stop_prior_task(blink_twice_token);
    counter_two = 2;
    perform_first_led_toggle();
    blink_twice_token = defer_exec(BLINK_DELAY, blink_toggle_callback, &blink_twice);
#endif
}

#ifdef AUTOCORRECT_ENABLE
bool apply_autocorrect(uint8_t backspaces, const char *str) {
    blink_led_once();
    return true;
}
#endif

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
#if defined(AUTO_SHIFT_ENABLE) || defined(AUTOCORRECT_ENABLE) || defined(NKRO_ENABLE) || defined(KEY_OVERRIDE_ENABLE)
    if (record->event.pressed) {
        switch (keycode) {
#    ifdef AUTO_SHIFT_ENABLE
            case AS_ON:
#    endif
#    ifdef AUTOCORRECT_ENABLE
            case AC_ON:
#    endif
#    ifdef NKRO_ENABLE
            case NK_ON:
#    endif
#    ifdef KEY_OVERRIDE_ENABLE
            case KO_ON:
#    endif
                blink_led_twice();
                break;
#    ifdef AUTO_SHIFT_ENABLE
            case AS_OFF:
#    endif
#    ifdef AUTOCORRECT_ENABLE
            case AC_OFF:
#    endif
#    ifdef NKRO_ENABLE
            case NK_OFF:
#    endif
#    ifdef KEY_OVERRIDE_ENABLE
            case KO_OFF:
#    endif
                blink_led_once();
                break;
#    ifdef NKRO_ENABLE
            case NK_TOGG:
                if (!keymap_config.nkro) {
                    blink_led_twice(); // turning on
                } else {
                    blink_led_once(); // turning off
                }
                break;
#    endif
#    ifdef KEY_OVERRIDE_ENABLE
            case KO_TOGG:
                if (key_override_is_enabled()) {
                    blink_led_once(); // turning off
                } else {
                    blink_led_twice(); // turning on
                }
                break;
#    endif
        }
    }
#endif
    return true;
}
