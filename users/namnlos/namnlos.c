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
#include "quantum.h"
#include "send_string.h"
#include "os_detection.h"
#include "host.h"
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
#    include "unicode.h"
#endif
#include "namnlos.h"
#include "extensions/tap_dance.h"
#include "control/control_idle.h"

#if defined(PROMICRO_LED_STATUS) || defined(BACKLIGHT_LED_STATUS)
#    include "lights/status_leds.h"
#endif

#ifdef OLED_ENABLE
#    include "oled/oled_functions.h"
#    include "oled/icons.h"
#    include "oled/oled_control.h"
#    include "oled/oled_wpm.h"
#    include "oled/oled_pet.h"
#endif

#if defined(LZFX) || defined(LZFX_DECOMPRESS) || defined(LZFX_COMPRESS)
#    include "lzfx.h"
#endif

#include "debug.h"

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
extern const rgblight_segment_t *const PROGMEM namnlos_rgb_layers[];
#endif

#ifdef OLED_ENABLE
static const char PROGMEM oled_space[2] = {0x20, 0};
#endif

userspace_config_t userspace_config;

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
os_variant_t os_type = OS_UNSURE;

uint32_t os_specific_setup(uint32_t trigger_time, void *cb_arg) {
    os_type                    = detected_host_os();
    uint8_t unicode_input_mode = 6; // Start with something that's out of bounds.
    switch (os_type) {
        case OS_MACOS:
        case OS_IOS:
            unicode_input_mode           = UNICODE_MODE_MACOS;
            keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
            break;
        case OS_WINDOWS:
            unicode_input_mode = UNICODE_MODE_WINCOMPOSE;
            break;
        case OS_LINUX:
            unicode_input_mode = UNICODE_MODE_LINUX;
            break;
        default:
            break;
    }
#    if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    if ((os_type != OS_UNSURE) && (unicode_input_mode < UNICODE_MODE_COUNT)) {
        set_unicode_input_mode(unicode_input_mode);
    }
#    endif
    return os_type ? 0 : 500;
}
#endif

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#if defined(DEBUG) || !defined(NO_DEBUG)
    debug_enable = true;
#endif
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    // Enable the LED layers
    rgblight_layers = namnlos_rgb_layers;
    rgblight_enable();
#endif
#ifdef OLED_ENABLE
    if (userspace_config.oled_brightness != 0) {
        oled_set_brightness(userspace_config.oled_brightness);
    }
#endif
    enable_keyboard_idle_control();
    keyboard_post_init_keymap();
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(100, os_specific_setup, NULL);
#endif
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw         = 0;
    userspace_config.gaming_mode = false;
#ifdef OLED_ENABLE
    if (userspace_config.oled_brightness == 0) {
        userspace_config.oled_brightness = OLED_BRIGHTNESS;
    }
#endif // OLED_ENABLE
    eeconfig_update_user(userspace_config.raw);

    if (eeconfig_read_default_layer() != _BASE) {
        eeconfig_update_default_layer(_BASE);
    }
    eeconfig_init_keymap();
}

__attribute__((weak)) void matrix_init_keymap(void) {}

