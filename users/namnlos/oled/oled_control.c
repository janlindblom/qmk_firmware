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

#include "oled_control.h"

#ifdef OLED_ENABLE
extern userspace_config_t userspace_config;

#    if CUSTOM_OLED_FADEOUT
#        ifdef DEFERRED_EXEC_ENABLE
bool           _fading       = false;
deferred_token fadeout_token = INVALID_DEFERRED_TOKEN;
uint8_t        fade_level    = 0;

uint32_t fadeout_render(uint32_t trigger_time, void *cb_arg) {
    if (fade_level > 0) {
        fade_level--;
        oled_set_brightness(fade_level);
        return 100;
    } else {
        oled_set_brightness(0);
        oled_off();
        _fading = false;
        return 0;
    }
}
#        endif // DEFERRED_EXEC_ENABLE
#    endif     // CUSTOM_OLED_FADEOUT

void turn_oled_on(void) {
#    ifdef CUSTOM_OLED_SLEEP
    oled_on();
#    endif
#    if defined(DEFERRED_EXEC_ENABLE) && defined(CUSTOM_OLED_FADEOUT)
    if (_fading) {
        cancel_deferred_exec(fadeout_token);
        _fading = false;
    }
    userspace_config.raw = eeconfig_read_user();
    oled_set_brightness(userspace_config.oled_brightness);
#    endif
}

void turn_oled_off(void) {
#    if defined(DEFERRED_EXEC_ENABLE) && defined(CUSTOM_OLED_FADEOUT)
    if (_fading || !is_oled_on()) {
        return;
    }
    _fading              = true;
    userspace_config.raw = eeconfig_read_user();
    fade_level           = userspace_config.oled_brightness;
    fadeout_token        = defer_exec(100, fadeout_render, NULL);
#    endif
#    ifdef CUSTOM_OLED_SLEEP
    oled_off();
#    endif
}

void step_oled_brightness(int8_t step) {
    uint8_t level = oled_get_brightness();
    if (level + step > 250) {
        level = 255;
    } else if (level + step < 1) {
        level = 1;
    } else {
        level += step;
    }
    oled_set_brightness(level);
    userspace_config.oled_brightness = level;
    hide_wpm_render();
#    ifdef OLED_STATUS_COL
    OLED_PLACE_CURSOR_FULL(OLED_STATUS_LINE, OLED_STATUS_COL);
#    else
    OLED_PLACE_CURSOR(OLED_STATUS_LINE);
#    endif
    oled_write_P(PSTR("\x0f "), false); // A little sun icon.
    oled_write(get_u8_str(level, ' '), false);
    eeconfig_update_user(userspace_config.raw);
}
#endif // OLED_ENABLE
