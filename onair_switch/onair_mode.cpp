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

void OnAirMode::setup() {
    _displayOnAir = false;
    _displayDirection = false;
}

void OnAirMode::setupDisplay(SB6432& display) {
    display.setFontScale(2);
    display.setTextAlign(ALIGN_CENTER);
}

void OnAirMode::loop(Switchboard& switchboard) {
    _displayCommError = switchboard.commError();

    // update display 1 to reflect state of channel 1
    if (_displayOnAir != switchboard.channel1()) {
        _displayOnAir = switchboard.channel1();
        switchboard.display1Dirty();
    }

    // activate direction, if button 2 is pressed and we are off-air
    bool direction = switchboard.button2() && !switchboard.channel1();
    switchboard.setDirection(direction);
    // update display 2
    if (_displayDirection != direction) {
        _displayDirection = direction;
        switchboard.display2Dirty();
    }

    // if button 1 has gone down, dispatch on-air/off-air request
    if (switchboard.button1Down()) {
        switchboard.toggleChannel1();
    }

    // if button 2 has gone down, try to activate direction mode
    if (switchboard.button2Down()) { 
        _onAirBeforeDirection = switchboard.channel1();
        // if we are on-air, request to go off-air
        if (_onAirBeforeDirection) {
            switchboard.toggleChannel1();
        }
    }

    // if button 2 has been released and FLAG is still set, send on-air request
    if (!switchboard.button2()) {
        if (_onAirBeforeDirection && !switchboard.channel1()) {
            switchboard.toggleChannel1();
            _onAirBeforeDirection = false;
        }
    }
}

void OnAirMode::updateDisplay1(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_displayCommError) {
        display.write(31, 23, "Comm");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    if (_displayOnAir) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.write(31, 23, "ON AIR");
        display.setBacklightColor(255, 0, 0);
    }
    else {
        display.setBacklightColor(50, 50, 50);
        display.write(31, 23, "OFFAIR");
    }
}

void OnAirMode::updateDisplay2(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_displayCommError) {
        display.write(31, 23, "Error");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    if (_displayDirection) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.setBacklightColor(0, 0, 255);
    }
    else {
        display.setBacklightColor(0, 0, 50);
    }

    display.write(31, 23, "REGIE");
}

