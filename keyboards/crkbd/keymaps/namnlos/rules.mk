OLED_ENABLE        = yes
LOCAL_GLCDFONT     = yes
RGBLIGHT_ENABLE    = no   # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE  = no
MOUSEKEY_ENABLE    = no   # Mouse keys, needed for baller
TAP_DANCE_ENABLE   = yes  # Let's dance
UNICODE_ENABLE     = yes  # Unicode
COMBO_ENABLE       = no   # Combos
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE   = no
EXTRAKEY_ENABLE    = yes  # Audio control and System control
WPM_ENABLE         = yes  # WPM counter enabled
NKRO_ENABLE        = yes  # USB Nkey Rollover
BLUETOOTH_ENABLE   = no   # Enable Bluetooth with the Adafruit EZ-Key HID
SWAP_HANDS_ENABLE  = no   # Enable one-hand typing
BACKLIGHT_ENABLE   = no   # Enable keyboard backlight functionality
MIDI_ENABLE        = no   # MIDI controls
AUDIO_ENABLE       = no   # Audio output on port C6
SLEEP_LED_ENABLE   = yes  # Breathing sleep LED during USB suspend
BOOTMAGIC_ENABLE   = yes  # Enable Bootmagic Lite
COMMAND_ENABLE     = yes  # Commands for debug and configuration
DEFERRED_EXEC_ENABLE        = yes
DEBOUNCE_TYPE               = sym_eager_pr
RENDER_PET					= yes
RENDER_KEYBOARD_LOGO        = yes
OLED_VERTICAL               = yes
#OLED_DRIVER = custom
ENCODER_ENABLE              = no
CONSOLE_ENABLE              = no
DEBUG                       = no
DYNAMIC_KEYMAP_ENABLE       = no
APPLICATION_ICONS           = no
LTO_ENABLE = yes

EXTRAFLAGS += -flto

#Debug options
VERBOSE = no
