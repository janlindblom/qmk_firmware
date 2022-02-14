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

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif
#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#if defined(BACKLIGHT_ENABLE) || defined(RGBLIGHT_ENABLE)
// Run backlight control every second, no need to go faster.
#    define BACKLIGHT_TIMER_INTERVAL 1000
#endif

/**
 * @brief Trigger function, will let the system know that the keyboard is in use.
 *
 */
void trigger_keyboard_active(void);

/**
 * @brief Check if the keyboard is inactive.
 *
 * @return true
 * @return false
 */
bool is_inactive(void);

/**
 * @brief Check if the keyboard is still inactive.
 *
 * @return true
 * @return false
 */
bool still_inactive(void);

void enable_keyboard_idle_control(void);
void turn_backlights_off(void);
void turn_backlights_on(void);
