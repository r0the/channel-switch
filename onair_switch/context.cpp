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

#include <EEPROM.h>
#include "context.h"
#include "config.h"
#include "onair.h"
#include "prog.h"
#include "translate.h"

#define MODE_ADDRESS 1

Context::Context() :
    _button1(false),
    _button2(false),
    _channel1(false),
    _channel2(false),
    _display1(PIN_CLK, PIN_DATA),
    _display1Dirty(false),
    _display2(PIN_CLK, PIN_DATA),
    _display2Dirty(false),
    _lastButton1(false),
    _lastButton2(false),
    _mode(NULL),
    _modeId(0),
    _mutePulseEnd(0),
    _now(0),
    _programmingModeStart(0),
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
    selectDisplay1();
    _display1.begin();

    // init display 2
    selectDisplay2();
    _display2.begin();

    setMode(EEPROM.read(MODE_ADDRESS));
}

void Context::loop() {
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

    if (!_button1 || !_button2) {
        _programmingModeStart = _now + PROGRAMMING_MODE_TIMEOUT;
    }

    if (_programmingModeStart <= _now) {
        initMode(new Prog);
    }

    // program logic
    _mode->loop(*this);

    // save last button states for edge detection
    _lastButton1 = _button1;
    _lastButton2 = _button2;

    if (_display1Dirty) {
        selectDisplay1();
        _mode->updateDisplay1(_display1);
        _display1.update();
        _display1Dirty = false;
    }

    if (_display2Dirty) {
        selectDisplay2();
        _mode->updateDisplay2(_display2);
        _display2.update();
        _display2Dirty = false;
    }
}

void Context::setMode(uint8_t modeId) {
    if (modeId >= MODE_COUNT) {
        modeId = MODE_ON_AIR;
    }

    _modeId = modeId;
    EEPROM.update(MODE_ADDRESS, _modeId);
    switch (modeId) {
        case MODE_ON_AIR:
            initMode(new OnAir);
            break;
        case MODE_TRANSLATE:
            initMode(new Translate);
            break;
    }
}

uint8_t Context::mode() const {
    return _modeId;
}

void Context::toggleChannel1() {
    _toggle1PulseEnd = _now + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ1, HIGH);
}

void Context::toggleChannel2() {
    _toggle2PulseEnd = _now + PULSE_LENGTH_MS;
    digitalWrite(PIN_RQ2, HIGH);
}

void Context::sendMutePulse() {
    _mutePulseEnd = _now + PULSE_LENGTH_MS;
    digitalWrite(PIN_MUTE, HIGH);
}

void Context::setDirection(bool active) {
    digitalWrite(PIN_DIR, active ? HIGH : LOW);
}

void Context::selectDisplay1() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, LOW);
    delay(CS_DELAY);
}

void Context::selectDisplay2() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, HIGH);
    delay(CS_DELAY);
}

void Context::initMode(Mode* mode) {
    delete _mode;
    _mode = mode;
    _mode->init(*this);
    selectDisplay1();
    _mode->initDisplay1(_display1);
    _mode->updateDisplay1(_display1);
    _display1.update();
    selectDisplay2();
    _mode->initDisplay2(_display2);
    _mode->updateDisplay2(_display2);
    _display2.update();
}

