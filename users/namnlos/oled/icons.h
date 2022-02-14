/**
 * Copyright © 2022 Jan Lindblom (@janlindblom)
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org>
 */

#pragma once
#include "quantum.h"
#include "namnlos.h"

#ifdef OLED_ENABLE
// Icon names start at 1 so we can return this value from render_icon_* when there should be an icon.
// Whenever no icon is supposed to be rendered, we return 0 (same as bool false) from render_icon_*.
enum oled_icon_names {
    ICON_AUTODESK = 1, // Autodesk
    ICON_KICAD         // KiCad
};

// Size of icon in bytes (32 * 32) / 8
#    define ICON_SIZE 128

/**
 * @brief Keymap-level "are we supposed to render an icon?" function.
 *
 * @return uint8_t 0 if no icon should be rendered, otherwise the icon indicated in the enum icon_names.
 */
uint8_t render_icon_keymap(void);

/**
 * @brief User-level "are we supposed to render an icon?" function.
 *
 * @return uint8_t 0 if no icon should be rendered, otherwise the icon indicated in the enum icon_names.
 */
uint8_t render_icon_user(void);

/**
 * @brief Function to render an icon on the OLED screen.
 *
 * @param icon the icon to render, as defined in the enum icon_names.
 */
void draw_icon(uint8_t icon);

/**
 * @brief Render the icon.
 * Right now, the icon is rendered in the upper left corner on the OLED.
 *
 */
void render_icon(void);
#endif // OLED_ENABLE
