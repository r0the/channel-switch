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

#include "switchboard.h"
#include "config.h"

#include "onair_mode.h"
#include "config_mode.h"
#include "translate_mode.h"

#include "direct_comm.h"
#include "serial_comm.h"

Switchboard::Switchboard() :
    _comm(NULL),
    _display1(PIN_CLK, PIN_DATA),
    _display1Dirty(false),
    _display2(PIN_CLK, PIN_DATA),
    _display2Dirty(false),
    _mode(NULL)
{
}

void Switchboard::setup() {
    _buttons.setup();
    pinMode(PIN_CS, OUTPUT);

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

    // program logic
    _mode->loop(*this);

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

void Switchboard::setupComm() {
    Comm* comm = NULL;
    switch (CONFIG[CONFIG_COMM].value()) {
        case COMM_DIRECT:
            comm = new DirectComm;
            break;
        case COMM_SERIAL:
            comm = new SerialComm;
            break;
    }

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
        }
    }

    delete _mode;
    _mode = mode;
    selectDisplay1();
    _mode->initDisplay(_display1);
    _mode->updateDisplay1(_display1);
    _display1.update();
    selectDisplay2();
    _mode->initDisplay(_display2);
    _mode->updateDisplay2(_display2);
    _display2.update();
}

void Switchboard::selectDisplay1() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, LOW);
    delay(CS_DELAY);
}

void Switchboard::selectDisplay2() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, HIGH);
    delay(CS_DELAY);
}

