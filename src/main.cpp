#include <Arduino.h>

/*
Bus Buddies. code for triggering the relay by sending a message in serial monitor. Future implementation is hooking it up to other sensors to make a
motion sensor.
*/
//Celebratory code
const int RELAY_PIN = 9;
const int BAUD_RATE = 9600;
//How long to trigger sensor, in MILLISECONDS
const int triggerDuration = 10000;
//what user types to trigger light
const char motionInput = 'M';
//starts off not detecting motion
bool motionDetected = false;

void setup() {
  // initialize digital pin 9 as an output.
  pinMode(RELAY_PIN, OUTPUT);
  // Start serial comm
  Serial.begin(BAUD_RATE);
}

void loop() {
  while (!motionDetected) {
    if (Serial.available() > 0) {
      char input = (char)Serial.read();
      if(input == motionInput) {
        motionDetected = true;
      }
    }  
  }
  
  digitalWrite(RELAY_PIN, HIGH);
  //not the prettiest code, but is a workaround to not having printf
  int durationInSecs = triggerDuration/1000;
  Serial.println("Motion detected, light triggered for ");
  Serial.print(durationInSecs);
  Serial.print(" secs.\n");
  //Serial.printf("Motion detected, light triggered for %d secs\n", triggerDuration/1000);
  delay(triggerDuration);
  digitalWrite(RELAY_PIN, LOW);
  motionDetected = false;
}
