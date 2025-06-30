/*
 * drive.c
 *
 *  Created on: Jun 26, 2025
 *      Author: singh
 */

#include <stdbool.h>
#include "drive.h"
#include "pwm.h"


bool Override = true;

const int MAX_AXES = 8;
extern float axes[MAX_AXES] = {0.0};

const int MAX_BUTTONS = 15;
extern int buttons[MAX_BUTTONS] = {0};




uint8_t M1=1,M2=2,M3=3,M4=4; //////////////////  <<<----------------->>>  ////////////////////
uint8_t m1=1,m2=2,m3=3,m4=4;



void digitalWrite(uint8_t channel, uint8_t value)
{
    // Map channel to PB6, PB7, PB8, PB9
    uint16_t pin;

    switch (channel)
    {
        case 1: pin = (1 << 6); break;  // PB6
        case 2: pin = (1 << 7); break;  // PB7
        case 3: pin = (1 << 8); break;  // PB8
        case 4: pin = (1 << 9); break;  // PB9
        default: return;                // Invalid channel
    }

    if (value)
        GPIOB_ODR |= pin;      // Set pin HIGH
    else
        GPIOB_ODR &= ~pin;     // Set pin LOW
}

void controlMotors(float xAxis, float yAxis, float rAnticlock, float rClock) {
  float x = xAxis * movement_speed;
  float y = yAxis * movement_speed;
  float rotAnticlock = map(-rAnticlock, -1, 1, 0, rot_speed);
  float rotclock = map(-rClock, -1, 1, 0, rot_speed);


  if(Override==1){
    analogWrite(M1, 0);
    analogWrite(M2, 0);
    analogWrite(M3, 0);
    analogWrite(M4, 0);
  }

  else if (x > 0 && y > 0) {
    //considering Left as positive and front as positive
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 0);
    analogWrite(M1, x);
    analogWrite(M2, y);
    analogWrite(M3, x);
    analogWrite(M4, y);
    Serial.println("Moving in Secound quadrant");

  }
   else if (x > 0 && y < 0) {
    digitalWrite(m1, 0);
    digitalWrite(m2, 1);
    digitalWrite(m3, 0);
    digitalWrite(m4, 1);
    analogWrite(M1,  x);
    analogWrite(M2, -y);
    analogWrite(M3,  x);
    analogWrite(M4, -y);
    Serial.println("Moving in Third quadrant");

  } else if(x < 0 && y > 0) {
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    digitalWrite(m3, 1);
    digitalWrite(m4, 0);
    analogWrite(M1, -x);
    analogWrite(M2,  y);
    analogWrite(M3, -x);
    analogWrite(M4,  y);
    Serial.println("Moving in First quadrant");
  }

 else if (x < 0 && y < 0) {
    digitalWrite(m1, 1);
    digitalWrite(m2, 1);
    digitalWrite(m3, 1);
    digitalWrite(m4, 1);
    analogWrite(M1, -x);
    analogWrite(M2, -y);
    analogWrite(M3, -x);
    analogWrite(M4, -y);
    Serial.println("Moving in Forth quadrant");
  }

  else if (x > 0 && y == 0) {
    digitalWrite(m1, 0);
    digitalWrite(m3, 0);
    analogWrite(M1, x);
    analogWrite(M2, 0);
    analogWrite(M3, x);
    analogWrite(M4, 0);
    Serial.println("Moving on -ve x-axis");
  }

  else if (x < 0 && y == 0) {
    digitalWrite(m1, 1);
    digitalWrite(m3, 1);
    analogWrite(M1, -x);
    analogWrite(M2,  0);
    analogWrite(M3, -x);
    analogWrite(M4,  0);
    Serial.println("Moving on +ve x-axis");
  }

  else if (x == 0 && y > 0) {
    digitalWrite(m2, 0);
    digitalWrite(m4, 0);
    analogWrite(M1, 0);
    analogWrite(M2, y);
    analogWrite(M3, 0);
    analogWrite(M4, y);
    Serial.println("Moving on +ve y-axis");
  }

  else if (x == 0 && y < 0) {
    digitalWrite(m2, 1);
    digitalWrite(m4, 1);
    analogWrite(M1,  0);
    analogWrite(M2, -y);
    analogWrite(M3,  0);
    analogWrite(M4, -y);
    Serial.println("Moving on -ve y-axis");
  }

  else if (rotAnticlock > 0){
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
    digitalWrite(m3, 1);
    digitalWrite(m4, 1);
    analogWrite(M1, rotAnticlock);
    analogWrite(M2, rotAnticlock);
    analogWrite(M3, rotAnticlock);
    analogWrite(M4, rotAnticlock);
    Serial.println("Rotating Anti clockwise");
  }

  else if (rotclock > 0){
    digitalWrite(m1, 1);
    digitalWrite(m2, 1);
    digitalWrite(m3, 0);
    digitalWrite(m4, 0);
    analogWrite(M1, rotclock);
    analogWrite(M2, rotclock);
    analogWrite(M3, rotclock);
    analogWrite(M4, rotclock);
    Serial.println("Rotating  Clockwise");
  }

  else {
    // Stop
    analogWrite(M1, 0);
    analogWrite(M2, 0);
    analogWrite(M3, 0);
    analogWrite(M4, 0);}

}

uint32_t getMillis(void) {
    return millis;
}

void check_override() {
    static int last_override_button = 0;
    static bool toggled_on_this_press = false;
    static uint32_t last_toggle_time = 0;

    const uint32_t debounce_ms = 200;
    uint32_t now = getMillis();

    if (buttons[9] == 1 && last_override_button == 0 && !toggled_on_this_press) {
        if (now - last_toggle_time >= debounce_ms) {
            Override = !Override;

            // Debug if using UART or LEDs
            // printf("Buttons9: %d\nOverride: %d\n", buttons[9], Override);

            last_toggle_time = now;
            toggled_on_this_press = true;
        }
    }

    if (buttons[9] == 0) {
        toggled_on_this_press = false;
    }

    last_override_button = buttons[9];
}
