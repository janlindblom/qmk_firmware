# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = no          # Commands for debug and configuration
NKRO_ENABLE = yes            # USB Nkey Rollover
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
BACKLIGHT_ENABLE   = no      # Enable keyboard backlight functionality
MIDI_ENABLE        = no      # MIDI controls
AUDIO_ENABLE       = no      # Audio output on port C6
UNICODE_ENABLE     = yes     # Unicode
BLUETOOTH_ENABLE   = no      # Enable Bluetooth with the Adafruit EZ-Key HID
SWAP_HANDS_ENABLE  = no      # Enable one-hand typing

ENCODER_ENABLE = yes
OLED_ENABLE = yes
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = no
SPLIT_KEYBOARD = yes
SLEEP_LED_ENABLE = no

LTO_ENABLE = yes
