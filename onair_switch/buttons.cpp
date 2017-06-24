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

#include "buttons.h"
#include "config.h"

void Buttons::setup() {
    _button1 = false;
    _button2 = false;
    _lastButton1 = false;
    _lastButton2 = false;
    _longPressEnd = 0;
    pinMode(PIN_BTN1, INPUT_PULLUP);
    pinMode(PIN_BTN2, INPUT_PULLUP);
}


void Buttons::loop() {
    // read inputs
    _button1 = digitalRead(PIN_BTN1) == LOW;
    _button2 = digitalRead(PIN_BTN2) == LOW;
    _button1Down = _button1 && !_lastButton1;
    _button2Down = _button2 && !_lastButton2;
    _lastButton1 = _button1;
    _lastButton2 = _button2;
    
    unsigned long now = millis();
    if (!_button1 || !_button2) {
        _longPressEnd = now + LONG_PRESS_MS;
    }

    _longPress = _longPressEnd <= now;
}

