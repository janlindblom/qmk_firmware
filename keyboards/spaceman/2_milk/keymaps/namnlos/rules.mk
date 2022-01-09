MCU = atmega32u4

BOOTLOADER = caterina

BOOTMAGIC_ENABLE = no  # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = no  # Audio control and System control
CONSOLE_ENABLE  = no   # Console for debug
COMMAND_ENABLE  = yes  # Commands for debug and configuration
NKRO_ENABLE = yes      # Enable N-Key Rollover
BACKLIGHT_ENABLE  = no # Custom backlighting code is used, so this should not be enabled
AUDIO_ENABLE  = no     # This can be enabled if a speaker is connected to the expansion port. Not compatible with RGBLIGHT below
RGBLIGHT_ENABLE  = yes # This can be enabled if a ws2812 strip is connected to the expansion port.
LTO_ENABLE = yes
