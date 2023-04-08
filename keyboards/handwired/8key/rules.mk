# Copyright 2023 Jan Lindblom (@janlindblom)
# SPDX-License-Identifier: GPL-2.0-or-later

SPACE_CADET_ENABLE = no
TERMINAL_ENABLE = no
OLED_ENABLE = yes

ifneq ($(PLATFORM),CHIBIOS)
    ifneq ($(strip $(LTO_SUPPORTED)), no)
        LTO_ENABLE = yes
    endif
endif

ifeq ($(KEYMAP), thepaintbrush_left)
    OPT_DEFS += -DDIRECT_PINS="{ { F7, F6, F5, F4 }, { B6, B2, B3, B1 } }"
else
    OPT_DEFS += -DDIRECT_PINS="{ { F4, F5, F6, F7 }, { B1, B3, B2, B6 } }"
endif
