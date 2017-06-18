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
    _display1(PIN_DISPLAY_CLOCK, PIN_DISPLAY_DATA),
    _display2(PIN_DISPLAY_CLOCK, PIN_DISPLAY_DATA),
    _lang1PulseEnd(0),
    _lang2PulseEnd(0),
    _lastButton1(false),
    _lastButton2(false),
    _mutePulseEnd(0)
{
    // init pins
    pinMode(PIN_TALLY_1, INPUT_PULLUP);
    pinMode(PIN_TALLY_2, INPUT_PULLUP);

    // init display 1
    selectDisplay1();
    display().begin();
    display().setFontScale(2);
    // init display 2
    selectDisplay2();
    display().begin();
    display().setFontScale(2);
    _mode = new OnAir(*this);
}

void Program::loop() {
    // check for end of pulse
    _now = millis();
    if (_lang1PulseEnd <= _now) {
        digitalWrite(PIN_LANG_1, LOW);
    }

    if (_lang2PulseEnd <= _now) {
        digitalWrite(PIN_LANG_2, LOW);
    }

    if (_mutePulseEnd <= _now) {
        digitalWrite(PIN_MUTE, LOW);
    }

    // read inputs
    _button1 = digitalRead(PIN_BUTTON_1) == LOW;
    _button2 = digitalRead(PIN_BUTTON_2) == LOW;
    _tally1 = digitalRead(PIN_TALLY_1) == HIGH;
    _tally2 = digitalRead(PIN_TALLY_2) == HIGH;

    // program logic
    _mode->loop(*this);

    // save last button states for edge detection
    _lastButton1 = _button1;
    _lastButton2 = _button2;
}

void Program::selectDisplay1() {
    delay(CS_DELAY);
    digitalWrite(PIN_DISPLAY_CS, LOW);
    delay(CS_DELAY);
    _display = &_display1;
}

void Program::selectDisplay2() {
    delay(CS_DELAY);
    digitalWrite(PIN_DISPLAY_CS, HIGH);
    delay(CS_DELAY);
    _display = &_display2;
}

void Program::sendLang1Pulse() {
    _lang1PulseEnd = _now + PULSE_LENGTH_MS;
}

void Program::sendLang2Pulse() {
    _lang2PulseEnd = _now + PULSE_LENGTH_MS;
}

void Program::sendMutePulse() {
    _mutePulseEnd = _now + PULSE_LENGTH_MS;
}


