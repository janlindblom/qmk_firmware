/*
Copyright 2021 Sam Mohr <sam@mohr.codes>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


/* USB Device descriptor parameter */
#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Sam Mohr
#define PRODUCT         Fun Size

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

// wiring
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
#define MATRIX_COL_PINS { B1, F7, F6, F5, F4 }
#define MATRIX_ROW_PINS_RIGHT { F4, F5, F6, F7 }
#define MATRIX_COL_PINS_RIGHT { D1, D0, D4, C6, D7 }

#define SOFT_SERIAL_PIN D2
#define SPLIT_USB_DETECT

#define ENCODERS_PAD_A { B5, B6 }
#define ENCODERS_PAD_B { B4, B2 }
#define ENCODERS_PAD_A_RIGHT { B3, E6 }
#define ENCODERS_PAD_B_RIGHT { B2, B4 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
