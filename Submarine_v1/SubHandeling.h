
void SubHandeling() {

  if (SubHandelingTimer.check() == 1) { // check if the metro has passed it's interval .

        // ----------------------------------------------
        // Change Depth
        // ----------------------------------------------

        float temp_speed = Speed;
        float delta_depth = 0.0;
      
        if (temp_speed < 0)   temp_speed = -temp_speed;
        if (DesiredDepth < 0) 
            DesiredDepth = 0;
        else if (DesiredDepth > MaxDepth)
            DesiredDepth = MaxDepth;
      
        delta_depth = temp_speed * PLANES_CHANGE;
        
        if (delta_depth < 1.0)      delta_depth = 1.0;
        else if (delta_depth > 5.0) delta_depth = 5.0;
        
        if (DesiredDepth > Depth){  //Do we need to go up?
            Depth += delta_depth;
            if (Depth > DesiredDepth) Depth = DesiredDepth;     //Flatten us out
        }
      
        if (DesiredDepth < Depth){  //Do we need to go down?
            Depth -= delta_depth;
            if (Depth < DesiredDepth) Depth = DesiredDepth;
        }

        // ----------------------------------------------
        //Change Heading
        // ----------------------------------------------
      
        float AmountOfChange; //How much to turn the boat.
        AmountOfChange = (Rudder * temp_speed) * RUDDER_CHANGE;
        if (AmountOfChange>0.0) Myprintf ("Rudder change %f", AmountOfChange);

        if (Heading > DesiredHeading){
          if ((Heading - DesiredHeading) < 180){
            Heading = Heading - AmountOfChange;
            if ((Heading < DesiredHeading) &&
            ((DesiredHeading - Heading) < AmountOfChange)){
              Heading = (float)DesiredHeading;
            }
          }
          else{
            Heading = Heading + AmountOfChange;
            if ((Heading > DesiredHeading) &&
            ((Heading - DesiredHeading) < AmountOfChange)){
              Heading = (float)DesiredHeading;
            }
          }
        }
        else{
          if (Heading < DesiredHeading){
            if ((DesiredHeading - Heading) < 180){
              Heading += AmountOfChange;
              if ((Heading > DesiredHeading) &&
              ((Heading - DesiredHeading) < AmountOfChange)){
                Heading = (float)DesiredHeading;
              }
            }
            else{
              Heading = Heading - AmountOfChange;
              if ((Heading < DesiredHeading) &&
              ((DesiredHeading - Heading) < AmountOfChange)){
                Heading = (float)DesiredHeading;
              }
            }
          }
        }
      
        if (Heading > 360)      Heading = Heading - 360.0;
        else if (Heading < 0)   Heading = Heading + 360.0;
        //Myprintf ("Heading: %f / %f", Heading, DesiredHeading);

        // ----------------------------------------------
        // Change Speed
        // ----------------------------------------------
        if (DesiredSpeed > Speed){ //Speed Up
          Speed += 0.45; //a little less than 1/2 a knot per second..
          if (Speed > DesiredSpeed) Speed = DesiredSpeed; // Did we go past target speed?
        }
      
        if (Speed > DesiredSpeed){ //Slow Down
          Speed -= 0.45;
          if (Speed < DesiredSpeed) Speed=DesiredSpeed; // Did we slow too much?
        }
        // Myprintf ("Current speed: %f/%f  Depth: %f/%f", Speed, DesiredSpeed, Depth, DesiredDepth);
        SubHandelingTimer = Metro(1000); // Reset the clock
  }
  if (ScreenRefreshTimer.check() == 1) {
          updateIndicators();
          ScreenRefreshTimer = Metro(300);
  }
}

