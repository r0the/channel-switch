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

#include "serial_comm.h"
#include "config.h"

void SerialComm::setup() {
    Serial1.begin(COMM_BAUD_RATE);
    _channel1 = false;
    _channel2 = false;
    _lastSignal = 0;
}

void SerialComm::loop() {
    unsigned long now = millis();
    if (Serial1.available()) {
        uint8_t state = Serial1.read();
        _channel1 = state & 0x01;
        _channel2 = state & 0x02;
        _lastSignal = now;
    }

    _error = now - _lastSignal > COMM_TIMEOUT;
}

bool SerialComm::channel1() const {
    return _channel1;
}

bool SerialComm::channel2() const {
    return _channel2;
}

bool SerialComm::error() const {
    return _error;
}

void SerialComm::setDirection(bool active) {
    if (active) {
        Serial1.write(CMD_DIRECTION_ENABLE);
    }
    else {
        Serial1.write(CMD_DIRECTION_DISABLE);
    }
}

void SerialComm::toggleChannel1() {
    Serial1.write(CMD_TOGGLE_CHANNEL_1);
}

void SerialComm::toggleChannel2() {
    Serial1.write(CMD_TOGGLE_CHANNEL_2);
}

void SerialComm::toggleMute() {
    Serial1.write(CMD_TOGGLE_MUTE);
}

