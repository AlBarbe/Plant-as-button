<!-- HEADER -->
# Plant as Button 🌱

Wouldn't be cool to use as a plant a touch sensor? 
Here's something you may like...

<!-- TABLE OF CONTENTS -->
<!--
<details>
  <summary>Table of contenent</summary>
    <ul>
      <li></li><a href="#introduction">Introduction</a></li>
      <li></li><a href="#how-it-works">How it works</a></li>
      <li></li><a href="#implementatio">IMplementation</a></li>
    </ul>
</details>
-->
<!-- INTRODUCTION -->
## Introduction

This little code was created to be used on a small microcontroller, and meant to be taken as a starting point in different other broject.  
The Idea was to use only the basic library (arduino.h), without implementin external one.  
In my case is tested on a ESP32 (nodemcu-32s), and coded via VS code and Platformio.

This is my first repository on GitHub, every opinion or suggestion is more than welcome!!

<!-- HOW IT WORKS -->
## How it works
- ### Concept
  To use a plant as an input device i used an existing function of esp32, some PINs are capable of functioning as capacitive touch sensor.
  The Microcontroller's touch PIN is connected to the soil near the roots of the plant by a simple cable (note that the plant is capable of conducting electricity).
  The whole system (soil, plant, cable) work as an extension of the touch pin, meaning that when is touched by something that conduct electricity (like hand) change capacitive property.
  Using an existing funcion ( TouchRead() ) of arduino.h, can be create a trigger value level under which we consider as something is touching, virtually a switch.
  
- ### Problems
  Every plant-pot system have a unique capacitive property, meaning that the values measured by the code could be different, also with a different range of noise. The code try to resolve this by atutomitize the calculation of trigger level, based on a mean of the last measured value and an aproximative esteem of noise error. To ensure possible issues from changing position, or simply by just watering the plant, in the main is implemented a condition in which: if it's measured a touch input for more than 5 second, the trigger level reset to the new setting.
  
- ### Main
  The main is coded to work in a non-blocking way using millis() function tecnique: basically every action is triggered by a timer. When the difference between the internal clock function (millis()) the last repetition (StartMillis) is bigger than the Period meant to be waited, the "if" condition trigger the action and reset the counter (StartMIllis = millis());
  The structure is composed by a prior definition of variables and Trigger Class, followed by Void Setup() where the trigger class is initialized, than the loop.
  The loop is composed only by condition to create a non blocking code, every 100 millis the new value is read, stored, elaboreted from trigger class.
  
- ### pab.h (trigger class)
  Althought i liked the idea of creating a single, standalone main file, the creation of an header file was a better choice.
  The class coded inside store in the array the last 10 value measure (when not touched) to calculate the mean value and to create a correct trigger value.
  The class also implement function to verify if the newest value is below trigger level, meaning in a touch and to be discarded from recording; and some other utility functions.
  

## Implementation
The code is meant to be implemanted with other functionality, the idea is to put every code or action inside the triggering condition (on touch, on release, if kept pressed, after whatever time).
Inside, everithing is already noted to try to be as easy as possible to use.  
NOTE: a non-blocking code in needed to not interfere with the others part of program.
