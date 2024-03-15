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
#include "quantum.h"
#include "tap_dance.h"

#ifdef TAP_DANCE_ENABLE
#include "process_tap_dance.h"

void qk_tap_dance_triple_on_each_tap(tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_triple_t *triple = (qk_tap_dance_triple_t *)user_data;
    if (state->count == 3) {
        register_code16(triple->kc3);
        state->finished = true;
    } else if (state->count == 2) {
        register_code16(triple->kc2);
        state->finished = true;
    }
}

void qk_tap_dance_triple_finished(tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_triple_t *triple = (qk_tap_dance_triple_t *)user_data;

    register_code16(triple->kc1);
}

void qk_tap_dance_triple_reset(tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_triple_t *triple = (qk_tap_dance_triple_t *)user_data;

    if (state->count == 3) {
        wait_ms(TAP_CODE_DELAY);
        unregister_code16(triple->kc3);
    } else if (state->count == 2) {
        unregister_code16(triple->kc2);
    } else if (state->count == 1) {
        unregister_code16(triple->kc1);
    }
}
#endif
