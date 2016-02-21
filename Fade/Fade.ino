#include <Adafruit_NeoPixel.h>

#define PIN 6 // the Data Pin for the strip.
#define NUMPIXELS 300 // how many pixels are on the strip

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int incoming;
int r = 24;
int g = 8;
int b = 64;

void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  Serial.begin(115200);

}

void loop() {
  for(int q = 0; q < 64; q += 1){
  for(int i = 0; i < strip1.numPixels(); i+=1){
    strip1.setPixelColor(i, strip1.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip1.show();
  delay(10);
  }
  for(int q = 64; q > 0; q -= 1){
  for(int i = 0; i < strip1.numPixels(); i+=1){
    strip1.setPixelColor(i, strip1.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip1.show();
  delay(10);
  }
}
