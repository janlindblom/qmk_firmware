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

#pragma once
#include "quantum.h"
#include "namnlos.h"

#if defined(PROMICRO_LED_STATUS) || (defined(BACKLIGHT_LED_STATUS) && defined(BACKLIGHT_ENABLE))
#    ifndef BACKLIGHT_LED_STATUS
#        ifdef __AVR__
#            ifndef STATUS_BLINK_PIN
/**
 * @brief STATUS_BLINK_PIN is the pin connected to an LED to use for status updates.
 *
 */
#                define STATUS_BLINK_PIN B0 // B0 is one of the built in LEDs on a Pro Micro.
#            endif
#            if (STATUS_BLINK_PIN == B0) || (STATUS_BLINK_PIN == D5)
#                ifndef LED_PIN_ON_STATE
#                    define LED_PIN_ON_STATE 0 // If STATUS_BLINK_PIN is one of B0 or D5, set LED_PIN_ON_STATE to 0.
#                endif
#            endif
#        endif
#    endif
#    define BLINK_DELAY 200

/**
 * @brief Blink the designated status LED once.
 *
 */
void blink_led_once(void);
/**
 * @brief Blink the designated status LED twice.
 *
 */
void blink_led_twice(void);
/**
 * @brief Blink the designated status LED a given number of times.
 *
 * @param times the number of times to blink.
 */
void blink_status_led(int8_t times);
#endif
