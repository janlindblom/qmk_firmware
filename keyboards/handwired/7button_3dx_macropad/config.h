// Copyright 2022 Jan Lindblom (@janlindblom)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN D1
#    define RGBLED_NUM 5
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_USE_TIMER
#    define RGBLIGHT_SLEEP
#endif

#ifdef BACKLIGHT_ENABLE
#    define BACKLIGHT_PIN B5
#    define BACKLIGHT_LEVELS 10
#    define BACKLIGHT_LIMIT_VAL 200
#endif

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING
#define LAYER_STATE_8BIT
