void ProcessCommands() {
  
  btnFaster.update();
  if (btnFaster.fell()  ) {
    DesiredSpeed += speedIncrement;
    if (DesiredSpeed > MaxSpeed) DesiredSpeed = MaxSpeed;
    #if DEBUGMODE
    Serial.println ("going faster");
    #endif
  }
  
  btnSlower.update();
  if (btnSlower.fell() ) {
    DesiredSpeed -= speedIncrement;
    if (DesiredSpeed < MinSpeed) DesiredSpeed = MinSpeed;
    #if DEBUGMODE
    Serial.println ("going slower");
    #endif
  }

  btnUp.update();
  if (btnUp.fell() ) {
    DesiredDepth -= diveIncrement;
    if (DesiredDepth < 0) DesiredDepth = 0;
    #if DEBUGMODE
    Serial.println ("going up");
    #endif
  }

  btnDown.update();
  if (btnDown.fell() ) {
    DesiredDepth += diveIncrement;
    if (DesiredDepth > MaxDepth) DesiredDepth = MaxDepth;
    #if DEBUGMODE
        Serial.println ("going down");
    #endif
  }

  if (PotHandelingTimer.check() == 1) {
      // What direction should we go?
      int val = analogRead(DirectionAnalogPin);    // read the value from the sensor
      if (val>412 && val<612) {  // then go straight
      } else if (val >=612) { // turn to the left
            DesiredHeading -=1;
            if(DesiredHeading < 0) DesiredHeading += 360;
      } else { // turn to the right
            DesiredHeading+=1;
            if(DesiredHeading > 359) DesiredHeading -= 360;    
      }
      
      PotHandelingTimer = Metro(100); // reset timer
  }

  if (Serial.available() > 0) {
    char ch = Serial.read();
    switch (ch) {
      case 'l':
        DesiredHeading -=5;
        if(DesiredHeading < 0) DesiredHeading += 360;
        break;
      case 'r':
        DesiredHeading+=5;
        if(DesiredHeading > 359) DesiredHeading -= 360;
        break;
    }
  }
}
