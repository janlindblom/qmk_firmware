/**
 * @file namnlos.h
 * @author Jan Lindblom (jan@namnlos.io)
 * @brief
 * @version 0.1
 * @date 2022-04-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#ifndef NAMNLOS
#    define NAMNLOS
#endif

#include "quantum.h"
#include "oled_driver.h"
#include "eeprom.h"
typedef union {
    uint32_t raw;
    struct {
        bool    gaming_mode : 1;
        uint8_t oled_brightness : 8;
    };
} userspace_config_t;
extern userspace_config_t userspace_config;

void matrix_init_keymap(void);
void matrix_init_user(void);
void keyboard_pre_init_keymap(void);
void keyboard_pre_init_user(void);
void eeconfig_init_keymap(void);
void eeconfig_init_user(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
#ifdef OLED_ENABLE
#    ifdef CUSTOM_OLED_TIMEOUT
extern uint32_t oled_on_timer;
extern uint8_t  current_oled_brightness;
#    endif
#    if defined(WPM_ENABLE) && defined(RENDER_KITTY) && defined(DEFERRED_EXEC_ENABLE)
extern deferred_token kitten;
void                  render_kitty(void);
uint32_t              kitty_animation_phases(uint32_t triger_time, void *cb_arg);
#    endif
void            kitten_up(void);
void            kitten_down(void);
bool            oled_task_keymap(void);
bool            oled_task_user(void);
bool            process_record_user_oled(uint16_t keycode, keyrecord_t *record);
void            render_layer_state(void);
void            render_keylock_status(uint8_t led_usb_state);
void            render_mod_status(uint8_t modifiers);
oled_rotation_t oled_init_keymap(oled_rotation_t rotation);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
#    ifdef WPM_ENABLE
void render_wpm(void);
#    endif
#endif

#define OLED_SPACE " "
#define OLED_NEWLINE PSTR("\n")

#define OLED_LABEL_WPM "WPM: "
#define OLED_LABEL_MODS "Mods "
#if defined(OLED_DISPLAY_128X128) || defined(OLED_DISPLAY_128X64) || defined(OLED_DISPLAY_64X128)
#    define OLED_LABEL_LOCKS "Locks:"
#    define OLED_LABEL_LAYER "Layer:"
#else
#    define OLED_LABEL_LOCKS "Locks"
#    define OLED_LABEL_LAYER "Layer"
#endif

