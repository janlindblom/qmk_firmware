ENCODER_ENABLE = no     # Enables the use of one or more encoders
KEY_LOCK_ENABLE = no    # Disable key lock
TERMINAL_ENABLE = no    # Disable terminal
GRAVE_ESC_ENABLE = no   # Disable Grave Escape
MAGIC_ENABLE = no       # Disable magic
SPACE_CADET_ENABLE = no # Disable space cadet
VELOCIKEY_ENABLE = no   # Disable velocikey
OLED_ENABLE = yes       # Enable OLED displays
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
RGBLIGHT_ENABLE = yes   # Enable keyboard RGB underglow
MOUSEKEY_ENABLE = yes   # Mouse keys, needed for baller
TAP_DANCE_ENABLE = yes  # Let's dance
UNICODE_ENABLE = yes    # Unicode
EXTRAKEY_ENABLE = yes   # Audio control and System control
WPM_ENABLE = yes        # WPM counter enabled
NKRO_ENABLE = yes       # USB Nkey Rollover

# Save space on pro micro
EXTRAFLAGS += -flto

#Debug options
VERBOSE = no
