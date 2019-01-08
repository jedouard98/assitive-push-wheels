#include <Adafruit_NeoPixel.h> // include neopixel library

#define PIN 12 // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 3 // How many NeoPixels are attached to the Arduino?

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int val;
// runs when you turn on the Flora
void setup() {
  Serial.begin(9600);       // start serial communication at 9600bps
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setPixelColor(0, pixels.Color(100, 100, 100));
  pixels.setPixelColor(1, pixels.Color(100, 100, 100));
  pixels.setPixelColor(2, pixels.Color(100, 100, 100));
}

void loop() {
while (Serial.available() > 0) {
       // if data is available to read
    int red = Serial.parseInt();           // read it and store it in 'val'
    int green = Serial.parseInt();
    int blue = Serial.parseInt();

    if (Serial.read()== '\n') {
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);
     
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));
      pixels.show();
    }
   }
  }
}



