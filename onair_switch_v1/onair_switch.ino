#include <monogfx.h>
#include <sb6432.h>

#define CS_DELAY 1
#define PULSE_OUT_MS 100

#define PIN_DATA 10
#define PIN_CLOCK 11
#define PIN_CS 12
#define PIN_DIP_SWITCH_1 7
#define PIN_DIP_SWITCH_2 6
#define PIN_SWITCH_1 9
#define PIN_SWITCH_2 8
#define PIN_OUT_1 4
#define PIN_OUT_2 5

SB6432 lcd1(PIN_CLOCK, PIN_DATA);
SB6432 lcd2(PIN_CLOCK, PIN_DATA);
uint8_t switch1 = HIGH;
uint8_t switch2 = HIGH;
uint8_t lastSwitch1 = HIGH;
uint8_t lastSwitch2 = HIGH;
bool regieMode;
unsigned long pulse1End = 0;
unsigned long pulse2End = 0;

void selectLcd1() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, LOW);
    delay(CS_DELAY);
}

void selectLcd2() {
    delay(CS_DELAY);
    digitalWrite(PIN_CS, HIGH);
    delay(CS_DELAY);
}

// ----------------------------------------------------------
// REGIE-Modus
// ----------------------------------------------------------
bool onAir = false;
bool regie = false;

void regieUpdateDisplays() {
    selectLcd1();
    lcd1.fill(MODE_CLEAR);
    if (onAir && !regie) {
        lcd1.fillRect(0, 0, 63, 5, MODE_SET);
        lcd1.fillRect(0, 26, 63, 5, MODE_SET);
        lcd1.write(4, 23, "ON AIR");
        lcd1.setBacklightColor(255, 0, 0);
    }
    else {
        lcd1.setBacklightColor(50, 0, 0);
        lcd1.write(1, 23, "OFFAIR");
    }

    lcd1.update();

    selectLcd2();
    lcd2.fill(MODE_CLEAR);
    lcd2.write(6, 23, "REGIE");
    if (regie) {
        lcd2.setBacklightColor(0, 0, 255);
        lcd2.fillRect(0, 0, 63, 5, MODE_SET);
        lcd2.fillRect(0, 26, 63, 5, MODE_SET);
    }
    else {
        lcd2.setBacklightColor(0, 0, 50);
    }

    lcd2.update();
}

void regieLoop(unsigned long now) {
    if (lastSwitch1 == HIGH && switch1 == LOW) {
        // switch 1 has been pressed
        onAir = !onAir;
        digitalWrite(PIN_OUT_1, HIGH);
        pulse1End = now + 100;
    }

    regie = switch2 == LOW;
    regieUpdateDisplays();
    if (regie) {
        digitalWrite(PIN_OUT_2, HIGH);
    }
    else {
        digitalWrite(PIN_OUT_2, LOW);
    }
}

// ----------------------------------------------------------
// DOLMETSCH-Modus
// ----------------------------------------------------------

bool language1 = true;

void dolmetschUpdateDisplays() {
    selectLcd1();
    lcd1.fill(MODE_CLEAR);
    lcd1.write(15, 23, "DEU");
    if (language1) {
        lcd1.fillRect(0, 0, 63, 5, MODE_SET);
        lcd1.fillRect(0, 26, 63, 5, MODE_SET);
        lcd1.setBacklightColor(255, 0, 0);
    }
    else {
        lcd1.setBacklightColor(50, 0, 0);
    }

    lcd1.update();

    selectLcd2();
    lcd2.fill(MODE_CLEAR);
    lcd2.write(15, 23, "FRA");
    if (!language1) {
        lcd2.setBacklightColor(0, 0, 255);
        lcd2.fillRect(0, 0, 63, 5, MODE_SET);
        lcd2.fillRect(0, 26, 63, 5, MODE_SET);
    }
    else {
        lcd2.setBacklightColor(0, 0, 50);
    }

    lcd2.update();    
}

void dolmetschLoop(unsigned long now) {
    if (switch1 == LOW) {
        language1 = true;
        pulse1End = now + 100;
        digitalWrite(PIN_OUT_1, HIGH);
    }
    else if (switch2 == LOW) {
        language1 = false;
        pulse2End = now + 100;
        digitalWrite(PIN_OUT_2, HIGH);
    }

    dolmetschUpdateDisplays();
}

// ----------------------------------------------------------
// Gemeinsamer Code
// ----------------------------------------------------------

void setup() {
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_SWITCH_1, INPUT);
    pinMode(PIN_SWITCH_2, INPUT);
    pinMode(PIN_OUT_1, OUTPUT);
    pinMode(PIN_OUT_2, OUTPUT);
    digitalWrite(PIN_OUT_1, LOW);
    digitalWrite(PIN_OUT_2, LOW);
    selectLcd1();
    lcd1.begin();
    lcd1.setFontScale(2);

    selectLcd2();
    lcd2.begin();
    lcd2.setFontScale(2);
    regieMode = digitalRead(PIN_DIP_SWITCH_1) == HIGH;
}

void loop() {
    unsigned long now = millis();
    switch1 = digitalRead(PIN_SWITCH_1);
    switch2 = digitalRead(PIN_SWITCH_2);
    if (regieMode) {
        regieLoop(now);
    }
    else {
        dolmetschLoop(now);
    }

    if (pulse1End <= now) {
        digitalWrite(PIN_OUT_1, LOW);
    }

    if (pulse2End <= now) {
        digitalWrite(PIN_OUT_2, LOW);
    }

    lastSwitch1 = switch1;
    lastSwitch2 = switch2;
}

