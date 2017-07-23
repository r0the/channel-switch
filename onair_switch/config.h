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

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ----------------------------------------------------------------------------
// pin configuration
// ----------------------------------------------------------------------------

#define PIN_RQ1    2
#define PIN_RQ2    3
#define PIN_MUTE   5
#define PIN_DIR    6
#define PIN_DATA  14
#define PIN_CS    15
#define PIN_CLK   16
#define PIN_TY1   18
#define PIN_TY2   19
#define PIN_BTN2  22
#define PIN_BTN1  23

#define CS_DELAY 1
#define PULSE_LENGTH_MS 100
#define LONG_PRESS_MS 5000

static const char* FIRMWARE_VERSION = "Version 0.4";

// ----------------------------------------------------------------------------
// configuration of modes
// ----------------------------------------------------------------------------

#define MODE_ON_AIR 0
#define MODE_TRANSLATE 1
#define MODE_COUNT 2
extern const char* MODE_NAME[MODE_COUNT];

// ----------------------------------------------------------------------------
// configuration of languages for translation mode
// ----------------------------------------------------------------------------

#define LANGUAGE_COUNT 4
extern const char* LANGUAGE_NAME[LANGUAGE_COUNT];

// ----------------------------------------------------------------------------
// configuration of tally modes
// ----------------------------------------------------------------------------

#define TALLY_ACTIVE_LOW 0
#define TALLY_ACTIVE_HIGH 1
#define TALLY_COUNT 2
extern const char* TALLY_NAME[TALLY_COUNT];

// ----------------------------------------------------------------------------
// programmable persistent configuration
// ----------------------------------------------------------------------------

class Config {
public:
    Config();
    inline uint8_t language1() const { return _language1; }
    inline uint8_t language2() const { return _language2; }
    inline uint8_t mode() const { return _mode; }
    inline uint8_t tally() const { return _tally; }
    void load();
    void save();
    void nextLanguage1();
    void nextLanguage2();
    void nextMode();
    void nextTally();
private:
    uint8_t _language1;
    uint8_t _language2;
    uint8_t _mode;
    uint8_t _tally;
};

extern Config CONFIG;

#endif

