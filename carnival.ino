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
 for(int c = 0; c < 3; c++){ 
  for(int i = 0; i < strip1.numPixels(); i+=3){
    strip1.setPixelColor(i+c, strip1.Color(random(50),random(50),random(50)));
    strip1.setPixelColor(i+c-1, strip1.Color(0,0,0));
    
    //strip1.setPixelColor(i+1, strip1.Color(0,255,0));
    //strip1.setPixelColor(i+2, strip1.Color(0,0,255));
  }
  strip1.show();
    delay(50);
}
}
