/**
 * Copyright © 2023 Jan Lindblom (@janlindblom)
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
#include "control_idle.h"

#ifdef OLED_ENABLE
#    include "oled/oled_control.h"
#endif

#if defined(BACKLIGHT_ENABLE)
#    include "backlight.h"
#endif
#if defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif

#if defined(BACKLIGHT_ENABLE) || defined(RGBLIGHT_ENABLE)
bool backlight_turned_off = false;
#endif

bool lights_are_turned_off = false;

// There are two timers here, basically we set a timer for a minute or whatever
// and when that one is exceeded we start the other one for the same amount of
// time. This means the keyboard is considered ACTIVE for up to a minute, after
// which we start counting down until the other timer is exceed and we consider
// the keyboard to be INACTIVE.
uint32_t keyboard_active_timer   = 0;
uint32_t keyboard_inactive_timer = 0;

#ifdef KEYBOARD_SLEEP_TIMEOUT
uint32_t keyboard_inactive_threshold = KEYBOARD_SLEEP_TIMEOUT;
#else
uint32_t keyboard_inactive_threshold = 60000u; // 1 minute
#endif

#if defined(BACKLIGHT_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
deferred_token keyboard_backlight_token = INVALID_DEFERRED_TOKEN;

uint32_t backlight_callback(uint32_t trigger_time, void *cb_arg) {
    // We're going to call both is_inactive() and still_inactive() to make sure
    // the inactive timer is triggered and run any code we want to run in those
    // functions too.
    bool lights_should_be_off = is_inactive();
    if (is_keyboard_master()) {
        if (lights_should_be_off && !lights_are_turned_off) {
            turn_backlights_off();
        } else if (!lights_should_be_off && lights_are_turned_off) {
            turn_backlights_on();
        }
    }
    return BACKLIGHT_TIMER_INTERVAL;
}
#endif

void enable_keyboard_idle_control(void) {
    trigger_keyboard_active();
#if defined(BACKLIGHT_ENABLE)
#    if defined(DEFERRED_EXEC_ENABLE)
    // Start the backlight control job as a deferred task
    if (is_keyboard_master()) {
        keyboard_backlight_token = defer_exec(BACKLIGHT_TIMER_INTERVAL, backlight_callback, NULL);
    }
#    endif
#endif
}

void trigger_keyboard_active(void) {
    if (is_keyboard_master()) {
        turn_backlights_on();
        keyboard_active_timer = timer_read32() + keyboard_inactive_threshold;
    }
}

bool is_inactive(void) {
    if (is_keyboard_master()) {
        if (!timer_expired32(timer_read32(), keyboard_active_timer)) {
            return false;
        } else {
            keyboard_inactive_timer = timer_read32() + keyboard_inactive_threshold;
            return true;
        }
    }
    return false;
}

bool still_inactive(void) {
    if (is_keyboard_master()) {
        if (timer_expired32(timer_read32(), keyboard_inactive_timer)) {
            return true;
        }
    }
    return false;
}

void turn_backlights_off(void) {
#ifdef BACKLIGHT_ENABLE
    // Disable backlight (turn it off)
    backlight_disable();
#endif
#ifdef RGBLIGHT_ENABLE
    // Disable RGB lights without storing the off state in EEPROM.
    rgblight_disable_noeeprom();
#endif
#if defined(OLED_ENABLE) && defined(CUSTOM_OLED_SLEEP)
    // Turn the OLED off.
    turn_oled_off(); // TODO: Move this OLED control stuff somewhere more fitting?
#endif
    lights_are_turned_off = true;
}

void turn_backlights_on(void) {
#ifdef BACKLIGHT_ENABLE
    // Enable the backlight (turn it on)
    backlight_enable();
#endif
#ifdef RGBLIGHT_ENABLE
    // Enable RGB lights without storing the on state in EEPROM.
    rgblight_enable_noeeprom();
#endif
#if defined(OLED_ENABLE) && defined(CUSTOM_OLED_SLEEP)
    // Turn the OLED on.
    turn_oled_on(); // TODO: Move this OLED control stuff somewhere more fitting?
#endif
    lights_are_turned_off = false;
}
