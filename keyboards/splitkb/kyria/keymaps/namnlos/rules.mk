# MCU name
MCU = RP2040
BOOTLOADER = rp2040

# Saving space
COMMAND_ENABLE          = no
SPACE_CADET_ENABLE      = no
GRAVE_ESC_ENABLE        = no
DYNAMIC_KEYMAP_ENABLE   = no
KEY_LOCK_ENABLE         = no
MIDI_ENABLE             = no
AUDIO_ENABLE            = no
TERMINAL_ENABLE         = no
CONSOLE_ENABLE          = no
VERBOSE                 = no
DEBUG                   = no
LTO_ENABLE              = no

# Kyria features
ENCODER_ENABLE          = no
MAGIC_ENABLE            = yes       # Magic
OLED_ENABLE             = yes       # Enable OLED displays
RGBLIGHT_ENABLE         = yes      	# Enable keyboard RGB underglow
MOUSEKEY_ENABLE         = yes      	# Mouse keys
TAP_DANCE_ENABLE        = yes		# Let's dance
UNICODE_ENABLE          = yes       # Unicode
EXTRAKEY_ENABLE         = yes      	# Audio control and System control
WPM_ENABLE              = yes       # WPM counter enabled
NKRO_ENABLE             = yes       # USB Nkey Rollover
DEFERRED_EXEC_ENABLE    = yes
KEY_OVERRIDE_ENABLE     = yes

# Driver selections
OLED_DRIVER             = SSD1306
WS2812_DRIVER           = vendor    # RP2040 ws2812 driver
SERIAL_DRIVER           = vendor    # RP2040 serial driver

# Namnlos features
RENDER_PET = yes

CONVERT_TO=kb2040
DEFAULT_FOLDER = splitkb/kyria/rev1
