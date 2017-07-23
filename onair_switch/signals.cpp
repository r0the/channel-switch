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

#include "signals.h"
#include "config.h"

static uint8_t activeTally() {
    switch (CONFIG.tally()) {
        case TALLY_ACTIVE_LOW:
            return LOW;
        case TALLY_ACTIVE_HIGH:
            return HIGH;
        default:
            return HIGH;
    }
}

void Signals::setup() {
    _channel1 = false;
    _channel2 = false;
    _channel1End = 0;
    _channel2End = 0;
    _muteEnd = 0;

    pinMode(PIN_TY1, INPUT_PULLUP);
    pinMode(PIN_TY2, INPUT_PULLUP);

    pinMode(PIN_RQ1, OUTPUT);
    digitalWrite(PIN_RQ1, LOW);

    pinMode(PIN_RQ2, OUTPUT);
    digitalWrite(PIN_RQ2, LOW);

    pinMode(PIN_MUTE, OUTPUT);
    digitalWrite(PIN_MUTE, LOW);

    pinMode(PIN_DIR, OUTPUT);
    digitalWrite(PIN_DIR, LOW);
}

void Signals::loop() {
    uint8_t active = activeTally();
    _channel1 = digitalRead(PIN_TY1) == active;
    _channel2 = digitalRead(PIN_TY2) == active;

    unsigned long now = millis();
    if (_channel1End <= now) {
        digitalWrite(PIN_RQ1, LOW);
    }

    if (_channel2End <= now) {
        digitalWrite(PIN_RQ2, LOW);
    }

    if (_muteEnd <= now) {
        digitalWrite(PIN_MUTE, LOW);
    }
}

void Signals::setDirection(bool active) {
    digitalWrite(PIN_DIR, active ? HIGH : LOW);
}

void Signals::toggleChannel1() {
    _channel1End = millis() + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ1, HIGH);
}

void Signals::toggleChannel2() {
    _channel2End = millis() + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ2, HIGH);
}

void Signals::toggleMute() {
    _muteEnd = millis() + PULSE_LENGTH_MS;
    digitalWrite(PIN_MUTE, HIGH);
}

