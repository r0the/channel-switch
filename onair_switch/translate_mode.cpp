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

#define STATE_ERROR     0
#define STATE_LANGUAGE1 1
#define STATE_LANGUAGE2 2
#define STATE_MUTE      3

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
    uint8_t lastState = _state;
    if (context.channel1() && context.channel2()) {
        _state = STATE_ERROR;
    }
    else if (context.channel1()) {
        _state = STATE_LANGUAGE1;
    }
    else if (context.channel2()) {
        _state = STATE_LANGUAGE2;
    }
    else {
        _state = STATE_MUTE;
    }

    if (lastState != _state) {
        context.display1Dirty();
    }

    // if button 1 has gone down, change language
    if (context.button1Down()) {
        switch (_state) {
            case STATE_LANGUAGE1:
            case STATE_LANGUAGE2:
                context.toggleChannel1();
                break;            
        }
            
    }

}

void TranslateMode::updateDisplay1(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (true) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.write(4, 23, "XXX");
        display.setBacklightColor(0, 0, 0);
    }
    else {
        display.setBacklightColor(50, 0, 0);
        display.write(1, 23, "YYY");
    }
}

void TranslateMode::updateDisplay2(SB6432& display) {
    display.fill(MODE_CLEAR);
    if (true) {
        display.fillRect(0, 0, 63, 5, MODE_SET);
        display.fillRect(0, 26, 63, 5, MODE_SET);
        display.setBacklightColor(0, 0, 0);
    }
    else {
        display.setBacklightColor(0, 0, 50);
    }

    display.write(4, 23, "BLUP");
}

