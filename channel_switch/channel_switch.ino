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
#include "switchboard.h"

Behaviour* behaviour;

void setup() {
//    Serial.begin(9600);
//    while (!Serial) { delay(1); }
//    Serial.println("Debugging");
    
    pinMode(PIN_DEV1, INPUT_PULLUP);
    pinMode(PIN_DEV2, INPUT_PULLUP);
    delay(100);
    if (digitalRead(PIN_DEV1) == HIGH) {
        behaviour = new Base;
    }
    else {
        behaviour = new Switchboard;
    }

    behaviour->setup();
}

void loop() {
    behaviour->loop();
}

