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

#include "config_mode.h"
#include "config.h"

ConfigMode::ConfigMode() :
    _menuPos(0)
{
}

void ConfigMode::setupDisplay(SSD1331& display) {
    display.setFontScale(1);
    display.setTextAlign(ALIGN_LEFT);
    display.setForegroundColor(255, 255, 255);
    display.setBackgroundColor(0, 0, 0);
}

void ConfigMode::loop(Switchboard& switchboard) {
    if (switchboard.button1Down()) {
        _menuPos = (_menuPos + 1) % (CONFIG_COUNT + 1);
        switchboard.display1Dirty();
        switchboard.display2Dirty();
    }

    if (switchboard.button2Down()) {
        switchboard.display2Dirty();
        if (_menuPos == CONFIG_COUNT) {
            CONFIG.save();
            switchboard.setupComm();
            switchboard.setupMode();
        }
        else {
            CONFIG[_menuPos].nextValue();
        }
    }
}

void ConfigMode::updateDisplay1(SSD1331& display) {
    display.clear();
    display.drawText(3, 11, "Config Menu");
    if (_menuPos == CONFIG_COUNT) {
        display.drawText(3, 58, "Exit");
    }
    else {
        display.drawText(3, 58, CONFIG[_menuPos].title());
    }
}

void ConfigMode::updateDisplay2(SSD1331& display) {
    display.clear();
    display.drawText(3, 11, FIRMWARE_VERSION);
    if (_menuPos == CONFIG_COUNT) {
        display.drawText(3, 58, "Confirm");
    }
    else {
        display.drawText(3, 58, CONFIG[_menuPos].name());
    }
}

