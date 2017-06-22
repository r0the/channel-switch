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

#include "program.h"
#include "config.h"

Program::Program() :
    _button1(false),
    _button2(false),
    _display1(PIN_CLK, PIN_DATA),
    _display2(PIN_CLK, PIN_DATA),
    _lastButton1(false),
    _lastButton2(false),
    _mutePulseEnd(0),
    _toggle1PulseEnd(0),
    _toggle2PulseEnd(0)
{
    // init pins
    pinMode(PIN_BTN1, INPUT_PULLUP);
    pinMode(PIN_BTN2, INPUT_PULLUP);
    pinMode(PIN_TY1, INPUT_PULLUP);
    pinMode(PIN_TY2, INPUT_PULLUP);

    pinMode(PIN_CS, OUTPUT);

    pinMode(PIN_RQ1, OUTPUT);
    digitalWrite(PIN_RQ1, LOW);

    pinMode(PIN_RQ2, OUTPUT);
    digitalWrite(PIN_RQ2, LOW);

    pinMode(PIN_MUTE, OUTPUT);
    digitalWrite(PIN_MUTE, LOW);

    pinMode(PIN_DIR, OUTPUT);
    digitalWrite(PIN_DIR, LOW);

    // init display 1
    SB6432& display1 = selectDisplay1();
    display1.begin();
    display1.setFontScale(2);

    // init display 2
    SB6432& display2 = selectDisplay2();
    display2.begin();
    display2.setFontScale(2);

    _mode = new OnAir(*this);
}

void Program::loop() {
    // check for end of pulse
    _now = millis();
    if (_toggle1PulseEnd <= _now) {
        digitalWrite(PIN_RQ1, LOW);
    }

    if (_toggle2PulseEnd <= _now) {
        digitalWrite(PIN_RQ2, LOW);
    }

    if (_mutePulseEnd <= _now) {
        digitalWrite(PIN_MUTE, LOW);
    }

    // read inputs
    _button1 = digitalRead(PIN_BTN1) == LOW;
    _button2 = digitalRead(PIN_BTN2) == LOW;
    _channel1 = digitalRead(PIN_TY1) == HIGH;
    _channel2 = digitalRead(PIN_TY2) == HIGH;

    // program logic
    _mode->loop(*this);

    // save last button states for edge detection
    _lastButton1 = _button1;
    _lastButton2 = _button2;
}

SB6432& Program::selectDisplay1() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, LOW);
    delay(CS_DELAY);
    return _display1;
}

SB6432& Program::selectDisplay2() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, HIGH);
    delay(CS_DELAY);
    return _display2;
}

void Program::toggleChannel1() {
    _toggle1PulseEnd = _now + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ1, HIGH);
}

void Program::toggleChannel2() {
    _toggle2PulseEnd = _now + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ2, HIGH);
}

void Program::sendMutePulse() {
    _mutePulseEnd = _now + PULSE_LENGTH_MS;
    digitalWrite(PIN_MUTE, HIGH);
}

void Program::setDirection(bool active) {
    if (active) {
        digitalWrite(PIN_DIR, HIGH);
    }
    else {
        digitalWrite(PIN_DIR, LOW);
    }
}

