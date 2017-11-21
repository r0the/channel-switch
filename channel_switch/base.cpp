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

void Base::setup() {
    Serial1.begin(COMM_BAUD_RATE);
    _comm.setup();
    _nextSend = 0;
}


void Base::loop() {
    _comm.loop();
    unsigned long now = millis();
    if (Serial1.available() >= 3) {
        if (checkHeader()) {
            char cmd = Serial1.read();
            switch (cmd) {
                case CMD_TOGGLE_CHANNEL_1:
                    _comm.toggleChannel1();
                    break;
                case CMD_TOGGLE_CHANNEL_2:
                    _comm.toggleChannel2();
                    break;
                case CMD_TOGGLE_MUTE:
                    _comm.toggleMute();
                    break;
                case CMD_DIRECTION_ENABLE:
                    _comm.setDirection(true);
                    break;
                case CMD_DIRECTION_DISABLE:
                    _comm.setDirection(false);
                    break;
            }
        }
    }

    if (_nextSend < now) {
        _nextSend = now + COMM_KEEPALIVE_MS;
        uint8_t data = 0;
        if (_comm.channel1()) {
            data += 1;
        }

        if (_comm.channel2()) {
            data += 2;
        }

        writeHeader();
        Serial1.write(data);
    }
}

