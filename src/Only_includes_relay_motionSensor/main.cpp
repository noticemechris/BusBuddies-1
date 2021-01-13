#include <Arduino.h>

/*
Bus Buddies. code for triggering the relay by motion sensor. Future implementation is hooking it
up to other sensors to make a motion sensor. IMPORTANT: right now the motion sensor will turn the
light on for a set amount of time, see:TRIGGER_DURATION, however we can code it so the light will
only be on when motion is detected. Personally, I'm in the boat of doing it for a set duration
of time as our most vulnerable user will be sitting still under the stop by themself. Will plan
to bring this up on the meeting of Saturday 1/16 .

FUTURE WORK TODO: Implement clock
*/

//Celebratory code
const int RELAY_PIN = 10;
const int MOTION_SENSOR_PIN = 2;
//Sets up motion sensor
int motionState = LOW;
//Sets Baud rate for serial comm
const int BAUD_RATE = 9600;
//How long to trigger sensor, in MILLISECONDS
const int TRIGGER_DURATION = 15000;
//What user types to trigger light
const char MOTION_INPUT = 'M';
//Starts off not detecting motion
bool motionDetected = false;

void setup() {
  // initialize relay pin as an output.
  pinMode(RELAY_PIN, OUTPUT);
  //Initialize motion sensor pin as an input
  pinMode(MOTION_SENSOR_PIN, INPUT);
  // Start serial comm
  Serial.begin(BAUD_RATE);
}

void loop() {
  motionState = digitalRead(MOTION_SENSOR_PIN);   // read new state
  if (motionState == HIGH) {   // pin state change: LOW -> HIGH
    lightOn();
  }
}

//Turns light on
void lightOn() {
  logLightOn();
  digitalWrite(RELAY_PIN, HIGH);
  delay(TRIGGER_DURATION);
  digitalWrite(RELAY_PIN, LOW);;
}

//Tells user light is on for a certian duration. Future implementation is pinging server.
void logLightOn() {
  //not the prettiest code, but is a workaround to not having printf
  int durationInSecs = TRIGGER_DURATION/1000;
  Serial.println("Motion detected, light triggered for ");
  Serial.print(durationInSecs);
  Serial.print(" secs.\n");
}