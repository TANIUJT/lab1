#include "pitches.h"
#include "button.h"
#include "buzzer.h"

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

int notes[] = {NOTE_A3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_F3, NOTE_SILENCE, NOTE_DS3, NOTE_SILENCE};
double durations[] = {4, 1, 4, 1, 4, 1, 4, 1};
int melodyLength = 20;
bool hasGameEnded=true;

void setup() {
    firstBuzzer.setMelody(notes, durations, melodyLength);
    secondBuzzer.setMelody(notes, durations, melodyLength);
    pinMode(R_OUT,OUTPUT);
    pinMode(G_OUT,OUTPUT);
    pinMode(B_OUT,OUTPUT);
}

void loop() {
 if(hasGameEnded){
  gameEnd();
  gameStart();
  }
    else {
     if (firstPlayerButton.wasPressed()){
        firstBuzzer.playSound();
        hasGameEnded=true;
        set_rgb(0, 255, 0);
        delay(2500);
      }
     if (secondPlayerButton.wasPressed()){
       secondBuzzer.playSound();
       hasGameEnded=true;
       set_rgb(0, 255, 0);
       delay(2500);
      } 
    }
}
  void gameStart(){
   hasGameEnded=false;
   set_rgb (0, 0, 0);
   firstBuzzer.turnSoundOn();
   secondBuzzer.turnSoundOn();
   int waitingTime = random(300, 2500);
   delay(waitingTime);
   set_rgb(255, 0, 0);
  }
  void gameEnd(){
    firstBuzzer.turnSoundOff();
    secondBuzzer.turnSoundOff();
    set_rgb(0, 0, 255);
    delay (1000);
  }
void set_rgb (int r, int g, int b){
  analogWrite(R_OUT, 255-r);
  analogWrite(G_OUT, 255-g);
  analogWrite(B_OUT, 255-b);
  }
