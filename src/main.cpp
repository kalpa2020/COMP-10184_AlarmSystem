// COMP-10184 – Mohawk College
// IoT Project #1 - Alarm System
//
// This program mimics a home alarm system.
//
// @author    Kalpa Wickramathunga
// @id        000378875
//
// I, Kalpa Wickramathunga, student number 000378875 certify that this is my original work.  
//
 
#include <Arduino.h> 
 
// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6
#define LED_DELAY 10000

int BLINK_DELAY = 125;
bool ALARM_ACTIVATED = true;

// ************************************************************* 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // configure the LED output 
  pinMode(LED_BUILTIN, OUTPUT); 
 
  // PIR sensor is an INPUT 
  pinMode(PIN_PIR, INPUT); 
 
  // Button is an INPUT 
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // Turn the LED off
  digitalWrite(LED_BUILTIN, HIGH);
} 
 
// ************************************************************* 
void loop() {
  bool bPIR;
  int iButton = digitalRead(PIN_BUTTON);

  if (iButton == 0) {
    // Activates the alarm when the user clicks the button
    ALARM_ACTIVATED = true;
  }
 
  // Read PIR sensor (true = Motion detected!).  As long as there 
  // is motion, this signal will be true.  About 2.5 seconds after  
  // motion stops, the PIR signal will become false. 
  bPIR = digitalRead(PIN_PIR);

  // Checks if the alarm is on and if motion is detected
  if (bPIR && ALARM_ACTIVATED) {
    bool deactivateAlarm = false;

    // The LED blinks for 10 seconds
    for (int i = 0; i < 40; i++) {
      // Checks if the button is pressed
      iButton = digitalRead(PIN_BUTTON);
      // If the button is pressed, deactivate the alarm
      if (iButton == 0) {
        deactivateAlarm = true;
        break;
      }
      digitalWrite(LED_BUILTIN, !bPIR);
      delay(BLINK_DELAY);
      digitalWrite(LED_BUILTIN, bPIR);
      delay(BLINK_DELAY);
    }

    if (deactivateAlarm) {                // Check if the user deactivated the alarm
      digitalWrite(LED_BUILTIN, HIGH);    // Turns the LED off
      ALARM_ACTIVATED = false;
      iButton = 1;
    } else {                              // If the alarm wasn't deactivated
      digitalWrite(LED_BUILTIN, LOW);     // Turn the LED on
      ALARM_ACTIVATED = false;
    }
    
  }
  
}