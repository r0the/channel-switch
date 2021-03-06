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

#include "switchboard.h"
#include "config.h"

#include "onair_mode.h"
#include "config_mode.h"
#include "translate_mode.h"

#include "direct_comm.h"

Switchboard::Switchboard() :
    _comm(NULL),
    _display1(PIN_OLED_CS1, PIN_OLED_RESET, PIN_OLED_CMD),
    _display1Dirty(false),
    _display2(PIN_OLED_CS2, PIN_OLED_RESET, PIN_OLED_CMD),
    _display2Dirty(false),
    _freezeEnd(0),
    _mode(NULL)
{
}

void Switchboard::setup() {
    _buttons.setup();

    // init display 1
    selectDisplay1();
    _display1.begin();
    // init display 2
    selectDisplay2();
    _display2.begin();
    CONFIG.load();
    setupComm();
    setupMode();
}

void Switchboard::loop() {
    _buttons.loop();
    _comm->loop();
    if (_buttons.longPress()) {
        setupMode(new ConfigMode);
    }

    if (_freezeEnd <= millis()) {
        // program logic
        _mode->loop(*this);
    }

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

void Switchboard::freeze() {
    _freezeEnd = millis() + COMMAND_FREEZE_MS;
}

void Switchboard::setupComm() {
    Comm* comm = new DirectComm;
    delete _comm;
    _comm = comm;
    _comm->setup();
}

void Switchboard::setupMode(Mode* mode) {
    if (mode == NULL) {
        switch (CONFIG[CONFIG_MODE].value()) {
            case MODE_ON_AIR:
                mode = new OnAirMode;
                break;
            case MODE_TRANSLATE:
                mode = new TranslateMode;
                break;
            default:
                mode = new OnAirMode;
                break;
        }
    }

    delete _mode;
    _mode = mode;
    selectDisplay1();
    _mode->setupDisplay(_display1);
    _mode->updateDisplay1(_display1);
    _display1.update();
    selectDisplay2();
    _mode->setupDisplay(_display2);
    _mode->updateDisplay2(_display2);
    _display2.update();
}

void Switchboard::toggleChannel1() {
    _comm->toggleChannel1();
    _freezeEnd = millis() + COMMAND_FREEZE_MS;
}

void Switchboard::toggleChannel2() {
    _comm->toggleChannel2();
    _freezeEnd = millis() + COMMAND_FREEZE_MS;
}

void Switchboard::selectDisplay1() {
}

void Switchboard::selectDisplay2() {
}

