#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Math.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define NavDialCenterX 80
#define NavDialCenterY 32
#define NavDialRadius 31
#define ShortDialLength 20

void initOLED() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(100);

  // Clear the buffer.
  display.clearDisplay();
}
void updateIndicators () {
  display.clearDisplay();

  // --------------------------------------
  // Nav Dial graphic
  // --------------------------------------
  
  display.drawCircle(NavDialCenterX, NavDialCenterY, NavDialRadius, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(NavDialCenterX-4,(NavDialCenterY - NavDialRadius) + 4);  display.print ("N");
  display.setCursor(NavDialCenterX-4,(NavDialCenterY + NavDialRadius) - 10);  display.print ("S");
  display.setCursor((NavDialCenterX - NavDialRadius) + 4,NavDialCenterY - 2);  display.print ("W");
  display.setCursor((NavDialCenterX + NavDialRadius) -7,NavDialCenterY - 3);  display.print ("E");

  int dx, dy;
  dx = sin(Heading * RADIANFACTOR) * ShortDialLength;
  dy = cos(Heading * RADIANFACTOR) * ShortDialLength;
  display.drawLine (NavDialCenterX ,NavDialCenterY,NavDialCenterX + dx, NavDialCenterY - dy, WHITE);
  display.fillCircle (NavDialCenterX ,NavDialCenterY,3, WHITE);

  for (int i=0; i<NavDialRadius; i+=4) {
      dx = sin(DesiredHeading * RADIANFACTOR) * (NavDialRadius - 3 - i);
      dy = cos(DesiredHeading * RADIANFACTOR) * (NavDialRadius - 3-i);
      display.drawPixel (NavDialCenterX + dx, NavDialCenterY - dy, WHITE);
  }

  // --------------------------------------
  // Speed indicator
  // --------------------------------------

  display.setCursor (0,0); display.print ("SPEED:");
  display.setCursor (0,9); display.print ((int) Speed ); display.print ("/"); display.print( (int) DesiredSpeed);

  // --------------------------------------
  // Depth indicator
  // --------------------------------------
  display.setCursor (0,48); display.print ("DEPTH:");
  display.setCursor (0,57); display.print ((int) Depth ); display.print ("/"); display.print( (int) DesiredDepth);
  
  display.display();
}
void updateIndicators_() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(13,0);
  display.print("ACTUAL");
  display.setCursor(80,0);
  display.print ("DESIRED");

  display.drawLine (11,10,47,10, WHITE);
  display.drawLine (80,10,120,10, WHITE);
  
  display.setCursor(62,14);
  display.print("D");
  display.setCursor(62,24);
  display.print("S");
  
  display.setCursor(26,14);
  display.println((int) Depth);
  display.setCursor(96,14);
  display.println((int) DesiredDepth);

  display.setCursor(26,24);
  display.println((int) Speed);
  display.setCursor(96,24);
  display.println((int) DesiredSpeed);

  display.display();
}