void matrix_init_user(void) {
#if defined(BOOTLOADER_CATERINA) && defined(__AVR__) && defined(__AVR_ATmega32U4__)
    DDRD &= ~(1 << 5);
    PORTD &= ~(1 << 5);

    DDRB &= ~(1 << 0);
    PORTB &= ~(1 << 0);
#endif
    matrix_init_keymap();
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Any keypress => keyboard is active.
        trigger_keyboard_active();
    }
    if (!process_record_keymap(keycode, record)) {
        // Keymap process_record returned false, stop processing.
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
#if defined(PROMICRO_LED_STATUS) || defined(BACKLIGHT_LED_STATUS)
#    if defined(AUTO_SHIFT_ENABLE) || defined(AUTOCORRECT_ENABLE) || defined(NKRO_ENABLE) || defined(KEY_OVERRIDE_ENABLE)
#        ifdef AUTO_SHIFT_ENABLE
            case AS_ON:
#        endif
#        ifdef AUTOCORRECT_ENABLE
            case AC_ON:
#        endif
#        ifdef NKRO_ENABLE
            case NK_ON:
#        endif
#        ifdef KEY_OVERRIDE_ENABLE
            case KO_ON:
#        endif
#        ifdef PROMICRO_LED_STATUS
                blink_led_twice();
#        endif
                break;
#        ifdef AUTO_SHIFT_ENABLE
            case AS_OFF:
#        endif
#        ifdef AUTOCORRECT_ENABLE
            case AC_OFF:
#        endif
#        ifdef NKRO_ENABLE
            case NK_OFF:
#        endif
#        ifdef KEY_OVERRIDE_ENABLE
            case KO_OFF:
#        endif
                blink_led_once();
#    endif
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
#endif
            case SK_NOT_EQL:
                SEND_STRING("!=");
                break;
            case SK_LEQ:
                SEND_STRING("<=");
                break;
            case SK_GEQ:
                SEND_STRING(">=");
                break;
#ifdef OLED_ENABLE
            case CK_OBI:
                step_oled_brightness(15);
                break;
            case CK_OBD:
                step_oled_brightness(-15);
                break;
#endif
#ifdef BACKLIGHT_ENABLE
            case CK_BACKLIGHT_LEVEL_REPORT:
                SEND_STRING("Backlight Level: ");
                send_byte(get_backlight_level());
                SEND_STRING(SS_TAP(X_ENTER));
                break;
#endif
#if defined(OS_DETECTION_ENABLE)
            case CK_DLEFT:
                if (detected_host_os() == OS_LINUX) {
                    tap_code16(LAG(KC_LEFT));
                } else if (detected_host_os() == OS_WINDOWS) {
                    tap_code16(LCG(KC_LEFT));
                }
                break;
            case CK_DRGHT:
                if (detected_host_os() == OS_LINUX) {
                    tap_code16(LAG(KC_RIGHT));
                } else if (detected_host_os() == OS_WINDOWS) {
                    tap_code16(LCG(KC_RIGHT));
                }
                break;
#endif
        }
    }
    return true;
}

/**
 * @brief Set the default layer optionally saving it to EEPROM if EEPROM_DEFAULT_LAYER_SAVE is defined.
 *
 * @param layer the layer to set as the default.
 */
void SET_DEFAULT_LAYER(uint8_t layer) {
#ifdef EEPROM_DEFAULT_LAYER_SAVE
    eeconfig_update_default_layer(layer); // Save the default layer to EEPROM
#endif
    default_layer_set((layer_state_t)1u << layer);
}

uint8_t GET_DEFAULT_LAYER(void) {
    return get_highest_layer(default_layer_state);
}

uint8_t GET_TOP_LAYER(void) {
    return get_highest_layer(layer_state);
}

__attribute__((weak)) layer_state_t default_layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
#endif
    return default_layer_state_set_keymap(state);
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYMB));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUMB));
    rgblight_set_layer_state(3, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJST));
#endif
#ifndef NO_UPDATE_TRI_LAYER_STATE
    return update_tri_layer_state(layer_state_set_keymap(state), _SYMB, _NUMB, _ADJST);
#else
    return layer_state_set_keymap(state);
#endif
}

