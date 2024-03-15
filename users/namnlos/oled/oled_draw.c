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

#include "oled_draw.h"

#ifdef OLED_ENABLE

void oled_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    uint8_t dx, dy, p, x, y;
    dx = (x2 > x1) ? x2 - x1 : x1 - x2;
    dy = (y2 > y1) ? y2 - y1 : y1 - y2;

    x = x1;
    y = y1;
    p = (dy << 1) - dx;

    while (x < x1) {
        if (p >= 0) {
            oled_write_pixel(x, y, true);
            y++;
            p += (dy << 1) - (dx << 1);
        } else {
            oled_write_pixel(x, y, true);
            p += (dy << 1);
        }
        x++;
    }
}

#endif // OLED_ENABLE
