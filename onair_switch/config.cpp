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

Config CONFIG;

const char* MODE_NAME[MODE_COUNT] = {"On-Air", "Translate"};
const char* LANGUAGE_NAME[LANGUAGE_COUNT] = {"DEU", "FRA", "ITA", "ENG"};
const char* TALLY_NAME[TALLY_COUNT] = {"LOW", "HIGH"};

Config::Config() :
    _language1(0),
    _language2(1),
    _mode(MODE_ON_AIR),
    _tally(TALLY_ACTIVE_HIGH)
{
}

void Config::load() {
    _language1 = EEPROM.read(LANGUAGE1_ADDRESS) % LANGUAGE_COUNT;
    _language2 = EEPROM.read(LANGUAGE2_ADDRESS) % LANGUAGE_COUNT;
    _mode = EEPROM.read(MODE_ADDRESS) % MODE_COUNT;
    _tally = EEPROM.read(TALLY_ADDRESS) % TALLY_COUNT;
}

void Config::save() {
    EEPROM.update(LANGUAGE1_ADDRESS, _language1);
    EEPROM.update(LANGUAGE2_ADDRESS, _language2);
    EEPROM.update(MODE_ADDRESS, _mode);
    EEPROM.update(TALLY_ADDRESS, _tally);
}

void Config::nextLanguage1() {
    _language1 = (_language1 + 1) % LANGUAGE_COUNT;
}

void Config::nextLanguage2() {
    _language2 = (_language2 + 1) % LANGUAGE_COUNT;
}

void Config::nextMode() {
    _mode = (_mode + 1) % MODE_COUNT;
}

void Config::nextTally() {
    _tally = (_tally + 1) % TALLY_COUNT;
}
