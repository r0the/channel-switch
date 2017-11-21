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

#ifndef DIRECT_COMM_H
#define DIRECT_COMM_H

#include "comm.h"

class DirectComm : public Comm {
public:
    virtual void setup();
    virtual void loop();
    virtual bool channel1() const;
    virtual bool channel2() const;
    virtual bool error() const;
    virtual void setDirection(bool active);
    virtual void toggleChannel1();
    virtual void toggleChannel2();
    virtual void toggleMute();
private:
    bool _channel1;
    bool _channel2;
    unsigned long _channel1End;
    unsigned long _muteEnd;
    unsigned long _channel2End;
};

#endif

