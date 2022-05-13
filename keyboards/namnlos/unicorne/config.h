// Copyright 2022 Jan Lindblom, Namnlos Custom Keyboards (@janlindblom)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x029A
#define PRODUCT_ID   0x002A
#define DEVICE_VER   0x0001

/* key matrix size */
#define MATRIX_ROWS  4
#define MATRIX_COLS  10
#define MATRIX_ROW_PINS \
    { D4, C6, D7, E6 }
#define MATRIX_COL_PINS \
    { F4, F5, F6, F7, B1, B3, B2, B6, B4, B5 }

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
