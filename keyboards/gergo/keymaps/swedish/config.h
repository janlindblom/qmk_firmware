#pragma once

#undef DEBOUNCE
#define DEBOUNCE 12
#define TAPPING_TERM 200

#define LAYER_STATE_8BIT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT

//#define COMBO_COUNT 3  // Enable if using combos.
#define UNICODE_SELECTED_MODES UC_WINC
#define IGNORE_MOD_TAP_INTERRUPT
#define OLED_FONT_H "keyboards/gergo/keymaps/swedish/namnlos_font.c"
#define OLED_FONT_WIDTH 8
#define OLED_TIMEOUT 60000
#define OLED_BRIGHTNESS 180
#define OLED_FONT_END 191
#define OLED_FADE_OUT_INTERVAL 5
