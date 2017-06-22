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

#ifndef PROGRAM_H
#define PROGRAM_H

#include <Arduino.h>
#include <sb6432.h>
#include "onair.h"

class Program {
public:
    Program();
    inline bool button1Down() const { return _button1 && !_lastButton1; }
    inline bool button2() const { return _button2; }
    inline bool button2Down() const { return _button2 && !_lastButton2; }
    inline bool channel1() const { return _channel1; }
    inline bool channel2() const { return _channel2; }
    void loop();
    SB6432& selectDisplay1();
    SB6432& selectDisplay2();
    void toggleChannel1();
    void toggleChannel2();
    void sendMutePulse();
    void setDirection(bool active);
private:
    bool _button1;
    bool _button2;
    bool _channel1;
    bool _channel2;
    SB6432 _display1;
    SB6432 _display2;
    bool _lastButton1;
    bool _lastButton2;
    OnAir* _mode;
    unsigned long _mutePulseEnd;
    unsigned long _now;
    unsigned long _toggle1PulseEnd;
    unsigned long _toggle2PulseEnd;
};

#endif

