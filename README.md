# Channel Switch

## Voraussetzungen

Die Channel Switch Arduino-Software ist für den Einsatz auf einem [Arduino MKR-1000](https://store.arduino.cc/arduino-mkr1000) vorgesehen. Um das Programm zu kompilieren, ist folgende Umgebung nötig:

* Arduino IDE 1.8 oder neuer
* Arduino SAMD Boards (32-bits ARM Cortex-M0+)
* [MonoGFX-Arduino library](https://github.com/r0the/monogfx-arduino)

## Gerätekonfiguration

Für die verschiedenen Geräte des Channel Switch wird die gleiche Arduino-Software verwendet. Der Betriebsmodus wird über die Eingänge A0 und A1 des Arduino festgelegt.

| A1  | A0  | Gerät                                      |
|:--- |:--- |:------------------------------------------ |
| 0   | 0   | Adapter LoRa-zu Audio-FSK-Kommunikation    |
| 0   | 1   | mobiles Switchboard mit LoRa-Kommunikation |
| 1   | 0   | Basisstation für Audio-FSK-Kommunikation   |
| 1   | 1   | Switchboard mit Audio-FSK-Kommunikation    |

Die Eingänge sind aktiv hoch. Sie sind mit einem Pullup-Widerstand geschaltet, standardmässig wird also immer die Option «Basisstation» gewählt.

## Pinbelegung

| MKR | Bezeichnung | Typ         | Gerät        | Funktion                                 | Aktiv          |
|:--- |:----------- |:----------- |:------------ |:---------------------------------------- |:-------------- |
| A0  | DEV1        | Digital in  | HW-Switch    | Identifikation des Gerätetyps            | HIGH           |
| A1  | DEV2        | Digital in  | HW-Switch    | Identifikation des Gerätetyps            | HIGH           |
| A2  | TY1         | Digital in  | Mischpult    | Kanal 1 offen (On Air / Sprache 1)       | konfigurierbar |
| A3  | TY2         | Digital in  | Mischpult    | Kanal 2 offen (Sprache 2)                | konfigurierbar |
| A4  | OLED_RESET  | Digital out | OLED         | Reset                                    | LOW            |
| A5  | OLED_CMD    | Digital out | OLED         | Command Mode                             | LOW            |
| A6  |             | -           | -            | -                                        | -              |
| 0   | BTN1        | Digital in  | Taste 1      | Taste 1 gedrückt                         | LOW            |
| 1   | BTN2        | Digital in  | Taste 2      | Taste 2 gedrückt                         | LOW            |
| 2   | RQ1         | Digital out | Mischpult    | Anforderung Kanal 1 (On Air / Sprache 1) | HIGH           |
| 3   | RQ2         | Digital out | Mischpult    | Anforderung Kanal 2 (On Air / Sprache 1) | HIGH           |
| 4   | DIR         | Digital out | Tellix Regie | Anfrage Kanal Regie                      | HIGH           |
| 5   | MUTE        | Digital out | ?            | Benachrichtigung Stummschaltung          | HIGH           |
| 6   | OLED_CS1    | Digital out | OLED         | Chip Select OLED links                   | LOW            |
| 7   | OLED_CS2    | Digital out | OLED         | Chip Select OLED rechts                  | LOW            |
| 8   | MOSI        | Digital out | SPI          | SPI Daten                                | -              |
| 9   | SCK         | Digital out | SPI          | SPI Takt                                 | -              |
| 10  | MISO        | Digital in  | SPI          | SPI Daten                                | -              |
| 11  | SDA         | -           | I2C          | I2C Daten                                | -              |
| 12  | SCL         | -           | I2C          | I2C Takt                                 | -              |


## Betriebsmodus On Air

In diesem Modus kann mit der linken Taste das Mikrofon auf Sendung geschaltet werden. Mit der rechten Taste kann eine Sprechverbindung zur Regie aufgebaut werden.

### Ein- und Ausgänge

Es werden die zwei Ausgänge *RQ1* und *DIR* verwendet. Über den Ausgang *RQ1* wird mit einem 100 ms langen Signal der Kanal auf Sendung geschaltet bzw. ausgeschaltet. Der Kanal zur Regie wird geöffnet, so lange der Ausgang *DIR* auf *HIGH* gesetzt wird.

Der Eingang *TY1* signalisiert mit *HIGH*, dass der Kanal auf Sendung ist.

### Anzeige

| Kurz    | Beschreibung                                                    |
|---------|-----------------------------------------------------------------|
| ON AIR  | "ON AIR", Balken ober- und unterhalb, intensiv rote Beleuchtung |
| off air | "OFF AIR", keine Balken, schwache rote Beleuchtung              |
| REGIE   | "REGIE, Balken ober- und unterhalb, intensiv blaue Beleuchtung  |
| regie   | "REGIE, keine Balken, schwache blaue Beleuchtung                |

### Logik

Das Display der linken Taste spiegelt immer den Zustand des Eingangs *TY1* wieder: liegt *HIGH* an, so wird *ON AIR* angezeigt, ansonsten *off air*. Das Display der rechten Taste gibt immer den Zustand des Ausgangs *DIR* wieder. Liegt *HIGH* auf dem Ausgang an, so wird *REGIE* angezeigt, ansonsten *regie*.

So lange die rechte Taste gedrückt gehalten wird (*BTN2* auf *HIGH*) und der Eingang *TY1* auf *LOW* ist, wird der Ausgang *Regie* auf *HIGH* gesetzt.

Wenn die rechte Taste gedrückt wird (*BTN2* von *LOW* auf *HIGH*) und der Eingang *TY1* auf *HIGH* ist, wird versucht, den Kanal Off-Air zu schalten, es wird also auf dem Ausgang *RQ1* ein 100 ms-Puls gesendet. Ausserdem wird das *FLAG* gesetzt.

Wenn die rechte Taste losgelassen wird und das *FLAG* gesetzt ist, wird der Kanal wieder auf Sendung geschaltet, indem ein 100 ms-Puls auf dem Ausgang *RQ1* gesendet wird.

| BTN1    | BTN2    | TY1     | FLAG  | RQ1    | DIR   | Beschreibung              |
|---------|---------|---------|-------|--------|-------|---------------------------|
| *       | L       | L       | *     | L      | L     | Off-Air                   |
| *       | L       | H       | *     | L      | L     | On-Air                    |
| *       | H       | L       | *     | L      | H     | Regie                     |
| Rising  | L       | *       | *     | Puls   | L     | On-Air/Off-Air-Anfrage    |
| *       | Rising  | L       | Set L | L      | L     | Regie ein                 |
| *       | Rising  | H       | Set H | Puls   | L     | Off-Air-Anfrage für Regie |
| *       | Falling | L       | L     | L      | L     | Regie aus                 |
| *       | Falling | L       | H     | Puls   | L     | On-Air-Anfrage nach Regie |
| *       | Falling | H       | *     | L      | L     | Regie fehlgeschlagen      |

## Betriebsmodus Konfiguration

Um in den Konfigurationsmodus zu gelangen, müssen beide Tasten gleichzeitig mindestens fünf Sekunden lang gedrückt werden.

## Betriebsmodus Übersetzung

Taste 1 schaltet zwischen zwei Sprachen um.
Taste 2 ist Räuspertaste (Mute wenn gedrückt).

Auf Display Taste 1 wird die gewählte Sprache angezeigt.
Die Farbe ändert mit der gewählten Sprache.
Wenn Muta aktiv ist, leuchet das Display weniger hell.

Auf Display Taste 2 wird MUTE angezeigt.
Wenn Mute aktiv ist, wird die Farbe intensiver und die Balken ober- und unterhalb angezeigt.

Konfiguration: Auswahl von zwei Sprachen aus: DEU, FRA, ITA, ENG

Ausgänge:
- (A) Sprache 1: Puls 100ms bei Wahl und Abwahl und Mute ein/aus
- (B) Sprache 2: Puls 100ms bei Wahl und Abwahl und Mute ein/aus
- (C) Mute: 100ms Puls bei ein und aus

Eingänge:
- (Tally 1): HIGH, wenn Kanal Sprache 1 offen
- (Tally 2): HIGH, wenn Kanal Sprache 2 offen
