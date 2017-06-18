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

#include "onair.h"
#include "program.h"

OnAir::OnAir(Program& context) :
    _displayOnAir(false)
{
    updateDisplay1(context);  
}

void OnAir::loop(Program& context) {
    // update display to reflect tally 1
    if (context.tally1() != _displayOnAir) {
        _displayOnAir = context.tally1();
        updateDisplay1(context);
    }

    // if button 1 has been pressed, dispatch on-air/off-air request
    if (context.button1Pressed()) {
        context.sendOnAirPulse();
    }
}

void OnAir::updateDisplay1(Program& context) {
    context.selectDisplay1();
    context.display().fill(MODE_CLEAR);
    if (_displayOnAir) {
        context.display().fillRect(0, 0, 63, 5, MODE_SET);
        context.display().fillRect(0, 26, 63, 5, MODE_SET);
        context.display().write(4, 23, "ON AIR");
        context.display().setBacklightColor(255, 0, 0);
    }
    else {
        context.display().setBacklightColor(50, 0, 0);
        context.display().write(1, 23, "OFFAIR");
    }

    context.display().update();
}

