#include <Metro.h> // Include the Metro library
#include "variables.h"
#include "Myprintf.h"
#include "OLED.h"
#include "ProcessCommands.h"
#include "SubHandeling.h"

#define DEBUGMODE true


void setup() {

  Serial.begin(9600);
  initOLED();
  setupInput (BTNFASTER_PIN, btnFaster);
  setupInput (BTNSLOWER_PIN, btnSlower);
  setupInput (BTNUP_PIN, btnUp);
  setupInput (BTNDOWN_PIN, btnDown); 
}

void loop() {
  ProcessCommands();
  SubHandeling();
}

void setupInput (int InputPin, Bounce &bounceObject) {
  pinMode(InputPin, INPUT_PULLUP);
  bounceObject.attach(InputPin);
  bounceObject.interval(5);
}

