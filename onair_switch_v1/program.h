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
    inline bool button1Pressed() const { return _button1 && !_lastButton1; }
    inline SB6432& display() const { return *_display; }
    void loop();
    void selectDisplay1();
    void selectDisplay2();
    void sendLang1Pulse();
    void sendLang2Pulse();
    void sendMutePulse();
    inline void sendOnAirPulse() { sendLang1Pulse(); }
    inline bool tally1() const { return _tally1; }
    inline bool tally2() const { return _tally2; }
private:
    bool _button1;
    bool _button2;
    SB6432 _display1;
    SB6432 _display2;
    SB6432* _display;
    unsigned long _lang1PulseEnd;
    unsigned long _lang2PulseEnd;
    bool _lastButton1;
    bool _lastButton2;
    OnAir* _mode;
    unsigned long _mutePulseEnd;
    unsigned long _now;
    bool _tally1;
    bool _tally2;
};

#endif

