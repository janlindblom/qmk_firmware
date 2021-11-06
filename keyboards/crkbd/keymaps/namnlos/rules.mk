OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LOCAL_GLCDFONT = yes
RGBLIGHT_ENABLE = yes   # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = no
MOUSEKEY_ENABLE = yes   # Mouse keys, needed for baller
TAP_DANCE_ENABLE = yes  # Let's dance
UNICODE_ENABLE = yes    # Unicode
COMBO_ENABLE = no       # Combos
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
EXTRAKEY_ENABLE = yes   # Audio control and System control
WPM_ENABLE = yes        # WPM counter enabled
NKRO_ENABLE = yes       # USB Nkey Rollover

LTO_ENABLE = yes

EXTRAFLAGS += -flto

#Debug options
VERBOSE = no
