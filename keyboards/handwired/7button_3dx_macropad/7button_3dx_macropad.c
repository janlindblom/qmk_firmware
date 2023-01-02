// Copyright 2022 Jan Lindblom (@janlindblom)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "7button_3dx_macropad.h"

void keyboard_post_init_kb(void) {
#if defined(BOOTLOADER_CATERINA) && defined(__AVR__) && defined(__AVR_ATmega32U4__)
    DDRD &= ~(1 << 5);
    PORTD &= ~(1 << 5);

    DDRB &= ~(1 << 0);
    PORTB &= ~(1 << 0);
#endif
    keyboard_post_init_user();
}
