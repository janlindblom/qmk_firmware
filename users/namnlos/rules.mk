# Common stuff for namnlos keymaps.
SRC += $(USER_PATH)/namnlos.c \
	$(USER_PATH)/extensions/tap_dance.c \
	$(USER_PATH)/control/control_idle.c \
	$(USER_PATH)/lights/rgb_layer.c

# Namnlos keymap defaults
BOOTMAGIC_ENABLE			?= yes
TAP_DANCE_ENABLE			?= yes
UNICODE_ENABLE				?= yes
OLED_ENABLE					?= yes
DEFERRED_EXEC_ENABLE		?= yes
BACKLIGHT_ENABLE			?= no
KEY_OVERRIDE_ENABLE			?= no
MOUSEKEY_ENABLE				?= yes
EXTRAKEY_ENABLE				?= yes
COMBO_ENABLE				= no
COMMAND_ENABLE				?= yes
NKRO_ENABLE					?= yes
ENCODER_ENABLE				?= no
RGBLIGHT_ENABLE				?= no
RGB_MATRIX_ENABLE			?= no
WPM_ENABLE					?= yes
DEBOUNCE_TYPE				?= sym_eager_pr
SPACE_CADET_ENABLE			?= no
GRAVE_ESC_ENABLE			?= no
DYNAMIC_KEYMAP_ENABLE		?= no
KEY_LOCK_ENABLE 			?= no
MIDI_ENABLE					?= no
AUDIO_ENABLE				?= no
AUTOCORRECT_ENABLE			?= no
TERMINAL_ENABLE 			?= no
CONSOLE_ENABLE				?= no
OS_DETECTION_ENABLE			?= yes

VERBOSE						?= no
DEBUG						?= no
AVR_USE_MINIMAL_PRINTF		?= yes
LTO_ENABLE					?= yes

CUSTOM_OLED_DRIVER			?= no
HUFFMAN_ENABLE				?= no
RENDER_PET					?= no
RENDER_KEYBOARD_LOGO		?= no
LZFX_ENABLE					?= no
LZFX_COMPRESS_ENABLE		?= no
LZFX_DECOMPRESS_ENABLE		?= no
OLED_VERTICAL				?= no
EXTRA_FUNCTION_LAYER		?= no
APPLICATION_ICONS			?= no
PROMICRO_LED_STATUS			?= no
CUSTOM_OLED_SLEEP			?= no

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
    DEFERRED_EXEC_ENABLE = yes
endif

ifeq ($(strip $(PROMICRO_LED_STATUS)), yes)
	OPT_DEFS += -DPROMICRO_LED_STATUS
	SRC += $(USER_PATH)/lights/status_leds.c
endif

ifeq ($(strip $(APPLICATION_ICONS)), yes)
	OPT_DEFS += -DAPPLICATION_ICONS
endif

ifeq ($(strip $(OLED_VERTICAL)), yes)
	OPT_DEFS += -DOLED_VERTICAL
else
	OPT_DEFS += -DOLED_HORIZONTAL
endif

ifeq ($(strip $(EXTRA_FUNCTION_LAYER)), yes)
	OPT_DEFS += -DEXTRA_FUNCTION_LAYER
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled/oled_functions.c \
		$(USER_PATH)/oled/icons.c \
		$(USER_PATH)/oled/oled_control.c \
		$(USER_PATH)/oled/oled_wpm.c \
		$(USER_PATH)/oled/oled_pet.c

	ifeq ($(strip $(CUSTOM_OLED_SLEEP)), yes)
		OPT_DEFS += -DCUSTOM_OLED_SLEEP
	endif

	ifeq ($(strip $(OLED_DRIVER)), custom)
		ifeq ($(strip $(CUSTOM_OLED_DRIVER)), sh1107)
			OPT_DEFS += -DOLED_DRIVER_SH1107
			SRC += $(USER_PATH)/oled/sh110x.c
		endif
		QUANTUM_LIB_SRC += i2c_master.c
	endif
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += $(USER_PATH)/lights/rgb_layer.c
endif

ifeq ($(strip $(RENDER_PET)), yes)
	OPT_DEFS += -DRENDER_PET
endif

ifeq ($(strip $(RENDER_KEYBOARD_LOGO)), yes)
	OPT_DEFS += -DRENDER_KEYBOARD_LOGO
endif

ifeq ($(strip $(LTO_ENABLE)), yes)
	EXTRAFLAGS += -flto
endif

ifeq ($(strip $(LZFX_ENABLE)), yes)
	SRC += $(USER_PATH)/lzfx.c
	OPT_DEFS += -DLZFX \
		-DLZFX_COMPRESS \
		-DLZFX_DECOMPRESS
else
	ifeq ($(strip $(LZFX_COMPRESS_ENABLE)), yes)
		SRC += $(USER_PATH)/lzfx.c
		OPT_DEFS += -DLZFX_COMPRESS
	endif
	ifeq ($(strip $(LZFX_DECOMPRESS_ENABLE)), yes)
		SRC += $(USER_PATH)/lzfx.c
		OPT_DEFS += -DLZFX_DECOMPRESS
	endif
endif
