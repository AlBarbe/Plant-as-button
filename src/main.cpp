#include <Arduino.h>
#include "pab.h"

#define PIN_INPUT     T0    //GPIO used as input signal - must chose between touch pin of the board (EX: T0, T1, etc..)

Trigger trigger (PIN_INPUT);
int value = 0;
bool KeptTouch = false;

unsigned long StartMillis1;
const int Period1 = 100;
unsigned long StartMillis2;
const int Period2 = 5000;

void setup(){
  Serial.begin(115200);
  delay (2000);

  trigger.initialize();
  Serial.printf("Initialized as follow:");
  trigger.debug();
  Serial.printf("\n");
}

void loop(){

  if (millis() < StartMillis1 || millis() < StartMillis2){    //protection against Millis() value reset
    StartMillis1 = 0;
    StartMillis2 = 0;
  }

  if (millis()- StartMillis1 > Period1) {                     //Timer to update touch sensor every "Period1" millisec
    value = touchRead(T0);
    trigger.update(value);
    //Serial.println(value);            //debug
    //trigger.debug();                  //debug
    StartMillis1 = millis();
  }
  
  if (trigger.touch () == true && KeptTouch == true) {        //condition to do action if kept pressed for more than "Period1"
    if (millis()- StartMillis2 > Period2) {                   //timer to update trigger reset after being touch for more than "Period2" millisec
      trigger.reset();
      StartMillis2 = millis();
      Serial.printf("Trigger reset!");  //debug
    }
  }

  if (trigger.touch () == true && KeptTouch == false) {       //condiotion to do action on press (1 time after pressed)
    StartMillis2 = millis();
    KeptTouch = true;
    Serial.printf("Touched!!!");        //debug

    //===========  Put Here the list of action to do on press  ============//
  }

  if (trigger.touch () == false && KeptTouch == true) {       //condition to do actions on release
    Serial.printf("Released!!!");       //debug
    KeptTouch = false;
  }
}