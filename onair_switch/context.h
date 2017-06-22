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

#define MODE_ON_AIR 0
#define MODE_TRANSLATE 1
#define MODE_COUNT 2

class Context;

class Mode {
public:
    virtual void init(Context& context) { }
    virtual void initDisplay1(SB6432& display) = 0;
    virtual void initDisplay2(SB6432& display) = 0;
    virtual void loop(Context& context) = 0;
    virtual void updateDisplay1(SB6432& display) = 0;
    virtual void updateDisplay2(SB6432& display) = 0;
};

class Context {
public:
    Context();
    inline bool button1Down() const { return _button1 && !_lastButton1; }
    inline bool button2() const { return _button2; }
    inline bool button2Down() const { return _button2 && !_lastButton2; }
    inline bool channel1() const { return _channel1; }
    inline bool channel2() const { return _channel2; }
    inline bool display1Dirty() { _display1Dirty = true; }
    inline bool display2Dirty() { _display2Dirty = true; }
    void loop();
    void setMode(uint8_t modeId);
    uint8_t mode() const;
    void sendMutePulse();
    void setDirection(bool active);
    void toggleChannel1();
    void toggleChannel2();
private:
    bool _button1;
    bool _button2;
    bool _channel1;
    bool _channel2;
    SB6432 _display1;
    bool _display1Dirty;
    SB6432 _display2;
    bool _display2Dirty;
    bool _lastButton1;
    bool _lastButton2;
    Mode* _mode;
    uint8_t _modeId;
    unsigned long _mutePulseEnd;
    unsigned long _now;
    unsigned long _programmingModeStart;
    unsigned long _toggle1PulseEnd;
    unsigned long _toggle2PulseEnd;
    void selectDisplay1();
    void selectDisplay2();
    void initMode(Mode* mode);
};

#endif

