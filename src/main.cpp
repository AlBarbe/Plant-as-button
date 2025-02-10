#include <Arduino.h>

#define PIN_LED     22    //GPIO used as led output signal
#define BUTTON_PIN  35    //GPIO for the button used to reset trigger level

int value = 0;
int trigger = 65;
bool touched1 = false;
bool touched2 = false;
int lastState = HIGH;     // the previous state from the input pin
int currentState;

void setup(){
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  {
    Serial.println("Setiing up trigger level");
    int min = 100;                        //max value that touch can output
    for (int i = 0; i < 30; i++) {        //this cycle seek for the lowes value
      value = touchRead(T0);              
      if (value < min) {
        min = value;
      }
    }
    trigger = min - 7;                    //set trigger n times lower than value
    Serial.print("trigger set to:  ");
    Serial.println(trigger);
  }
}

void loop(){

  value = touchRead(T0);
  currentState = digitalRead(BUTTON_PIN);
  //Serial.println(currentState);         //if you need debug in console
  //Serial.println(value);

  //Button to change Trigger level
  if(lastState == LOW && currentState == HIGH){
    Serial.println("The state changed from LOW to HIGH");

    int min = 100;                        //max value that touch can output
    for (int i = 0; i < 30; i++) {        //this cycle seek for the lowes value
      value = touchRead(T0);              
      if (value < min) {
        min = value;
      }
    }
    trigger = min - 7;                    //set trigger n times lower than value
    Serial.print("trigger set to:  ");
    Serial.println(trigger);
  }

  //The properly touch button and what to do when touched
  if (value < trigger) {                  //check if being touched 
    touched1 = true;
  } else {
    touched1 = false;
  }
  if (touched1 == true && touched2 == false)  //Do action on touch
  {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));
  }

  lastState = currentState;
  touched2 = touched1;
  delay(100);
}