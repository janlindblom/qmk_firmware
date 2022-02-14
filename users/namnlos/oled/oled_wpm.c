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
#include "oled_wpm.h"
#include "control/control_idle.h"

#ifdef OLED_ENABLE
#    ifdef WPM_ENABLE
uint8_t current_wpm;
#        ifdef DEFERRED_EXEC_ENABLE
bool           _hide_wpm = false;
deferred_token wpm_token = INVALID_DEFERRED_TOKEN;
#        endif

/**
 * Keymap level function to ask whether the WPM should be rendered.
 * Weak function to be overridden by keymap.c.
 */
__attribute__((weak)) bool render_wpm_keymap(void) {
    return true;
}

/**
 * @brief Userspace function to ask whether the WPM should be rendered.
 *
 * @return true if it should.
 * @return false otherwise.
 */
bool render_wpm_user(void) {
    return render_wpm_keymap();
}

uint32_t show_wpm_render(uint32_t trigger_time, void *cb_arg) {
#        ifdef DEFERRED_EXEC_ENABLE
#            ifndef OLED_WPM_COL
    OLED_PLACE_CURSOR(OLED_WPM_LINE);
    OLED_CLEAR_LINE();
#            else
    OLED_PLACE_CURSOR_FULL(OLED_WPM_LINE, OLED_WPM_COL);
    oled_write_P(PSTR("     "), false);
#            endif
    _hide_wpm = false; // Show WPM again.
#        endif
    return 0;
}

/**
 * @brief Hides the WPM display with a timeout, will re-show when the timeout is hit.
 *
 * Subsequent calls to this function will add a second to the timeout.
 *
 */
void hide_wpm_render(void) {
#        ifdef DEFERRED_EXEC_ENABLE
    if (!_hide_wpm || (wpm_token == INVALID_DEFERRED_TOKEN)) { // Not hidden yet, hide and setup deferred task to show again.
        _hide_wpm = true;                                      // Hide the WPM display.
        wpm_token = defer_exec(1000, show_wpm_render, NULL);   // Show the WPM display again after 1 second.
    } else if (_hide_wpm) {                                    // Already hidden, add a second to the timeout.
        extend_deferred_exec(wpm_token, 1000);                 // Extend the timeout with 1 second.
    }
#        endif
}

/**
 * @brief Whether the WPM display should be rendered.
 *
 * @return true if it should,
 * @return false otherwise.
 */
bool hide_wpm(void) {
#        ifdef DEFERRED_EXEC_ENABLE
    return _hide_wpm;
#        else
    return false;
#        endif
}
/**
 * @brief Renders WPM to the OLED.
 *
 */
void render_wpm(void) {
    current_wpm = get_current_wpm();
    if (hide_wpm()) { // Hide wpm if it is not needed/wanted
        return;
    }
#        ifndef OLED_WPM_COL
    OLED_PLACE_CURSOR(OLED_WPM_LINE);
#        else
    OLED_PLACE_CURSOR_FULL(OLED_WPM_LINE, OLED_WPM_COL);
#        endif
    if (!render_wpm_user()) {
        //render_wpm_user() says no
#        ifndef OLED_WPM_COL
        OLED_CLEAR_LINE();
#        else
        oled_write_P(PSTR("     "), false);
#        endif
        return;
    }

    oled_write_P(PSTR(OLED_LABEL_WPM), false); // Print a little chevron there
    oled_write(get_u8_str(current_wpm, ' '), false);
}
#    endif // WPM_ENABLE
#endif     // OLED_ENABLE
