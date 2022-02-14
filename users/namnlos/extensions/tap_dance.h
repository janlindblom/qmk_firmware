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

#ifdef TAP_DANCE_ENABLE
#    include "process_tap_dance.h"

typedef struct {
    uint16_t kc1;
    uint16_t kc2;
    uint16_t kc3;
} qk_tap_dance_triple_t;

#    define ACTION_TAP_DANCE_TRIPLE(kc1, kc2, kc3) \
        { .fn = {qk_tap_dance_triple_on_each_tap, qk_tap_dance_triple_finished, qk_tap_dance_triple_reset}, .user_data = (void *)&((qk_tap_dance_triple_t){kc1, kc2, kc3}), }

void qk_tap_dance_triple_on_each_tap(tap_dance_state_t *state, void *user_data);
void qk_tap_dance_triple_finished(tap_dance_state_t *state, void *user_data);
void qk_tap_dance_triple_reset(tap_dance_state_t *state, void *user_data);
#endif
