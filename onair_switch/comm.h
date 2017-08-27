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
 
#ifndef COMM_H
#define COMM_H
 
class Comm {
public:
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual bool channel1() const = 0;
    virtual bool channel2() const = 0;
    virtual bool error() const = 0;
    virtual void setDirection(bool active) = 0;
    virtual void toggleChannel1() = 0;
    virtual void toggleChannel2() = 0;
    virtual void toggleMute() = 0;
};

#endif

