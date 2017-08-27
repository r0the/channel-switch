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

#ifndef ONAIR_MODE_H
#define ONAIR_MODE_H

#include "switchboard.h"

class OnAirMode : public Mode {
public:
    OnAirMode();
    virtual void initDisplay(SB6432& display);
    virtual void loop(Switchboard& switchboard);
    virtual void updateDisplay1(SB6432& display);
    virtual void updateDisplay2(SB6432& display);
private:
    bool _displayCommError;
    bool _displayOnAir;
    bool _displayDirection;
    bool _onAirBeforeDirection;
};

#endif

