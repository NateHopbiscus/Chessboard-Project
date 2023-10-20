//Libraries Needed for the Code to Work
#include <Adafruit_NeoPixel.h>
#include <Adafruit_MCP23X08.h>
//Initialize Values for Later
#define ON LOW
#define OFF HIGH
#define CHESSPIECE 0
#define NOCHESSPIECE 1

//Column Array
uint8_t columns[8];
uint8_t colPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

//Device Setup
Adafruit_NeoPixel pixels(79, 11, NEO_GRB + NEO_KHZ800);
Adafruit_MCP23X08 mcp;


void piece_color(uint8_t start, int piece) {
  for (int i = start; i < start + 1; i++) {
    if (piece == true) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 255));
    }
    else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
}

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  for (int i = 0; i < 8; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  } //Set all column pins to INPUT
  //Initialize MCP device
  mcp.begin_I2C();
  //Set all Transistor Pins to OUTPUT
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  //Then turn them all off.
  mcp.digitalWrite(0, OFF);
  mcp.digitalWrite(1, OFF);
  mcp.digitalWrite(2, OFF);
  mcp.digitalWrite(3, OFF);
  mcp.digitalWrite(4, OFF);
  mcp.digitalWrite(5, OFF);
  mcp.digitalWrite(6, OFF);
  mcp.digitalWrite(7, OFF);
}

void loop() {
  //For loop runs through the Rows (k) and then the columns in each row (i)
  //Code scans for a Low Signal, caused by a magnet being in proximity to hall effects
  for (int k = 0; k < 8; k++) {
    mcp.digitalWrite(k, ON);
    delayMicroseconds(300);
    for (int i = 0; i < 8; i++) {
      if (digitalRead(colPins[i]) == CHESSPIECE) {
        piece_color((i + (k * 8)), true);
      } else {
        piece_color((i + (k * 8)), false);
      }
    }
    mcp.digitalWrite(k, OFF);
  }
  pixels.show();
}
