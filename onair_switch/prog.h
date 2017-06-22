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

#ifndef PROG_H
#define PROG_H

#include "context.h"

class Prog : public Mode {
public:
    Prog();
    virtual void init(Context& context);
    virtual void initDisplay1(SB6432& display);
    virtual void initDisplay2(SB6432& display);
    virtual void loop(Context& context);
    virtual void updateDisplay1(SB6432& display);
    virtual void updateDisplay2(SB6432& display);
private:
    uint8_t _language1;
    uint8_t _language2;
    uint8_t _menuItem;
    uint8_t _modeId;
};

#endif

