# On-Air/Off-Air Switch

## Betriebsmodus On-Air/Off-Air

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


## Pinbelegung

| Pin | I/O | Abk. | Bezeichnung         | Beschreibung                      |
|-----|-----|------|---------------------|-----------------------------------|
|  2  | OUT | RQ1  | Request Channel 1   | Ausgang Anforderungs-Puls Kanal 1 |
|  3  | OUT | RQ2  | Request Channel 2   | Ausgang Anforderungs-Puls Kanal 2 |
|  5  | OUT | MUTE | Mute                | Ausgang Mute                      |
|  6  | OUT | DIR  | Direction           | Ausgang Regie                     |
| 14  | OUT | DATA | Display Data        | Ausgang Datenlinie für Anzeigen   |
| 15  | OUT | CS   | Display Chip Select | Ausgang Auswahl der Anzeige       |
| 16  | OUT | CLK  | Display Clock       | Ausgang Datentakt für Anzeigen    |
| 18  | IN  | TY1  | Tally Channel 1     | Eingang Bestätigung Kanal 1 offen |
| 19  | IN  | TY2  | Tally Channel 2     | Eingang Bestätigung Kanal 2 offen |
| 20  | IN  | PRG  | Programming Mode    | Eingang Programmiermodus          |
| 22  | IN  | BTN2 | Button 2            | Eingang rechte Taste              |
| 23  | IN  | BTN1 | Button 1            | Eingang linke Taste               |
