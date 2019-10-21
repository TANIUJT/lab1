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
Buzzer winnerBuzzer(PIN_BUZZER1);
enum GameState {
    GAME_IN_PROGRESS = 101,
    GAME_ENDED = 102,
    PLAYING_MELODY = 103
};

int notes1[] = {NOTE_A3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_F3, NOTE_SILENCE, NOTE_DS3, NOTE_SILENCE};
int notes2[] = {NOTE_A5, NOTE_SILENCE, NOTE_G5, NOTE_SILENCE, NOTE_F5, NOTE_SILENCE, NOTE_DS5, NOTE_SILENCE};
double durations[] = {4, 1, 4, 1, 4, 1, 4, 1};
int melodyLength = 8;
GameState gameState= GAME_IN_PROGRESS;
uint64_t melodyDurationInMillis=2500;
uint64_t melodyBeginningTime=0;

void setup() {
    pinMode(R_OUT,OUTPUT);
    pinMode(G_OUT,OUTPUT);
    pinMode(B_OUT,OUTPUT);
    pinMode(PIN_BUZZER1,OUTPUT);
    pinMode(PIN_BUZZER2,OUTPUT);
}

void loop() {
  switch (gameState){
    case GAME_IN_PROGRESS:
      if (firstPlayerButton.wasPressed()){
        winnerBuzzer.setMelody(notes1,durations,melodyLength);
        buzzerPlay(PIN_BUZZER1);
        }
      if (secondPlayerButton.wasPressed()){
        winnerBuzzer.setMelody(notes2,durations,melodyLength);
        buzzerPlay(PIN_BUZZER2);
        } 
        break;
      case PLAYING_MELODY: 
        if(millis()-melodyBeginningTime<melodyDurationInMillis){
          winnerBuzzer.playSound();
          }
        else{
          gameState=GAME_ENDED;
        }
        break;
       case GAME_ENDED:
        gameEnd();
        gameStart();
        gameState=GAME_IN_PROGRESS;
        break;
   }
 }
  void buzzerPlay(int playerBuzzerNumber){
         winnerBuzzer.setBuzzer(playerBuzzerNumber);      
         winnerBuzzer.turnSoundOn();
         gameState=PLAYING_MELODY;
         set_rgb(0, 255, 0);
         melodyBeginningTime=millis();
  }
  void gameStart(){
   set_rgb (0, 0, 0);
   int waitingTime = random(300, 2500);
   delay(waitingTime);
   set_rgb(255, 0, 0);
  }
  void gameEnd(){  
    winnerBuzzer.turnSoundOff();
    set_rgb(0, 0, 255);
    delay (1000);
  }
  void set_rgb (int r, int g, int b){
    analogWrite(R_OUT, 255-r);
    analogWrite(G_OUT, 255-g);
    analogWrite(B_OUT, 255-b);
  }
