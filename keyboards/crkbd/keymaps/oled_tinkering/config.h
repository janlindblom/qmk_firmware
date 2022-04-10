/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

//#define USE_MATRIX_I2C
#ifdef KEYBOARD_crkbd_rev1_common
#    undef USE_I2C
#    define USE_SERIAL
#endif

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

//#define OLED_DISPLAY_CUSTOM
#define OLED_DISPLAY_128X64
//#define OLED_DISPLAY_64X128
//#define OLED_DISPLAY_WIDTH 64
//#define OLED_DISPLAY_HEIGHT 128

//#define OLED_BLOCK_TYPE uint16_t
//#define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
//#define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)

//#define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)

//#define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56 }
//#define OLED_TARGET_MAP { 56, 48, 40, 32, 24, 16, 8, 0 }
//#define OLED_COM_PINS COM_PINS_ALT
//#define OLED_COLUMN_OFFSET 4
//#define OLED_IC OLED_IC_SH1107
#define OLED_BRIGHTNESS 50
//#undef OLED_UPDATE_INTERVAL
//#define OLED_UPDATE_INTERVAL 100

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
