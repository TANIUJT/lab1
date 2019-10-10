#include "pitches.h"
#include "button.h"
#include "buzzer.h"
#include <Arduino.h>

#define PIN_BUZZER1 4
#define PIN_BUZZER2 5
#define PIN_BUTTON_PLAYER1 6
#define PIN_BUTTON_PLAYER2 7
#define R_OUT 10
#define G_OUT 11
#define B_OUT 12

Button firstPlayerButton(PIN_BUTTON_PLAYER1);
Button secondPlayerButton(PIN_BUTTON_PLAYER2);
Buzzer firstBuzzer(PIN_BUZZER1);
Buzzer secondBuzzer(PIN_BUZZER2);

int notes[] = {NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_DS3, NOTE_SILENCE};
double durations[] = {8, 8, 1, 8, 1, 8, 1, 24};
int melodyLength = 8;

void setup() {
    firstBuzzer.setMelody(notes, durations, melodyLength);
    secondBuzzer.setMelody(notes, durations, melodyLength);
    pinMode(R_OUT,OUTPUT);
    pinMode(G_OUT,OUTPUT);
    pinMode(B_OUT,OUTPUT);
}

void loop() {
 set_rgb (0, 0, 0);
 int waitingTime = random(300, 2500);
 delay(waitingTime);
 set_rgb(255, 0, 0);
 while (1){
   if (firstButton.wasPressed){
      firstBuzzer.playSound();
      set_rgb(0, 255, 0);
      break;
   // delay (2500);
   }
   if (secondButton.wasPressed){
     secondBuzzer.playSound();
     set_rgb(0, 255, 0);
     break; 
 //  delay (2500);
   } 
  }
  delay (2500);
  set_rgb(0, 0, 255);
  delay (500);
}
void set_rgb (int r, int g, int b){
  analogWrite(R_OUT, 255-r);
  analogWrite(G_OUT, 255-g);
  analogWrite(B_OUT, 255-b);
  }
