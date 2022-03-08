# Bootloader selection
BOOTLOADER = caterina

MOUSEKEY_ENABLE = no    # Mouse keys, needed for baller
TAP_DANCE_ENABLE = yes  # Let's dance
UNICODE_ENABLE = yes    # Unicode
EXTRAKEY_ENABLE = yes   # for media keys
COMBO_ENABLE = no       # Combos
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
COMMAND_ENABLE = no

LTO_ENABLE = yes
EXTRAFLAGS += -flto
CONSOLE_ENABLE = no

#Debug options
VERBOSE = no
