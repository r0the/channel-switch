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

#include "config_mode.h"
#include "config.h"

#define MENU_ITEM_COUNT 5

#define MENU_MODE 0
#define MENU_LANGUAGE_1 1
#define MENU_LANGUAGE_2 2
#define MENU_TALLY 3
#define MENU_EXIT 4

ConfigMode::ConfigMode() :
    _menuPos(0)
{
}

void ConfigMode::initDisplay1(SB6432& display) {
    display.setFontScale(1);
    display.setBacklightColor(255, 255, 255);
}

void ConfigMode::initDisplay2(SB6432& display) {
    display.setFontScale(1);
    display.setBacklightColor(255, 255, 255);
}

void ConfigMode::loop(Context& context) {
    if (context.button1Down()) {
        _menuPos = (_menuPos + 1) % MENU_ITEM_COUNT;
        context.display1Dirty();
        context.display2Dirty();
    }

    if (context.button2Down()) {
        context.display2Dirty();
        if (_menuPos == MENU_EXIT) {
            CONFIG.save();
            context.initMode();
        }
        else {
            CONFIG.item(_menuPos).nextValue();
        }
    }
}

void ConfigMode::updateDisplay1(SB6432& display) {
    display.fill(MODE_CLEAR);
    display.write(0, 8, "Config Menu");
    if (_menuPos == MENU_EXIT) {
        display.write(0, 31, "Exit");
    }
    else {
        display.write(0, 31, CONFIG.item(_menuPos).title());
    }
}

void ConfigMode::updateDisplay2(SB6432& display) {
    display.fill(MODE_CLEAR);
    display.write(0, 8, FIRMWARE_VERSION);
    if (_menuPos == MENU_EXIT) {
        display.write(0, 31, "Confirm");
    }
    else {
        display.write(0, 31, CONFIG.item(_menuPos).name());
    }
}

