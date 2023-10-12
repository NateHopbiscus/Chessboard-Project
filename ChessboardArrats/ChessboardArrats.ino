#include <Adafruit_NeoPixel.h>

//TRANSISTORS ( WHAT TURNS THEM ON ) (IS THE SIGNAL PIN ON THE PCB )
#define ROW1 3
#define ROW2 4

#define ON LOW
#define OFF HIGH

//ON / OFF
#define CHESSPIECE 1
#define NOCHESSPIECE 0

// ARDUINO BOARD TO PCB
uint8_t columns[3];
uint8_t colPins[3] = {22, 24, 26};

//THE LEDs
Adafruit_NeoPixel pixels(24, 17, NEO_GRB + NEO_KHZ800);

void piece_color(uint8_t start, int piece) {
  for (int i = start; i < start + 4; i++) {
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

  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(ROW1, ON);

  for (int i = 0; i < 3; i++) {
    columns[i] = digitalRead(colPins[i]);
    Serial.print(columns[i]);
    if (columns[i] == CHESSPIECE) {
      piece_color(i * 4, true);
    } else {
      piece_color(i * 4, false);
    }
  }

  delay(25);
  digitalWrite(ROW1, OFF);
  delay(50);
  digitalWrite(ROW2, ON);

  for (int i = 0; i < 3; i++) {
    columns[i] = digitalRead(colPins[i]);
    Serial.print(columns[i]);
    if (columns[i] == CHESSPIECE) {
      piece_color((i + 3) * 4, true);
    } else {
      piece_color((i + 3) * 4, false);
    }
  }

  delay(25);
  digitalWrite(ROW2, OFF);
  delay(50);

  pixels.show();
  Serial.println();
  Serial.println();
  
}
