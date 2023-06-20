#----------------------------------------------------------------------------
# make gboards/gergo:namnlos:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
BALLER = no             # Enable to ball out
BALLSTEP = 20           # Multiple in px to move, multiplied by layer number
SCROLLSTEP = 1          # Lines to scroll with ball

MOUSEKEY_ENABLE             = yes   # Mouse keys, needed for baller
OLED_ENABLE                 = yes
WPM_ENABLE                  = yes
TAP_DANCE_ENABLE            = yes
UNICODE_ENABLE              = yes
DEFERRED_EXEC_ENABLE        = yes
COMMAND_ENABLE              = no
NKRO_ENABLE                 = yes
DEBOUNCE_TYPE               = sym_eager_pr
RENDER_PET                  = yes
OLED_VERTICAL               = yes
APPLICATION_ICONS           = yes

# Saving space, make sure _everything_ we're not using is disabled
MIDI_ENABLE                 = no
AUDIO_ENABLE                = no
SPACE_CADET_ENABLE          = no
GRAVE_ESC_ENABLE            = no
BACKLIGHT_ENABLE            = no
COMBO_ENABLE                = no
ENCODER_ENABLE              = no
RGBLIGHT_ENABLE             = no
RGB_MATRIX_ENABLE           = no
CONSOLE_ENABLE              = no
VERBOSE                     = no
DEBUG                       = no
DYNAMIC_KEYMAP_ENABLE       = no

LTO_ENABLE                  = yes
#Debug options
DEBUG_MATRIX_SCAN_RATE      = no
DEBUG_BALLER                = no
DEBUG_MATRIX                = no

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
SRC += matrix.c i2c_master.c
ifneq ($(strip $(BALLSTEP)),)
    OPT_DEFS += -DTRKSTEP=$(strip $(BALLSTEP))
endif
ifneq ($(strip $(SCROLLSTEP)),)
    OPT_DEFS += -DSCROLLSTEP=$(strip $(SCROLLSTEP))
endif
ifeq ($(strip $(BALLER)), yes)
    POINTING_DEVICE_ENABLE	= yes
    OPT_DEFS += -DBALLER
endif
ifeq ($(strip $(DEBUG_BALLER)), yes)
    OPT_DEFS += -DDEBUG_BALLER
endif
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
