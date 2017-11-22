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

#include "config.h"
//#include <EEPROM.h>
#include <FlashAsEEPROM.h>

Config CONFIG;

#define LANGUAGE_COUNT 4

const char* MODE_NAMES[MODE_COUNT] = {"On-Air", "Translation"};
const char* LANGUAGE_NAMES[LANGUAGE_COUNT] = {"DEU", "FRA", "ITA", "ENG"};
const char* TALLY_NAMES[TALLY_COUNT] = {"LOW", "HIGH"};
const char* COMM_NAMES[COMM_COUNT] = {"Direct", "Serial"};

bool checkHeader() {
    char magic1 = Serial1.read();
    char magic2 = Serial1.read();
    return magic1 == COMM_MAGIC_1 && magic2 == COMM_MAGIC_2;
}
void writeHeader() {
    Serial1.write(COMM_MAGIC_1);
    Serial1.write(COMM_MAGIC_2);
}

ConfigItem::ConfigItem(uint8_t address, const char* title, uint8_t maxValue, const char** names) :
    _address(address),
    _maxValue(maxValue),
    _names(names),
    _title(title),
    _value(0)
{
}

void ConfigItem::load() {
    _value = EEPROM.read(_address) % _maxValue;
}

void ConfigItem::nextValue() {
    _value = (_value + 1) % _maxValue;
}

void ConfigItem::save() {
    EEPROM.update(_address, _value);
}

Config::Config() :
    _items(new ConfigItem*[CONFIG_COUNT])
{
    _items[CONFIG_MODE] = new ConfigItem(3, "Mode", MODE_COUNT, MODE_NAMES);
    _items[CONFIG_LANGUAGE_1] = new ConfigItem(1, "Language 1", LANGUAGE_COUNT, LANGUAGE_NAMES);
    _items[CONFIG_LANGUAGE_2] = new ConfigItem(2, "Language 2", LANGUAGE_COUNT, LANGUAGE_NAMES);
    _items[CONFIG_TALLY] = new ConfigItem(4, "Tally Active", TALLY_COUNT, TALLY_NAMES);
    _items[CONFIG_COMM] = new ConfigItem(5, "Comm", COMM_COUNT, COMM_NAMES);
}

ConfigItem& Config::operator[](uint8_t index) const {
    return *_items[index];
}

uint8_t Config::tally() const {
    return _items[CONFIG_TALLY]->value();
}

void Config::load() {
    for (uint8_t i = 0; i < CONFIG_COUNT; ++i) {
        _items[i]->load();
    }
}

void Config::save() {
    for (uint8_t i = 0; i < CONFIG_COUNT; ++i) {
        _items[i]->save();
    }
}

