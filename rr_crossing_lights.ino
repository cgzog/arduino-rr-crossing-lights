//  rr_crossing_lights
//
//  flashes a typical railroad crossing light set with a fade on and fade off effect
//  for each light which simulates incandesent bulbs rather than LEDs
//
//
// Built using the 1.6.7 Arduino IDE
//
//
// Copyright (c) 2016, Christian Herzog
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other materials
//    provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be used
//    to endorse or promote products derived from this software without specific prior written
//    permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
// AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#define LED_LEFT_1  5       // LED connections
#define LED_LEFT_2  6       // must be PWM-capable ports!

#define LED_RIGHT_1 10
#define LED_RIGHT_2 11

// the values below looked good to me and gave me the approximately 1Hz rate from the DOT regulations
// found online - tune to suit you taste
#define LED_ON_TIME     400 // milliseconds
#define LED_FADE_TIME   100 // milliseconds
#define LED_FADE_STEPS  6

#define LED_ON      255 // full PWM
#define LED_OFF     0


void setup() {

  pinMode(LED_LEFT_1, OUTPUT);      // set up the output pins
  pinMode(LED_LEFT_2, OUTPUT);
  pinMode(LED_RIGHT_1, OUTPUT);
  pinMode(LED_RIGHT_2, OUTPUT);
  
  analogWrite(LED_LEFT_1, 255);
  analogWrite(LED_LEFT_2, 255);    // left set on

  analogWrite(LED_RIGHT_1, 0);
  analogWrite(LED_RIGHT_2, 0);     // right set off
}

void loop() {

int i;

  while (1) {
    
    delay(LED_ON_TIME);                      // left is on at the start of each loop
  
    for (i = 0 ; i < LED_FADE_STEPS; i++) {  // fade left down and right up

      analogWrite(LED_LEFT_1, LED_ON - (LED_ON / LED_FADE_STEPS * i)); // fade left down
      analogWrite(LED_LEFT_2, LED_ON - (LED_ON / LED_FADE_STEPS * i));

      analogWrite(LED_RIGHT_1, LED_ON / LED_FADE_STEPS * i);           // fade right up
      analogWrite(LED_RIGHT_2, LED_ON / LED_FADE_STEPS * i);

      delay(LED_FADE_TIME / LED_FADE_STEPS);  // wait for the appropriate amount of time based on the total fade time and number of steps
    }

    analogWrite(LED_RIGHT_1, 255);            // make sure things are fully on / off as appropriate
    analogWrite(LED_RIGHT_2, 255);            // right fully on

    analogWrite(LED_LEFT_1, 0);
    analogWrite(LED_LEFT_2, 0);               // left fully off
    
    delay(LED_ON_TIME);                       // wait "on" time

    for (i = 0 ; i < LED_FADE_STEPS; i++) {  // fade right down and left up

      analogWrite(LED_RIGHT_1, LED_ON - (LED_ON / LED_FADE_STEPS * i));
      analogWrite(LED_RIGHT_2, LED_ON - (LED_ON / LED_FADE_STEPS * i));

      analogWrite(LED_LEFT_1, LED_ON / LED_FADE_STEPS * i);
      analogWrite(LED_LEFT_2, LED_ON / LED_FADE_STEPS * i);

      delay(LED_FADE_TIME / LED_FADE_STEPS);
    }

    analogWrite(LED_LEFT_1, 255);
    analogWrite(LED_LEFT_2, 255);   // left fully on

    analogWrite(LED_RIGHT_1, 0);
    analogWrite(LED_RIGHT_2, 0);     // right fully off
  }
}
