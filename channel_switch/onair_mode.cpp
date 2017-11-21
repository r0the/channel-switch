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

#include "onair_mode.h"

#define STATE_ON_AIR        0
#define STATE_DIRECTION     1
#define STATE_MUTE          2
#define STATE_CHANNEL_ERROR 3
#define STATE_COMM_ERROR    4

static uint8_t determineState(Switchboard& switchboard) {
    if (switchboard.commError()) {
        return STATE_COMM_ERROR;
    }

    if (switchboard.channel1()) {
        return STATE_ON_AIR;
    }
    else {
        if (switchboard.button2()) {
            return STATE_DIRECTION;
        }
        else {
            return STATE_MUTE;
        }        
    }
}

void OnAirMode::setupDisplay(MonoGfx& display) {
    display.setFontScale(2);
    display.setTextAlign(ALIGN_CENTER);
}

void OnAirMode::loop(Switchboard& switchboard) {
    uint8_t lastState = _state;
    _state = determineState(switchboard);
    switchboard.setDirection(_state == STATE_DIRECTION);

    // if button 1 has gone down, dispatch on-air/off-air request
    if (switchboard.button1Down()) {
        switchboard.toggleChannel1();
    }

    // if button 2 has gone down, try to activate direction mode
    if (switchboard.button2Down()) { 
        _onAir = switchboard.channel1();
        // if we are on-air, request to go off-air
        if (_onAir) {
            switchboard.toggleChannel1();
        }
    }

    // if button 2 has been released and FLAG is still set, send on-air request
    if (!switchboard.button2()) {
        if (_onAir && !switchboard.channel1()) {
            switchboard.toggleChannel1();
            _onAir = false;
        }
    }

    if (lastState != _state) {
        switchboard.display1Dirty();
    }

    if (lastState != _state) {
        switchboard.display2Dirty();        
    }
}

void OnAirMode::updateDisplay1(MonoGfx& display) {
    if (_state == STATE_COMM_ERROR) {
        display.setBackgroundColor(255, 0, 0);
        display.fill(MODE_CLEAR);
        display.write(31, 23, "Comm");
        return;
    }

    if (_state == STATE_ON_AIR) {
        display.setBackgroundColor(255, 0, 0);
        display.fill(MODE_CLEAR);
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.write(31, 23, "ON AIR");
    }
    else {
        display.setBackgroundColor(50, 50, 50);
        display.fill(MODE_CLEAR);
        display.write(33, 23, "OFFAIR");
    }
}

void OnAirMode::updateDisplay2(MonoGfx& display) {
    display.fill(MODE_CLEAR);
    if (_state == STATE_COMM_ERROR) {
        display.setBackgroundColor(255, 0, 0);
        display.fill(MODE_CLEAR);
        display.write(31, 23, "Error");
        return;
    }

    if (_state == STATE_DIRECTION) {
        display.setBackgroundColor(0, 0, 255);
        display.fill(MODE_CLEAR);
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
    }
    else {
        display.setBackgroundColor(0, 0, 50);
        display.fill(MODE_CLEAR);
    }

    display.write(31, 23, "REGIE");
}

