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
#define PIN_BOARD_1 A3
#define PIN_BOARD_2 A2

#define CS_DELAY 1
#define PULSE_LENGTH_MS 100
#define LONG_PRESS_MS 5000

static const char* FIRMWARE_VERSION = "Version 0.4";

// ----------------------------------------------------------------------------
// Serial commands
// ----------------------------------------------------------------------------

#define CMD_TOGGLE_CHANNEL_1 '1'
#define CMD_TOGGLE_CHANNEL_2 '2'
#define CMD_TOGGLE_MUTE 'M'
#define CMD_DIRECTION_ENABLE 'D'
#define CMD_DIRECTION_DISABLE 'd'

// ----------------------------------------------------------------------------
// configuration item indices
// ----------------------------------------------------------------------------

#define CONFIG_MODE       0
#define CONFIG_LANGUAGE_1 1
#define CONFIG_LANGUAGE_2 2
#define CONFIG_TALLY      3
#define CONFIG_COMM       4
#define CONFIG_COUNT      5

// ----------------------------------------------------------------------------
// configuration of modes
// ----------------------------------------------------------------------------

#define MODE_ON_AIR    0
#define MODE_TRANSLATE 1
#define MODE_COUNT     2

// ----------------------------------------------------------------------------
// configuration of tally modes
// ----------------------------------------------------------------------------

#define TALLY_ACTIVE_LOW  0
#define TALLY_ACTIVE_HIGH 1
#define TALLY_COUNT       2

// ----------------------------------------------------------------------------
// configuration of communication mode
// ----------------------------------------------------------------------------

#define COMM_BAUD_RATE    4800
#define COMM_TIMEOUT      1000
#define COMM_KEEPALIVE_MS  100

#define COMM_DIRECT 0
#define COMM_SERIAL 1
#define COMM_COUNT  2

// ----------------------------------------------------------------------------
// configuration item
// ----------------------------------------------------------------------------

class ConfigItem {
public:
    ConfigItem(uint8_t address, const char* title, uint8_t maxValue,
        const char** names);
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
    const char* _title;
    uint8_t _value;
};

// ----------------------------------------------------------------------------
// programmable persistent configuration
// ----------------------------------------------------------------------------

class Config {
public:
    Config();
    ConfigItem& operator[](uint8_t index) const;

    uint8_t tally() const;
    void load();
    void save();
private:
    ConfigItem** _items;

    uint8_t _mode;
    uint8_t _tally;
};

extern Config CONFIG;

#endif

