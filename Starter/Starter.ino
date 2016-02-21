#include <Adafruit_NeoPixel.h>

#define PiN 6 // the Data Pin for the strip.
#define NUMPiXELS 300 // how many pixels are on the strip

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPiXELS, PiN, NEO_GRB + NEO_KHZ800);

int incoming;

void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  Serial.begin(115200);

}

void loop() {
    /*
    if (Serial.available() > 0) {
      incoming = Serial.read(); // reads the next thing sent on the serial line.
      if (incoming == 'a') {
        Serial.println ("Auto Enabled!");
      }
    }
  */ 
  
  for (int i = 0; i < 299; i = i +1){
    strip1.setPixelColor(i,strip1.Color(255,0,0));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i,strip1.Color(0,0,0));

   //red
  }
   for (int i = 299; i > 0; i = i -1){
    strip1.setPixelColor(i,strip1.Color(255,0,0));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i,strip1.Color(0,0,0));

   //red
  }
}