void matrix_scan_user(void) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS) && defined(RGBLIGHT_MODS)
    uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
    rgblight_set_layer_state(6, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(7, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(8, mods & MOD_MASK_ALT);
    rgblight_set_layer_state(9, mods & MOD_MASK_GUI);
#endif
}

#ifdef OLED_ENABLE
__attribute__((weak)) bool render_layer_state_keymap(void) {
    return true;
}

void render_layer_state_user(void) {
    static const char PROGMEM layer_status[5][6] = {
        // clang-format off
        {0xFC, 0xFF, 0xFD, 0xFD, 0xFE, 0},  // _BASE
        {0xFF, 0xFD, 0xFD, 0xFD, 0xFE, 0},  // _LOWER
        {0xFC, 0xFD, 0xFF, 0xFD, 0xFE, 0},  // _RAISE
        {0xFC, 0xFD, 0xFD, 0xFF, 0xFE, 0},  // _ADJST
        {0xFC, 0xFD, 0xFD, 0xFD, 0xFF, 0}   // OTHER
        // clang-format on
    };

    static const char PROGMEM layer_name[][OLED_RENDER_LAYER_NAME_LENGTH] = {
        // clang-format off
        [_BASE] = OLED_RENDER_LAYOUT_QWERTY,
        [_SVRK] = OLED_RENDER_LAYOUT_SVORAK,
        [_KICAD] = OLED_RENDER_LAYOUT_KICAD,
        [_ADESK] = OLED_RENDER_LAYOUT_ADESK,
        [_GAMING] = OLED_RENDER_LAYOUT_GAMING
        // clang-format on
    };

    if (!render_layer_state_keymap()) {
        return;
    }
#    ifdef OLED_LAYER_COL
    OLED_PLACE_CURSOR_FULL(OLED_LAYER_LINE, OLED_LAYER_COL);
#    else
    OLED_PLACE_CURSOR(OLED_LAYER_LINE);
#    endif
#    ifdef OLED_VERBOSE
    oled_write_P(PSTR(OLED_LABEL_LAYER), false);
#    endif

    uint8_t active_layer  = 4;
    switch (GET_TOP_LAYER()) {
        case _BASE:
            active_layer = 0;
            break;
        case _LOWER:
            active_layer = 1;
            break;
        case _RAISE:
            active_layer = 2;
            break;
        case _ADJST:
            active_layer = 3;
        default:
            break;
    }
    oled_write_P(layer_status[active_layer], false);

    uint8_t top_layer = GET_DEFAULT_LAYER();
    if (top_layer != _BASE) {
        switch (top_layer) {
            case _SVRK:
            case _ADESK:
            case _KICAD:
            case _GAMING:
                oled_write_P(layer_name[top_layer], false);
                break;
            default:
                break;
        }
    } else {
        oled_write_P(PSTR(OLED_EMPTY_LINE), false);
    }
}

void render_keylock_status(void) {
    static const char PROGMEM lock_names[3][2] = {
        {0x43, 0}, // CAPS LOCK
        {0x4E, 0}, // NUM LOCK
        {0x53, 0}  // SCROLL LOCK
    };
    static const char PROGMEM lock_labels[2][2] = {{0xBE, 0}, {0xBF, 0}};
#    ifdef OLED_KEYLOCK_COL
    OLED_PLACE_CURSOR_FULL(OLED_KEYLOCK_LINE, OLED_KEYLOCK_COL);
#    else
    OLED_PLACE_CURSOR(OLED_KEYLOCK_LINE);
#    endif
#    ifdef OLED_VERBOSE
    oled_write_P(PSTR(OLED_LABEL_LOCKS), false);
#    endif
    led_t host_leds = host_keyboard_led_state();
    oled_write_P(lock_names[0], false);
    // Since bool is basically uint8_t, we can use IS_LED_ON as an index to the lock_labels array.
    oled_write_P(lock_labels[(uint8_t)host_leds.caps_lock], false);
    oled_write_P(oled_space, false);
    oled_write_P(lock_names[1], false);
    oled_write_P(lock_labels[(uint8_t)host_leds.num_lock], false);
#    if (OLED_DISPLAY_WIDTH == 64) || defined(OLED_HORIZONTAL)
    oled_write_P(oled_space, false);
#    endif
    oled_write_P(lock_names[2], false);
    oled_write_P(lock_labels[(uint8_t)host_leds.scroll_lock], false);
}

void render_mod_status(uint8_t modifiers) {
    static const char PROGMEM mod_status[5][3] = {
        // clang-format off
        {0xE8, 0xE9, 0}, // SHIFT
        {0xE4, 0xE5, 0}, // CTRL
        {0xE6, 0xE7, 0}, // ALT
        {0xEA, 0xEB, 0}, // GUI
        {0xEC, 0xED, 0}
        // clang-format on
    };
#    ifdef OLED_MODS_COL
    OLED_PLACE_CURSOR_FULL(OLED_MODS_LINE, OLED_MODS_COL);
#    else
    OLED_PLACE_CURSOR(OLED_MODS_LINE);
#    endif
#    ifdef OLED_VERBOSE
    oled_write_P(PSTR(OLED_LABEL_MODS), false);
#    endif
    oled_write_P(mod_status[0], (modifiers & MOD_MASK_SHIFT));
    oled_write_P(oled_space, false);
    oled_write_P(mod_status[4 - (uint8_t)!keymap_config.swap_lctl_lgui], (modifiers & MOD_MASK_GUI));
#    if defined(OLED_HORIZONTAL) || (OLED_DISPLAY_WIDTH == 64)
    oled_write_P(oled_space, false);
#    endif
    oled_write_P(mod_status[2], (modifiers & MOD_MASK_ALT));
    oled_write_P(oled_space, false);
    oled_write_P(mod_status[1], (modifiers & MOD_MASK_CTRL));
}

void render_magic_status(void) {
#    ifndef OLED_MAGIC_COL
    OLED_PLACE_CURSOR(OLED_MAGIC_LINE);
#    else
    OLED_PLACE_CURSOR_FULL(OLED_MAGIC_LINE, OLED_MAGIC_COL);
#    endif

    uint8_t os = 0;
#    if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    os_type = detected_host_os();
    os      = os_type < 3 ? os_type : 3;
#    else
    os = keymap_config.swap_lctl_lgui ? 3 : 2;
#    endif
#    if defined(OLED_DISPLAY_128X128) || defined(OLED_DISPLAY_128X64)
    // clang-format off
    static const char PROGMEM os_logo[2][4][3] = {
        // Unsure           Linux            Windows          macOS
        {{0x81, 0x84, 0}, {0x99, 0x9A, 0}, {0x97, 0x98, 0}, {0x95, 0x96, 0}},
        {{0xC1, 0xC4, 0}, {0xB9, 0xBA, 0}, {0xB7, 0xB8, 0}, {0xB5, 0xB6, 0}}
        };
    // clang-format on

    oled_write_P(PSTR("NK"), keymap_config.nkro);
    oled_write_P(oled_space, false);
    oled_write_P(os_logo[0][os], false);
#        ifndef OLED_MAGIC_COL
    OLED_PLACE_CURSOR(OLED_MAGIC_LINE + 1);
#        else
    OLED_PLACE_CURSOR_FULL(OLED_MAGIC_LINE + 1, OLED_MAGIC_COL);
#        endif
    oled_write_P(PSTR("RO"), keymap_config.nkro);
    oled_write_P(oled_space, false);
    oled_write_P(os_logo[1][os], false);
#    else
    static const char PROGMEM os_logo[4][2] = {
        {0x00, 0}, // Unsure
        {0x9D, 0}, // Linux
        {0x9F, 0}, // Windows
        {0x9E, 0}  // macOS
    };

    static const char PROGMEM magic_status[3][2][2] = {
        // clang-format off
        { // NKRO
            {0x07, 0}, // NKRO off
            {0x08, 0}  // NKRO on
        }, { // Swap LCtrl<->LGUI
            {0x9E, 0}, // Mac
            {0x9F, 0}  // Windows
        }, { // Autocorrect
            {0x13, 0},
            {0x13, 0}
        }
        // clang-format on
    };

    oled_write_P(magic_status[0][0], keymap_config.nkro);
#        ifdef AUTOCORRECT_ENABLE
    oled_write_P(magic_status[2][0], autocorrect_is_enabled());
#        endif
    oled_write_P(os_logo[os], false);
    // uint8_t highest_default_layer = get_highest_layer(default_layer_state);
#    endif
    // oled_write_P(magic_status[0][(uint8_t)keymap_config.nkro], false);
    // #    if defined(OLED_DISPLAY_128X128) || defined(OLED_DISPLAY_128X64) || (defined(OLED_HORIZONTAL) && (OLED_DISPLAY_WIDTH > 64))
    //  oled_write_P(oled_space, false);
    // #    endif
    //  oled_write_P(magic_status[1][(uint8_t)!keymap_config.swap_lctl_lgui], false);
}

__attribute__((weak)) bool oled_task_master_keymap(void) {
    return true;
}

void oled_task_master_user(void) {
    if (!oled_task_master_keymap()) {
        return;
    }
    render_layer_state_user();
#    ifndef NO_ACTION_ONESHOT
    render_mod_status(get_mods() | get_oneshot_mods());
#    else
    render_mod_status(get_mods());
#    endif
    render_keylock_status();
    render_magic_status();
#    ifdef WPM_ENABLE
#        if (OLED_COUNT == 1) || defined(OLED_WPM_COL) || defined(OLED_HORIZONTAL)
    render_wpm();
#        endif
#    endif
#    if defined(WPM_ENABLE) && defined(RENDER_PET)
#        if (OLED_COUNT == 1) || defined(OLED_HORIZONTAL)
    render_pet();
#        elif defined(RENDER_KEYBOARD_LOGO) && (OLED_COUNT == 2) && defined(OLED_VERTICAL)
    render_keyboard_logo();
#        endif
    render_icon();
#    endif
    // oled_advance_page(true);
}

__attribute__((weak)) bool oled_task_non_master_keymap(void) {
    return true;
}

void oled_task_non_master_user(void) {
    if (!oled_task_non_master_keymap()) {
        return;
    }
#    if (OLED_COUNT == 2)
// Code for non-master side.
#        if defined(WPM_ENABLE) && defined(RENDER_PET) && !defined(OLED_HORIZONTAL)
    render_pet();
#        endif
    render_icon();
#        if defined(WPM_ENABLE) && !defined(OLED_WPM_COL)
    render_wpm();
#        endif
#    endif
}

__attribute__((weak)) bool oled_task_keymap(void) {
    return true;
}

bool oled_task_user(void) {
    if (!oled_task_keymap()) {
        return false;
    }
    if (is_keyboard_master()) {
        oled_task_master_user();
    } else {
        oled_task_non_master_user();
    }
    return false;
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return rotation;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#    ifdef DEFERRED_EXEC_ENABLE
#        ifdef RENDER_PET
    pet_control_on(3000);
#        endif // RENDER_PET
#    endif     // DEFERRED_EXEC_ENABLE
    return oled_init_keymap(rotation);
}
#endif // OLED_ENABLE

__attribute__((weak)) bool shutdown_keymap(bool jump_to_bootloader) {
    return true;
}
bool                       shutdown_user(bool jump_to_bootloader) {
#ifdef OLED_ENABLE
#    if defined(DEFERRED_EXEC_ENABLE) && defined(RENDER_PET)
    pet_control_off();
#    endif
    userspace_config.oled_brightness = oled_get_brightness();
    eeconfig_update_user(userspace_config.raw);
#endif
    // Switch of any active special layers
    if (layer_state_is(_GAMING)) {
        layer_off(_GAMING);
    }
    if (layer_state_is(_ADESK)) {
        layer_off(_ADESK);
    }
    if (layer_state_is(_KICAD)) {
        layer_off(_KICAD);
    }
    if (layer_state_is(_LANG)) { // This will incidentally also switch off _SVRK
        layer_off(_LANG);
    }
    return shutdown_keymap(jump_to_bootloader);
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}
void                       suspend_power_down_user(void) {
#if defined(OLED_ENABLE)
#    if defined(DEFERRED_EXEC_ENABLE) && defined(RENDER_PET)
    pet_control_off();
#    endif
    userspace_config.oled_brightness = oled_get_brightness();
    eeconfig_update_user(userspace_config.raw);
#endif
    // Switch of any active special layers
    if (layer_state_is(_GAMING)) {
        layer_off(_GAMING);
    }
    if (layer_state_is(_ADESK)) {
        layer_off(_ADESK);
    }
    if (layer_state_is(_KICAD)) {
        layer_off(_KICAD);
    }
    if (layer_state_is(_LANG)) { // This will incidentally also switch off _SVRK
        layer_off(_LANG);
    }
    suspend_power_down_keymap();
}

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
#ifdef OLED_ENABLE
#    ifdef DEFERRED_EXEC_ENABLE
#        ifdef RENDER_PET
    pet_control_on(1000);
#        endif // RENDER_PET
#    endif     // DEFERRED_EXEC_ENABLE
    userspace_config.oled_brightness = oled_get_brightness();
    eeconfig_update_user(userspace_config.raw);
#endif // OLED_ENABLE
    suspend_wakeup_init_keymap();
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(100, os_specific_setup, NULL);
#endif
}

__attribute__((weak)) bool led_update_keymap(led_t led_state) {
    return true;
}

bool led_update_user(led_t led_state) {
    bool res = led_update_keymap(led_state);
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    rgblight_set_layer_state(5, led_state.caps_lock);
#endif
    if (res) {
#ifdef CAPS_LOCK_LED_PIN
        setPinOutput(CAPS_LOCK_LED_PIN);
        if (led_state.caps_lock) {
            writePinLow(CAPS_LOCK_LED_PIN);
        } else {
            writePinHigh(CAPS_LOCK_LED_PIN);
        }
#endif
    }
    return res;
}

#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
#    ifdef CAPS_WORD_LED_PIN
    setPinOutput(CAPS_WORD_LED_PIN);
    if (active) {
        writePinLow(CAPS_WORD_LED_PIN);
    } else {
        writePinHigh(CAPS_WORD_LED_PIN);
    }
#    endif
}
#endif
