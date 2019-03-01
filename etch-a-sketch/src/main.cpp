#include <Arduino.h>
// #include <serstream>
#include <math.h>
#include <FastLED.h>
// #define NUM_STRIPS 6

// CONSTANTS
#define BRIGHTNESS 64
const int NUM_LEDS = 256;
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;
const bool    kMatrixSerpentineLayout = true;



// PINS
const int xPotPin = A0; //pin A0 to read analog input
const int yPotPin = A1
const int ledPin = 5;

//Variables:
int x_pot_value; //save analog value
int y_pot_value; //save analog value
int old_position = -1;
int current_position = -1

CRGB leds_plus_safety_pixel[NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

// MATRIX COORDINATE FN
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;

  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }

  return i;
}

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(xPotPin, INPUT); //Optional
  pinMode(yPotPin, INPUT); //Optional
  FastLED.addLeds<NEOPIXEL, ledPin>(leds);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1000);
  FastLED.setBrightness( BRIGHTNESS );
}

void loop() {
  x_pot_value = analogRead(xPotPin); //Read and save analog value from potentiometer
  y_pot_value = analogRead(yPotPin);
  x_pot_value = map(x_pot_value, 0, 1023, 0, 16); //Map value 0-1023 to 0-255 (PWM)
  y_pot_value = map(y_pot_value, 0, 1023, 0, 16);

  current_position = XYsafe( x_pot_value, y_pot_value)

  if (current_position != old_position) {
    leds[current_position] = CRGB::White;
  }

  old_position = current_position;

  delay(100);                          //Small delay
}
