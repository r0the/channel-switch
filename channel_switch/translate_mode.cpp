/*
 * Copyright (C) 2017 - 2018 by Stefan Rothe
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

#define STATE_MUTE          0
#define STATE_LANGUAGE_1    1
#define STATE_LANGUAGE_2    2
#define STATE_CHANNEL_ERROR 3
#define STATE_COMM_ERROR    4

static uint8_t determineState(Switchboard& switchboard) {
    if (switchboard.commError()) {
        return STATE_COMM_ERROR;
    }

    if (switchboard.channel1()) {
        if (switchboard.channel2()) {
            return STATE_CHANNEL_ERROR;
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

void TranslateMode::setupDisplay(SSD1331& display) {
    display.setTextAlign(ALIGN_CENTER);
}

void TranslateMode::loop(Switchboard& switchboard) {
    bool lastLanguage1 = _language1;
    uint8_t lastState = _state;
    _state = determineState(switchboard);
    switch (_state) {
        case STATE_CHANNEL_ERROR:
            switchboard.toggleChannel2();
            break;
        case STATE_LANGUAGE_1:
            _language1 = true;
            break;
        case STATE_LANGUAGE_2:
            _language1 = false;
            break;
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

void TranslateMode::updateDisplay1(SSD1331& display) {
    display.setFont(&SWISS_20_B);
    display.setForegroundColor(255, 255, 255);
    if (_state == STATE_CHANNEL_ERROR) {
        display.setBackgroundColor(0xE0, 0, 0);
        display.clear();
        display.drawText(TEXT_X, TEXT_Y, "Both");
        return;
    }

    if (_state == STATE_COMM_ERROR) {
        display.setBackgroundColor(0xE0, 0, 0);
        display.clear();
        display.drawText(TEXT_X, TEXT_Y, "Comm");
        return;
    }

    if (_language1) {
        if (_state == STATE_MUTE) {
            display.setFont(&SWISS_20);
            display.setBackgroundColor(0, 0, 0x60);                
            display.clear();
        }
        else {
            display.setBackgroundColor(0, 0, 0xC0);
            display.clear();
        }

        display.drawText(TEXT_X, TEXT_Y, CONFIG[CONFIG_LANGUAGE_1].name());
    }
    else {
        if (_state == STATE_MUTE) {
            display.setFont(&SWISS_20);
            display.setBackgroundColor(0, 0, 0x60);                
            display.clear();
        }
        else {
            display.setBackgroundColor(0, 0, 0xC0);
            display.clear();
        }

        display.drawText(TEXT_X, TEXT_Y, CONFIG[CONFIG_LANGUAGE_2].name());
    }

    if (_state != STATE_MUTE) {
        display.fillRectangle(0, 0, 95, 10);
        display.fillRectangle(0, 53, 95, 10);
    }
}

void TranslateMode::updateDisplay2(SSD1331& display) {
    display.setFont(&SWISS_20_B);
    if (_state == STATE_CHANNEL_ERROR) {
        display.setBackgroundColor(255, 0, 0);
        display.clear();
        display.drawText(TEXT_X, TEXT_Y, "Open");
        return;
    }

    if (_state == STATE_COMM_ERROR) {
        display.setBackgroundColor(255, 0, 0);
        display.clear();
        display.drawText(TEXT_X, TEXT_Y, "Error");
        return;
    }

    if (_state == STATE_MUTE) {
        display.setBackgroundColor(0xC0, 0, 0);
        display.clear();
        display.fillRectangle(0, 0, 96, 10);
        display.fillRectangle(0, 53, 96, 10);
    }
    else {
        display.setBackgroundColor(0x20, 0x00, 0x00);
        display.setFont(&SWISS_20);
        display.clear();
    }

    display.drawText(TEXT_X, TEXT_Y, "MUTE");
}

