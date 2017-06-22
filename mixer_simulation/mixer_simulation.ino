#define PIN_TALLY_1 3
#define PIN_TALLY_2 4
#define PIN_LANG_1  5
#define PIN_LANG_2  6

bool lastLang1 = false;
bool onAir = false;

void setup() {
    pinMode(PIN_TALLY_1, OUTPUT);
    pinMode(PIN_TALLY_2, OUTPUT);
    pinMode(PIN_LANG_1, INPUT_PULLUP);
    pinMode(PIN_LANG_2, INPUT_PULLUP);
}

void loop() {
    bool lang1 = digitalRead(PIN_LANG_1) == HIGH;
    // switch on-air/off-air
    if (!lastLang1 && lang1) {
        onAir = !onAir;
    }

    lastLang1 = lang1;

    if (onAir) {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(PIN_TALLY_1, HIGH);
    }
    else {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(PIN_TALLY_1, LOW);
    }
}

