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
#include <EEPROM.h>

#define LANGUAGE1_ADDRESS 1
#define LANGUAGE2_ADDRESS 2
#define MODE_ADDRESS      3
#define TALLY_ADDRESS     4

// config item indices
#define CONFIG_MODE       0
#define CONFIG_LANGUAGE_1 1
#define CONFIG_LANGUAGE_2 2
#define CONFIG_TALLY      3
#define CONFIG_COUNT      4

Config CONFIG;

const char* MODE_NAME[MODE_COUNT] = {"On-Air", "Translate"};
const char* LANGUAGE_NAME[LANGUAGE_COUNT] = {"DEU", "FRA", "ITA", "ENG"};
const char* TALLY_NAME[TALLY_COUNT] = {"LOW", "HIGH"};

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
    _itemCount(CONFIG_COUNT),
    _items(new ConfigItem*[_itemCount])
{
    _items[CONFIG_MODE] = new ConfigItem(3, "Mode", MODE_COUNT, MODE_NAME);
    _items[CONFIG_LANGUAGE_1] = new ConfigItem(1, "Language 1", LANGUAGE_COUNT, LANGUAGE_NAME);
    _items[CONFIG_LANGUAGE_2] = new ConfigItem(2, "Language 2", LANGUAGE_COUNT, LANGUAGE_NAME);
    _items[CONFIG_TALLY] = new ConfigItem(4, "Tally Active", TALLY_COUNT, TALLY_NAME);
}

ConfigItem& Config::item(uint8_t index) const {
    return *_items[index];
}

uint8_t Config::language1() const {
    return _items[CONFIG_LANGUAGE_1]->value();
}

uint8_t Config::language2() const {
    return _items[CONFIG_LANGUAGE_2]->value();    
}

uint8_t Config::mode() const {
    return _items[CONFIG_MODE]->value();
}

uint8_t Config::tally() const {
    return _items[CONFIG_TALLY]->value();
}

void Config::load() {
    for (uint8_t i = 0; i < _itemCount; ++i) {
        _items[i]->load();
    }
}

void Config::save() {
    for (uint8_t i = 0; i < _itemCount; ++i) {
        _items[i]->save();
    }
}

