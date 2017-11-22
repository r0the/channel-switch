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


#define TEXT_X 47
#define TEXT_Y 37

// ----------------------------------------------------------------------------
// pin configuration
// ----------------------------------------------------------------------------

#define PIN_DEV1        A0
#define PIN_DEV2        A1
#define PIN_TY1         A2
#define PIN_TY2         A3
#define PIN_OLED_RESET  A4
#define PIN_OLED_CMD    A5

#define PIN_BTN2        0
#define PIN_BTN1        1
#define PIN_RQ1         2
#define PIN_RQ2         3
#define PIN_DIR         4
#define PIN_MUTE        5
#define PIN_OLED_CS1    6
#define PIN_OLED_CS2    7

#define PULSE_LENGTH_MS 100

// ----------------------------------------------------------------------------
// switchboard behaviour
// ----------------------------------------------------------------------------

// The delay in milliseconds both buttons must be pressed until the
// configuration mode is activated
#define LONG_PRESS_MS 5000

// The delay in milliseconds the switchboard does not update it's state after
// it issued a command
#define COMMAND_FREEZE_MS 200

// ----------------------------------------------------------------------------
// serial communication configuration
// ----------------------------------------------------------------------------

#define COMM_MAGIC_1 'S'
#define COMM_MAGIC_2 'r'

// The baud rate of the serial communication
#define COMM_BAUD_RATE    4800

// The timeout in milliseconds from the last keepalive signal until the
// switchboard displays a communication error message
#define COMM_TIMEOUT_MS    1000

// The delay in milliseconds between two keepalive signals transmitted by
// the base
#define COMM_KEEPALIVE_MS  100

bool checkHeader();
void writeHeader();

// ----------------------------------------------------------------------------
// version information
// ----------------------------------------------------------------------------

static const char* FIRMWARE_VERSION = "Version 0.6";

// ----------------------------------------------------------------------------
// serial commands
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

