/*
 * Copyright (C) 2017 - 2018 by Stefan Rothe
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

#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>

class Storage {
public:
    Storage();
    void writeByte(uint16_t address, uint8_t data) const;
    uint8_t readByte(uint16_t address) const;
private:
    Storage(const Storage&);
    Storage operator=(const Storage&);
};


class ConfigItem {
public:
    ConfigItem(const Storage& storage, const uint8_t address, const char* title,
        uint8_t maxValue, const char** names);
    void load();
    inline const char* name() const { return _names[_value]; }
    void nextValue();
    void save();
    inline const char* title() const { return _title; }
    inline uint8_t value() const { return _value; }
private:
    uint8_t _address;
    uint8_t _maxValue;
    const char** _names;
    const Storage& _storage;
    const char* _title;
    uint8_t _value;
};

#endif

