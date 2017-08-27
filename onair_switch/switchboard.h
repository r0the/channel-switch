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

#ifndef CONTEXT_H
#define CONTEXT_H

#include <Arduino.h>
#include <sb6432.h>
#include "behaviour.h"
#include "buttons.h"
#include "comm.h"

class Switchboard;

class Mode {
public:
    virtual void initDisplay1(SB6432& display) = 0;
    virtual void initDisplay2(SB6432& display) = 0;
    virtual void loop(Switchboard& context) = 0;
    virtual void updateDisplay1(SB6432& display) = 0;
    virtual void updateDisplay2(SB6432& display) = 0;
};

class Switchboard : public Behaviour {
public:
    Switchboard();
    virtual void setup();
    virtual void loop();
    inline bool button1Down() const { return _buttons.button1Down(); }
    inline bool button2() const { return _buttons.button2(); }
    inline bool button2Down() const { return _buttons.button2Down(); }
    inline bool channel1() const { return _comm->channel1(); }
    inline bool channel2() const { return _comm->channel2(); }
    inline bool commError() const { return _comm->error(); }
    inline bool display1Dirty() { _display1Dirty = true; }
    inline bool display2Dirty() { _display2Dirty = true; }
    void setupComm();
    void setupMode(Mode* mode = NULL);
    inline void setDirection(bool active) { _comm->setDirection(active); }
    inline void toggleChannel1() { _comm->toggleChannel1(); }
    inline void toggleChannel2() { _comm->toggleChannel2(); }
    inline void toggleMute() { _comm->toggleMute(); };
private:
    Buttons _buttons;
    Comm* _comm;
    SB6432 _display1;
    bool _display1Dirty;
    SB6432 _display2;
    bool _display2Dirty;
    Mode* _mode;
    void selectDisplay1();
    void selectDisplay2();
};

#endif

