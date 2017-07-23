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

OnAirMode::OnAirMode() :
    _displayOnAir(false),
    _displayDirection(false)
{
}

void OnAirMode::initDisplay1(SB6432& display) {
    display.setFontScale(2);
}

void OnAirMode::initDisplay2(SB6432& display) {
    display.setFontScale(2);
}

void OnAirMode::loop(Context& context) {
    // update display 1 to reflect state of channel 1
    if (_displayOnAir != context.channel1()) {
        _displayOnAir = context.channel1();
        context.display1Dirty();
    }

    // activate direction, if button 2 is pressed and we are off-air
    bool direction = context.button2() && !context.channel1();
    context.setDirection(direction);
    // update display 2
    if (_displayDirection != direction) {
        _displayDirection = direction;
        context.display2Dirty();
    }

    // if button 1 has gone down, dispatch on-air/off-air request
    if (context.button1Down()) {
        context.toggleChannel1();
    }

    // if button 2 has gone down, try to activate direction mode
    if (context.button2Down()) { 
        _onAirBeforeDirection = context.channel1();
        // if we are on-air, request to go off-air
        if (_onAirBeforeDirection) {
            context.toggleChannel1();
        }
    }

    // if button 2 has been released and FLAG is still set, send on-air request
    if (!context.button2()) {
        if (_onAirBeforeDirection && !context.channel1()) {
            context.toggleChannel1();
            _onAirBeforeDirection = false;
        }
    }
}

void OnAirMode::updateDisplay1(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_displayOnAir) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.write(4, 23, "ON AIR");
        display.setBacklightColor(255, 0, 0);
    }
    else {
        display.setBacklightColor(50, 50, 50);
        display.write(1, 23, "OFFAIR");
    }
}

void OnAirMode::updateDisplay2(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_displayDirection) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.setBacklightColor(0, 0, 255);
    }
    else {
        display.setBacklightColor(0, 0, 50);
    }

    display.write(4, 23, "REGIE");
}

