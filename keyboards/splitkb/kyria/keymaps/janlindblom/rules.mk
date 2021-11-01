ENCODER_ENABLE = no     # Enables the use of one or more encoders
KEY_LOCK_ENABLE = no
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
TERMINAL_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
AUDIO_ENABLE = no
VELOCIKEY_ENABLE = no
BACKLIGHT_ENABLE = no
OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
RGBLIGHT_ENABLE = yes   # Enable keyboard RGB underglow
MOUSEKEY_ENABLE = yes   # Mouse keys, needed for baller
TAP_DANCE_ENABLE = yes  # Let's dance
UNICODE_ENABLE = yes    # Unicode
EXTRAKEY_ENABLE = yes      # Audio control and System control
WPM_ENABLE = yes

EXTRAFLAGS += -flto

#Debug options
VERBOSE = no
