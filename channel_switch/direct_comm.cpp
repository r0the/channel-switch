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

#include "direct_comm.h"
#include "config.h"

void DirectComm::setup() {
    _channel1 = false;
    _channel2 = false;
    _channel1End = 0;
    _channel2End = 0;

    pinMode(PIN_TY1, INPUT_PULLUP);
    pinMode(PIN_TY2, INPUT_PULLUP);

    pinMode(PIN_RQ1, OUTPUT);
    digitalWrite(PIN_RQ1, LOW);

    pinMode(PIN_RQ2, OUTPUT);
    digitalWrite(PIN_RQ2, LOW);

    pinMode(PIN_DIR, OUTPUT);
    digitalWrite(PIN_DIR, LOW);
}

void DirectComm::loop() {
    _channel1 = digitalRead(PIN_TY1) == TALLY_ACTIVE;
    _channel2 = digitalRead(PIN_TY2) == TALLY_ACTIVE;

    unsigned long now = millis();
    if (_channel1End <= now) {
        digitalWrite(PIN_RQ1, LOW);
    }

    if (_channel2End <= now) {
        digitalWrite(PIN_RQ2, LOW);
    }
}


bool DirectComm::channel1() const {
    return _channel1;
}

bool DirectComm::channel2() const {
    return _channel2;
}

bool DirectComm::error() const {
    return false;
}

void DirectComm::setDirection(bool active) {
    digitalWrite(PIN_DIR, active ? HIGH : LOW);
}

void DirectComm::toggleChannel1() {
    _channel1End = millis() + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ1, HIGH);
}

void DirectComm::toggleChannel2() {
    _channel2End = millis() + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ2, HIGH);
}

