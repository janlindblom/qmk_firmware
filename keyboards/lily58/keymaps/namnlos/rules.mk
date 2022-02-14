BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no         # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE= yes            # OLED display
MAGIC_ENABLE = yes
TAP_DANCE_ENABLE = yes  # Let's dance
UNICODE_ENABLE = no     # Unicode
COMBO_ENABLE = no       # Combos
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
LOCAL_GLCDFONT = yes
WPM_ENABLE = yes

VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
EXTRAFLAGS += -flto

SRC +=  ./lib/logo_reader.c
