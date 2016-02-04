#include <Adafruit_NeoPixel.h>

#define PIN 6 // the Data Pin for the strip.
#define NUMPIXELS 300 // how many pixels are on the strip

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int incoming;

void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  Serial.begin(115200);

}

void loop() {
  if (Serial.available() > 0) {
    incoming = Serial.read(); // reads the next thing sent on the serial line.
    if (incoming == 'a') {
      Serial.println ("Auto Enabled!");
    }
  }
  
  for(int i = 0; i < strip1.numPixels(); i++){
    strip1.setPixelColor(i, strip1.Color(0,128,0));
  }
  
  strip1.show();
}
