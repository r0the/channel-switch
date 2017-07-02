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

#define STATE_ERROR     0
#define STATE_ONAIR     1
#define STATE_MUTE      2

#define LANGUAGE_1      1
#define LANGUAGE_2      2


TranslateMode::TranslateMode()
{
}

void TranslateMode::initDisplay1(SB6432& display) {
    display.setFontScale(2);
}

void TranslateMode::initDisplay2(SB6432& display) {
    display.setFontScale(2);
}

void TranslateMode::loop(Context& context) {
    // display error if both channels are open
    bool lastOnAir = _displayOnAir;
    bool lastError = _displayError;
    uint8_t lastChannel = _channel;
    _displayOnAir = context.channel1() || context.channel2();
    _displayError = context.channel1() && context.channel2();
    if (_displayOnAir && !_displayError) {
        if (context.channel1()) {
            _channel = LANGUAGE_1;
        }
        else if (context.channel2()) {
            _channel = LANGUAGE_2;
        }
    }

    if (lastChannel != _channel || lastOnAir != _displayOnAir || lastError != _displayError) {
        context.display1Dirty();
    }

    if (lastOnAir != _displayOnAir) {
        context.display2Dirty();        
    }

    // if button 1 has gone down, change language
    if (context.button1Down() && !_displayError) {
        if (_displayOnAir) {
            context.toggleChannel1();
            context.toggleChannel2();            
        }
        else {
            switch (_channel) {
                case LANGUAGE_1:
                    context.toggleChannel1();
                    break;
                case LANGUAGE_2:
                    context.toggleChannel2();
                    break;
            }
        }
    }

    if (context.button2Down()) {
        if (context.channel1()) {
            context.toggleChannel1();
        }

        if (context.channel2()) {
            context.toggleChannel2();
        }        
    }

    if (!context.button2()) {
        if (!_displayOnAir) {
            switch (_channel) {
                case LANGUAGE_1:
                    context.toggleChannel1();
                    break;
                case LANGUAGE_2:
                    context.toggleChannel2();
                    break;
            }            
        }
    }
}

void TranslateMode::updateDisplay1(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_displayError) {
        display.write(4, 23, "Error");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    if (_displayOnAir) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
    }

    switch (_channel) {
        case LANGUAGE_1:
            display.write(4, 23, LANGUAGE_NAME[CONFIG.language1()]);
            if (_displayOnAir) {
                display.setBacklightColor(0, 255, 0);
            }
            else {
                display.setBacklightColor(0, 50, 0);                
            }

            break;
        case LANGUAGE_2:
            display.write(4, 23, LANGUAGE_NAME[CONFIG.language2()]);
            if (_displayOnAir) {
                display.setBacklightColor(0, 0, 255);
            }
            else {
                display.setBacklightColor(0, 0, 50);                
            }

            break;
    }
}

void TranslateMode::updateDisplay2(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (_displayError) {
        display.write(4, 23, "Error");
        display.setBacklightColor(255, 0, 0);
        return;
    }

    display.write(4, 23, "MUTE");
    if (_displayOnAir) {
        display.setBacklightColor(50, 50, 50);
    }
    else {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.setBacklightColor(255, 255, 255);
    }
}

