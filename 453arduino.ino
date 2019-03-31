#include <Adafruit_DotStar.h>

#define NUMPIXELS 64 // Number of LEDs in strip
 
// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

//Else if using standard spi & clk pins use this
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

uint32_t serialData = 0;   //Holds a byte of incoming data
char colorInt[8] = {0};   //Holds the whole string of data
int ledPos = 0;          //Current Led to be illuminated
int strPos = 0;              //position of colorInt to place incoming byte at

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off' 
  strip.setBrightness(5);
  Serial.begin(9600); 
}

void loop() {
 if (Serial.available())
       {//if serial data receivied
              serialData = Serial.read();      //Read incoming byte
               
              Serial.print("I received: ");     //Display individual bytes, for testing purposes
              Serial.println(serialData, HEX);
              
              if(serialData != 10){       //arduino terminal sends 10 at end of string so check for that, can be changed to whatever char marks end of a color's data
                colorInt[strPos++] = serialData; 
              }

            
              if(serialData == 10){      //if end found, then turn hex string to hex number, set color at position, reset variables as needed
              //Serial.println(strtoul(colorInt,NULL,16));
              strip.setPixelColor(ledPos++,strtoul(colorInt,NULL,16));
              if(ledPos >= 64)ledPos = 0;
              for(int i = 0; i < 8; i++)colorInt[i] = 0;          
              strPos = 0;
              }
       }//end of serial data 
       strip.show();
}


/*
// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 64 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
//Adafruit_DotStar strip = Adafruit_DotStar(
//  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  strip.setBrightness(5);
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)

void loop() {
  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(20);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
}*/
