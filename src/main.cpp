#include <Arduino.h>
#include "pab.h"

//class declaration

#define PIN_INPUT     T0    //GPIO used as input signal - must chose between touch pin of the board (EX: T0, T1, etc..)

int value = 0;
Trigger trigger (PIN_INPUT);
bool touched1 = false;
bool touched2 = false;

void setup(){
  Serial.begin(115200);
  delay (2000);

  trigger.initialize();
  Serial.printf("Initialized as follow:");
  trigger.debug();
  Serial.printf("\n");
}

void loop(){
 
  value = touchRead(T0);
  trigger.update(value);
  Serial.println(value);
  trigger.debug();

  //The properly touch button and what to do when touched
  /*if (value < trigger) {                  //check if being touched 
    touched1 = true;
  } else {
    touched1 = false;
  }
  if (touched1 == true && touched2 == false)  //Do action on touch
  {
    
  //--------------actions to do-------------------

  }
  touched2 = touched1;*/
  delay(1000);
}