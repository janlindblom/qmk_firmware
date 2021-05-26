/**
 * @file config.h
 * @author Jan Lindblom (jan@namnlos.io)
 * @version 0.1
 * @date 2022-04-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifdef SPLIT_KEYBOARD
#    if defined(BOOTLOADER_CATERINA) && defined(__AVR__) && defined(__AVR_ATmega32U4__)
// Only if we're looking at a two-promicro split setup.
#        define SPLIT_LAYER_STATE_ENABLE
#        define SPLIT_LED_STATE_ENABLE
#        define SPLIT_MODS_ENABLE
#        ifdef WPM_ENABLE
#            define SPLIT_WPM_ENABLE
#        endif
#        ifdef OLED_ENABLE
#            define SPLIT_OLED_ENABLE
#        endif
#    endif
#endif

#ifdef OLED_ENABLE
#    define OLED_DISABLE_TIMEOUT

#    ifndef OLED_BRIGHTNESS
#        define OLED_BRIGHTNESS 120
#    endif
#    ifdef OLED_FONT_H
#        undef OLED_FONT_H
#    endif
#    define OLED_FONT_H "oled_font.h"
#    define OLED_FONT_END 255

#    ifndef OLED_IC_SH1107
#        define OLED_IC_SH1107 2
#    endif

#    ifdef OLED_DISPLAY_64X128
#        if (defined(OLED_IC) && (OLED_IC == OLED_IC_SH1107)) || defined(OLED_DRIVER_SH1107)
#            if !defined(OLED_IC) || (defined(OLED_IC) && (OLED_IC != OLED_IC_SH1107))
#                ifdef OLED_IC
#                    undef OLED_IC
#                endif
#                define OLED_IC OLED_IC_SH1107
#            endif

#            define OLED_DISPLAY_CUSTOM
#            define OLED_DISPLAY_WIDTH 64
#            define OLED_DISPLAY_HEIGHT 128
#            define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#            define OLED_BLOCK_TYPE uint32_t
#            define OLED_SOURCE_MAP \
                { 32, 40, 48, 56 }
#            define OLED_TARGET_MAP \
                { 24, 16, 8, 0 }
#            define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#            define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#            define OLED_COM_PINS COM_PINS_ALT
#            ifndef OLED_BRIGHTNESS
#                define OLED_BRIGHTNESS 120
#            endif
#            undef OLED_UPDATE_INTERVAL
#            define OLED_UPDATE_INTERVAL 100
#        endif
#    endif
#endif
