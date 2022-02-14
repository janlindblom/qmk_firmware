/**
 * Copyright © 2022 Jan Lindblom (@janlindblom)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "quantum.h"
#include "namnlos.h"

#ifdef OLED_ENABLE
uint8_t PET_OFFSET(uint8_t offset);
void    render_keyboard_logo(void);
#    ifdef RENDER_PET
void     render_pet(void);
bool     render_pet_keymap(void);
bool     render_pet_user(void);
uint32_t pet_animation_phases(uint32_t triger_time, void *cb_arg);
#        ifdef DEFERRED_EXEC_ENABLE
extern deferred_token pet_token;
void                  pet_control_on(uint32_t delay);
void                  pet_control_off(void);
#        endif // DEFERRED_EXEC_ENABLE
#    endif                      // RENDER_PET
#endif                          // OLED_ENABLE
