# On-Air/Off-Air Switch

## Betriebsmodus On-Air/Off-Air

In diesem Modus kann mit der linken Taste das Mikrofon auf Sendung geschaltet werden.
Mit der rechten Taste kann eine Sprechverbindung zur Regie aufgebaut werden.

### Ein- und Ausgänge

Es werden die zwei Ausgänge *On-Air* und *Regie* verwendet. Über den Ausgang *On-Air* wird
mit einem 100 ms langen Signal der Kanal auf Sendung geschaltet bzw. ausgeschaltet. Der Kanal
zur Regie wird geöffnet, so lange der Ausgang *Regie* auf *HIGH* gesetzt wird.

Der Eingang *Tally 1* signalisiert mit einem *HIGH*, dass der Kanal auf Sendung ist.

### Anzeige

| Kurz    | Beschreibung                                                    |
|---------|-----------------------------------------------------------------|
| ON AIR  | "ON AIR", Balken ober- und unterhalb, intensiv rote Beleuchtung |
| off air | "OFF AIR", keine Balken, schwache rote Beleuchtung              |
| REGIE   | "REGIE, Balken ober- und unterhalb, intensiv blaue Beleuchtung  |
| regie   | "REGIE, keine Balken, schwache blaue Beleuchtung                |

### Logik

Das Display der linken Taste spiegelt immer den Zustand des Eingangs *Tally 1* wieder: liegt
*HIGH* an, so wird *ON AIR* angezeigt, ansonsten *off air*. Das Display der rechten Taste gibt
immer den Zustand des Ausgangs *Regie* wieder. Liegt *HIGH* auf dem Ausgang an, so wird *REGIE*
angezeigt, ansonsten *regie*.

So lange die rechte Taste gedrückt gehalten wird (*Taste 2* auf *HIGH*) und der Eingang
*Tally 1* auf *LOW* ist, wird der Ausgang *Regie* auf *HIGH* gesetzt.

Wenn die rechte Taste gedrückt wird (*Taste 2* von *LOW* auf *HIGH*) und der Eingang *Tally 1*
auf *HIGH* ist, wird versucht, den Kanal Off-Air zu schalten, es wird also auf dem Ausgang
*On-Air* ein 100 ms-Puls gesendet. Ausserdem wird das *Flag* gesetzt.

Wenn die rechte Taste losgelassen wird und das *Regie-On-Air*-Flag gesetzt ist, wird der Kanal
wieder auf Sendung geschaltet, indem ein 100 ms-Puls auf dem Ausgang *On-Air* gesendet wird.

| Taste 1 | Taste 2 | Tally 1 | Flag  | On-Air | Regie | Beschreibung              |
|---------|---------|---------|-------|--------|-------|---------------------------|
| *       | L       | L       | *     | L      | L     | Off-Air                   |
| *       | L       | H       | *     | L      | L     | On-Air                    |
| *       | H       | L       | *     | L      | H     | Regie                     |
| Rising  | L       | L       | *     | Puls   | L     | On-Air-Anfrage            |
| Rising  | L       | H       | *     | Puls   | L     | Off-Air-Anfrage           |
| *       | Rising  | L       | Set L | L      | L     | Regie ein                 |
| *       | Rising  | H       | Set H | Puls   | L     | Off-Air-Anfrage für Regie |
| *       | Falling | L       | L     | L      | L     | Regie aus                 |
| *       | Falling | L       | H     | Puls   | L     | On-Air-Anfrage nach Regie |
| *       | Falling | H       | *     | L      | L     | Regie fehlgeschlagen      |

## Betriebsmodus Konfiguration

# Betriebsmodus Übersetzung

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

| Pin | I/O | Funktion            |
|-----|-----|---------------------|
|  2  | OUT | Sprache 1 / On-Air  |
|  3  | OUT | Sprache 2           |
|  5  | OUT | Mute                |
|  6  | OUT | Regie               |
| 14  | OUT | Display Data        |
| 15  | OUT | Display Chip Select |
| 16  | OUT | Display Clock       |
| 18  | IN  | Tally 1             |
| 19  | IN  | Tally 2             |
| 20  | IN  | Programming Mode    |
| 22  | IN  | Button 2            |
| 23  | IN  | Button 1            |
