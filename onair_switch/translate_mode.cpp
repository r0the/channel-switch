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

#include "translate_mode.h"
#include "config.h"

#define STATE_MUTE       0
#define STATE_LANGUAGE_1 1
#define STATE_LANGUAGE_2 2
#define STATE_ERROR      3
#define STATE_COMM_ERROR 4

static uint8_t detectState(Switchboard& switchboard) {
    if (switchboard.commError()) {
        return STATE_COMM_ERROR;
    }

    if (switchboard.channel1()) {
        if (switchboard.channel2()) {
            return STATE_ERROR;
        }
        else {
            return STATE_LANGUAGE_1;
        }
    }
    else {
        if (switchboard.channel2()) {
            return STATE_LANGUAGE_2;
        }
        else {
            return STATE_MUTE;
        }        
    }
}

void TranslateMode::initDisplay(SB6432& display) {
    display.setFontScale(2);
    display.setTextAlign(ALIGN_CENTER);
}

void TranslateMode::loop(Switchboard& switchboard) {
    bool lastLanguage1 = _language1;
    uint8_t lastState = _state;
    _state = detectState(switchboard);
    switch (_state) {
        case STATE_ERROR:
            switchboard.toggleChannel2();
            break;
        case STATE_LANGUAGE_1:
            _language1 = true;
            break;
        case STATE_LANGUAGE_2:
            _language1 = false;
            break;
    }

    if (_state == STATE_ERROR) {
        switchboard.toggleChannel2();
        return;
    }

    // if button 1 has gone down, change language
    if (switchboard.button1Down()) {
        if (_state == STATE_MUTE) {
            _language1 = !_language1;
        }
        else {
            switchboard.toggleChannel1();
            switchboard.toggleChannel2();            
        }
    }

    if (switchboard.button2Down()) {
        if (_language1) {
            switchboard.toggleChannel1();
        }
        else {
            switchboard.toggleChannel2();
        }
    }

    if (lastState != _state || lastLanguage1 != _language1) {
        switchboard.display1Dirty();
    }

    if (lastState != _state) {
        switchboard.display2Dirty();        
    }
}

void TranslateMode::updateDisplay1(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_state == STATE_ERROR) {
        display.write(31, 23, "Error");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    if (_state == STATE_COMM_ERROR) {
        display.write(31, 23, "Comm");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    if (_state != STATE_MUTE) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
    }

    if (_language1) {
        display.write(31, 23, CONFIG[CONFIG_LANGUAGE_1].name());
        if (_state == STATE_MUTE) {
            display.setBacklightColor(0, 50, 0);                
        }
        else {
            display.setBacklightColor(0, 255, 0);
        }
    }
    else {
        display.write(31, 23, CONFIG[CONFIG_LANGUAGE_2].name());
        if (_state == STATE_MUTE) {
            display.setBacklightColor(0, 0, 50);                
        }
        else {
            display.setBacklightColor(0, 0, 255);
        }
    }
}

void TranslateMode::updateDisplay2(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_state == STATE_ERROR) {
        display.write(31, 23, "Error");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    if (_state == STATE_COMM_ERROR) {
        display.write(31, 23, "Error");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    display.write(31, 23, "MUTE");
    if (_state == STATE_MUTE) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.setBacklightColor(255, 255, 255);
    }
    else {
        display.setBacklightColor(50, 50, 50);
    }
}

