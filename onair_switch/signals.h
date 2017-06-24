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

#ifndef SIGNALS_H
#define SIGNALS_H

class Signals {
public:
    void setup();
    void loop();
    bool channel1() const { return _channel1; }
    bool channel2() const { return _channel2; }
    void setDirection(bool active);
    void toggleChannel1();
    void toggleChannel2();
    void toggleMute();
private:
    bool _channel1;
    bool _channel2;
    unsigned long _channel1End;
    unsigned long _muteEnd;
    unsigned long _channel2End;
};

#endif

