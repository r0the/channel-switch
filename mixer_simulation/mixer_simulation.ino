#define PIN_TY1 3
#define PIN_TY2 4
#define PIN_RQ1 5
#define PIN_RQ2 6

bool lastRequest1 = false;
bool lastRequest2 = false;
bool channel1 = false;
bool channel2 = false;

void setup() {
    pinMode(PIN_TY1, OUTPUT);
    pinMode(PIN_TY2, OUTPUT);
    pinMode(PIN_RQ1, INPUT_PULLUP);
    pinMode(PIN_RQ2, INPUT_PULLUP);
}

void loop() {
    bool request1 = digitalRead(PIN_RQ1) == HIGH;
    bool request2 = digitalRead(PIN_RQ2) == HIGH;

    if (!lastRequest1 && request1) {
        channel1 = !channel1;
    }

    if (!lastRequest2 && request2) {
        channel2 = !channel2;
    }

    lastRequest1 = request1;
    lastRequest2 = request2;

    digitalWrite(LED_BUILTIN, channel1 ? HIGH : LOW);
    digitalWrite(PIN_TY1, channel1 ? HIGH : LOW);
    digitalWrite(PIN_TY2, channel2 ? HIGH : LOW);
}

