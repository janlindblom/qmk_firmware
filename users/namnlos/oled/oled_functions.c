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
#include "namnlos.h"
#include "oled_functions.h"
#include "oled_pet.h"

#ifdef OLED_ENABLE
void OLED_PLACE_CURSOR_FULL(uint8_t row, uint8_t col) {
#    ifndef OLED_VERBOSE
    oled_set_cursor(col, PET_OFFSET(row));
#    else
    oled_set_cursor(col, PET_OFFSET(row + 1));
#    endif
}

void OLED_PLACE_CURSOR(uint8_t row) {
    OLED_PLACE_CURSOR_FULL(row, 0);
}

/**
 * @brief Clears out the current line on the OLED.
 *
 */
void OLED_CLEAR_LINE(void) {
    oled_write_P(PSTR(OLED_EMPTY_LINE), false);
}
#endif
