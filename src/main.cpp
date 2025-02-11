#include <Arduino.h>
#include "pab.h"

#define PIN_INPUT     T0    //GPIO used as input signal - must chose between touch pin of the board (EX: T0, T1, etc..)

Trigger trigger (PIN_INPUT);      //class meant to simplify recursive action, and clean main
int value = 0;                    //last value measured
bool KeptTouch = false;           //bool used to track hold touch

unsigned long StartMillis1;       //first timer -- sampling speed
const int Period1 = 100;
unsigned long StartMillis2;       //second timer -- how many millis before adapting trigger level
const int Period2 = 5000;

void setup(){
  Serial.begin(115200);
  trigger.initialize();
  Serial.printf("Initialized as follow:");   //debug
  trigger.debug();                           //debug
  Serial.printf("\n");                       //debug
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