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

#ifndef BUTTONS_H
#define BUTTONS_H

class Buttons {
public:
    void setup();
    void loop();
    inline bool button1() const { return _button1; }
    inline bool button1Down() const { return _button1Down; }
    inline bool button2() const { return _button2; }
    inline bool button2Down() const { return _button2Down; }
    inline bool longPress() const { return _longPress; }
private:
    bool _button1;
    bool _button1Down;
    bool _button2;
    bool _button2Down;
    bool _lastButton1;
    bool _lastButton2;
    bool _longPress;
    unsigned long _longPressEnd;
};

#endif

