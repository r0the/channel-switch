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

#include "config.h"

Config CONFIG;

#define LANGUAGE_COUNT 5

const char* MODE_NAMES[MODE_COUNT] = {"On-Air", "Translation"};
const char* LANGUAGE_NAMES[LANGUAGE_COUNT] = {"DEU", "FRA", "ITA", "ROH", "ENG"};

bool checkHeader() {
    char magic1 = Serial1.read();
    char magic2 = Serial1.read();
    return magic1 == COMM_MAGIC_1 && magic2 == COMM_MAGIC_2;
}
void writeHeader() {
    Serial1.write(COMM_MAGIC_1);
    Serial1.write(COMM_MAGIC_2);
}

Config::Config() :
    _storage(),
    _items(new ConfigItem*[CONFIG_COUNT])
{
    _items[CONFIG_MODE] = new ConfigItem(_storage, 3, "Mode", MODE_COUNT, MODE_NAMES);
    _items[CONFIG_LANGUAGE_1] = new ConfigItem(_storage, 1, "Language 1", LANGUAGE_COUNT, LANGUAGE_NAMES);
    _items[CONFIG_LANGUAGE_2] = new ConfigItem(_storage, 2, "Language 2", LANGUAGE_COUNT, LANGUAGE_NAMES);
}

ConfigItem& Config::operator[](uint8_t index) const {
    return *_items[index];
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

