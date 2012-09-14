#include "SPI.h"
#include "Adafruit_WS2801.h"

/*
  Dynamic Reactive lighting 
 
 This is controller software for LED Lights. It will be dynamic and react 
 to the environment it's placed in, as well as being network-connected.
 The lights will also increase the utility of lighting by responding to
 the needs of the building occupants. It will do this using a variety
 of sensors and APIs. The entire project will leverage and consist of
 open source software and open hardware.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 
 
 You must get the Adafruit-WS2801-Library below if you wish to drive WS2801 pixels.
 Thank you Adafruit Industries! This would not have been possible without you!
/*****************************************************************************
 * Example sketch for driving Adafruit WS2801 pixels! -> https://github.com/adafruit/Adafruit-WS2801-Library
 * 36mm Square shape ----> https://www.adafruit.com/products/683
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 * 
 *****************************************************************************

 You will need an arduino compatible microcontroller and the arduino software.
 http://arduino.cc/en/Main/Software
 
 Thank you Noisebridge hacker space!
*/


int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

int incomingByte = 0;
char incomingString[10];

int grpx = -1; //hyperWipe iterator

//button
int ledPin = 13;                // Button LED is connected to pin 13
int buttonPin0 = 12;              // button is connected to pin 2
int buttonStatus0;                        // variable for reading the button status
int buttonDelayStatus0;                  //pin status after delay
int buttonMode0 = 0;
int buttonEffect0 = 0;

// Don't forget to connect the ground wire to Arduino ground,

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(60, dataPin, clockPin);

void setup() {

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  //button
  /*
  pinMode(ledPin, OUTPUT);      // Set the LED pin as output
   pinMode(buttonPin0, INPUT);    // Set the switch pin as input
   */
  Serial.begin(9600);
}


void loop() {


  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    incomingString[0] = incomingByte;
  }
  else{//set the mode to r if no mode is set
    if (incomingString[0] == 0){
      incomingString[0] = 'r';
    }
  }


  switch(incomingString[0])
  {
  case 'a': 
    setColor(Color(125, 0, 255));
    break;

  case 'l': 
    colorWipe(Color(64, 156, 255), 0);
    break;

  case 's': 
    breathe(0, 100, 255);
    break; 

  case 'f': 
    breatheHyperWipe(Color(0,235,255) ,Color(255, 0, 0)) ;
    break;           

  case 'h': 
    breathe(125, 0, 255);
    break; 

  case 'b': 
    breathe(167, 0, 255);
    break; 

  case 't': 
    setColor(Color(255, 241, 224));
    break; 

  case 'o': 
    setColor(Color(255, 60, 0));
    break; 

  case 'p': 
    breathe(255, 60, 0);
    break; 

  case 'r': 
    rainbowCycle(5);
    break; 

  case 'e': 
    rainbow(50);
    break; 


  }



  //examples

  //colorWipe(Color(255, 0, 0), 500);
  //colorWipe(Color(255, 255, 0), 500);
  //colorWipe(Color(0, 255, 0), 500);
  //colorWipe(Color(0, 255, 255), 500);
  //colorWipe(Color(0, 0, 255), 500);
  //colorWipe(Color(255, 0, 255), 500);
  //colorWipe(Color(225, 255, 200), 500);
  //colorWipe(Color(255, 0, 0), 0);
  //colorWipe(Color(255, 255, 255), 0);
  //colorWipe(Color(215, 175, 255), 0);
  //colorWipe(Color(167, 0, 255), 0);  //black light
  //colorWipe(Color(125, 0, 255), 0);  //heroku
  //colorWipe(Color(64, 156, 255), 0);  //blue sky
  //colorWipe(Color(201, 226, 255), 0);  //overcast
  //colorWipe(Color(255, 197, 143), 0);  //light bulb
  //colorWipe(Color(255, 241, 224), 0);  //halogen

  //rainbow(50);

  //breathe(125, 0, 255);

  //strip.setPixelColor(addrGrid(1, 3), Color(255, 255, 255));
  //strip.setPixelColor(addrGrid(4, 3), Color(255, 255, 255));
  //    strip.show();  

  //  breatheHyperWipe(Color(0,235,255) ,Color(255, 0, 0)) ;

  //rainbowCycle(5);

  //setColor(Color(255, 0, 0));
  //setColor(Color(255, 255, 0));
  //setColor(Color(0, 255, 0));
  //setColor(Color(255, 255, 255));
  //setColor(Color(0, 0, 255));
  //setColor(Color(255, 241, 224));
  //setColor(Color(255, 197, 143));
  //setOffsetColor(Color(255, 147, 41),0,3);
  //breathe(125, 0, 255);

}

