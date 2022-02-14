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
#include "status_leds.h"

#if defined(PROMICRO_LED_STATUS) || (defined(BACKLIGHT_LED_STATUS) && defined(BACKLIGHT_ENABLE))
int8_t counter     = 2;
bool   is_blinking = false;
#    ifdef DEFERRED_EXEC_ENABLE
deferred_token blink_token;

void toggle_led(void) {
#        if (defined(BACKLIGHT_LED_STATUS) && defined(BACKLIGHT_ENABLE))
    backlight_toggle();
#        elif defined(PROMICRO_LED_STATUS)
    setPinOutput(STATUS_BLINK_PIN);
    togglePin(STATUS_BLINK_PIN);
#        endif
}

void led_off(void) {
#        if defined(PROMICRO_LED_STATUS)
    setPinOutput(STATUS_BLINK_PIN);
    writePin(STATUS_BLINK_PIN, ~(LED_PIN_ON_STATE));
#        endif
}

uint32_t blink_toggle_callback(uint32_t trigger_time, void *cb_arg) {
    uint8_t return_delay = 0;
    if (is_blinking) {
        toggle_led();
        if (counter > 0) {
            counter--;
            return_delay = BLINK_DELAY;
        } else {
            led_off();
            is_blinking = false;
        }
    }
    return return_delay;
}
#    endif

void blink_led_once(void) {
    blink_status_led(1);
}

void blink_led_twice(void) {
    blink_status_led(2);
}

void blink_status_led(int8_t times) {
#    ifdef DEFERRED_EXEC_ENABLE
    if (is_blinking) {
        return;
    }
    led_off();
    is_blinking = true;
    counter     = times * 2 - 1;
    blink_token = defer_exec(BLINK_DELAY, blink_toggle_callback, NULL);
#    endif
}
#endif
