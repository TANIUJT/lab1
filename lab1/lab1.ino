#include "pitches.h"
#include "button.h"
#include "buzzer.h"

#define PIN_BUZZER 6
#define PIN_BUTTON_OFF 5

Button buttonOff(PIN_BUTTON_OFF);
Buzzer buzzer(PIN_BUZZER);


int notes[] = {NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_DS3, NOTE_SILENCE};
double durations[] = {8, 8, 1, 8, 1, 8, 1, 24};
int melodyLength = 8;

void setup() {
    buzzer.setMelody(notes, durations, melodyLength);
    buzzer.turnSoundOff();
}

void loop() {
  
    buzzer.playSound();
    if (buttonOff.wasPressed())
    {
        buzzer.turnSoundOn();
    }
}