void breatheHyperWipe(uint8_t brc ,uint8_t wic) {
  breathe(0,235,255);
  hyperWipe(Color(255, 0, 0));
}

void happyFace() {
  // happy face
  strip.setPixelColor(addrGrid(2, 1), Color(255, 255, 255));
  strip.setPixelColor(addrGrid(3, 1), Color(255, 255, 255));
  strip.setPixelColor(addrGrid(1, 3), Color(255, 255, 255));
  strip.setPixelColor(addrGrid(2, 4), Color(255, 255, 255));
  strip.setPixelColor(addrGrid(3, 4), Color(255, 255, 255));
  strip.setPixelColor(addrGrid(4, 3), Color(255, 255, 255));

  strip.show();
}

void rainbow(uint8_t wait) {
  int i, j;

  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

void seizure(){
  setColor(Color(255, 0, 0));
  delay(50);
  setColor(Color(0,0,0));
  delay(50);
  setColor(Color(0, 255, 0));
  setColor(Color(0,0,0));
  delay(50);
  setColor(Color(0, 0, 255));
  setColor(Color(0,0,0));
  delay(50);
  setColor(Color(255, 0, 0));
  delay(50);
  setColor(Color(255, 255, 255));
  setColor(Color(0,0,0));
  delay(50);
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}



// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    if (i != grpx) { 
      strip.setPixelColor(i, c);
      strip.show();
    }
    delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = g;
  c <<= 8;
  c |= r;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void setColor(uint32_t c) {
  int i;
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();

}

void breathe(int r, int g, int b) {
  float breatheBase = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  r = (breatheBase/255)*r;
  g = (breatheBase/255)*g;
  b = (breatheBase/255)*b;
  setColor(Color(r, g, b));
}

void hyperWipe(uint32_t grc){
  grpx++;
  if (grpx > 16) {
    grpx = 0;
  }
  strip.setPixelColor(grpx, grc);
  strip.show();
}


void setOffsetColor(uint32_t c, int offset, int occurence) {
  int i;

  for (i=offset; i < strip.numPixels() - offset; i=i+occurence) {
    strip.setPixelColor(i, c);
  }
  strip.show();

}


int addrGrid(int x, int y)  {  //find sequential number in grid
  if (y == 1) {
    return(abs(x - 4));
  }

  if (y == 2) {
    return(x + 3); 
  }

  if (y == 3) {
    return(abs(x - 4)+8);
  }

  if (y == 4) {
    return(x + 11); 
  }  
}


void operateSwitch()  {
  buttonStatus0 = digitalRead(buttonPin0);      // read input value and store it in val
  delay(2);                         // 10 milliseconds is a good amount of time
  buttonDelayStatus0 = digitalRead(buttonPin0);     // read the input again to check for bounces
  if (buttonStatus0 == buttonDelayStatus0) {                 // make sure we got 2 consistant readings!
    if (buttonStatus0 != buttonMode0) {          // the button state has changed!
      if (buttonStatus0 == HIGH) {                // check if the button is pressed
        if (buttonEffect0 == 0) {          // is the light off?
          buttonEffect0 = 1;               // turn light on! 

        }
      }
    }
  }
}






