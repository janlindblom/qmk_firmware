# Common stuff for namnlos keymaps.
SRC += $(USER_PATH)/namnlos.c

MIDI_ENABLE          ?= no
AUDIO_ENABLE         ?= no
TAP_DANCE_ENABLE     ?= yes  # Let's dance
UNICODE_ENABLE       ?= yes    # Unicode
SPACE_CADET_ENABLE   ?= no
GRAVE_ESC_ENABLE     ?= no
OLED_ENABLE          ?= no
DEFERRED_EXEC_ENABLE ?= yes
CUSTOM_OLED_DRIVER   ?= no

ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(strip $(OLED_DRIVER)), custom)
        ifeq ($(strip $(CUSTOM_OLED_IC)), SH1107)
            OPT_DEFS += -DOLED_ENABLE \
                -DOLED_DRIVER_SH1107
            SRC += $(USER_PATH)/sh1107.c
            QUANTUM_LIB_SRC += i2c_master.c
        endif
    endif
    ifeq ($(strip $(CUSTOM_OLED_DRIVER)), yes)
        OPT_DEFS += -DCUSTOM_OLED_DRIVER
    endif
endif
