/*
 * Copyright (C) 2017 by Stefan Rothe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "base.h"
#include "config.h"
#include "context.h"

// TODO: delay mute display
// TODO: center text

Behaviour* behaviour;


void setup() {
    pinMode(PIN_BOARD_1, INPUT_PULLUP);
    pinMode(PIN_BOARD_2, INPUT_PULLUP);
    delay(100);
    if (digitalRead(PIN_BOARD_1) == HIGH) {
        behaviour = new Base;
    }
    else {
        behaviour = new Context;
    }

    behaviour->setup();
}

void loop() {
    behaviour->loop();
}

