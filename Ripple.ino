#include <Adafruit_NeoPixel.h>

#define PIN 6 // the Data Pin for the strip.
#define NUMPIXELS 300 // how many pixels are on the strip

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int incoming;
boolean redAlliance = true; // will default to red.
boolean isFading = true; //makes it fade instead of single color.


void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  Serial.begin(115200);

}

void loop() {
  if (Serial.available() > 0) {
    incoming = Serial.read(); // reads the next thing sent on the serial line.
    switch (incoming) {
        case 'a': // if incoming == 'r' it will do this
          //auto mode stuff
          break; // the _break;_ is the most important part. Never Forget!
        case 'r':
            redAlliance = true;
            isFading = false;
          break;
        case 'b':
          //BLUE!
          redAlliance = false;
          isFading = false;
          break;
        default: //this happens if incoming doesn't match any of the above
          isFading = true;
      }
    }
if (isFading){
    for(int n = 0; n < 48; n+= 4) {
      ripple(n, 0, 48-n, 7, 30);
    }
    for(int n = 48; n > 0; n-= 4) {
      ripple(n, 0, 48-n, 7, 30);
    }
  } else if (redAlliance) {
    ripple(64, 0, 0, 7, 30);
  } else {
    ripple(0, 0, 64, 7, 30);
  }
}



void ripple(int r, int g, int b, byte magnitude, byte wait){
  for (int s = (magnitude * -2); s < 0; s++){
    if (Serial.available() == 0){
    for (int p = 0; p < strip1.numPixels() + (2 * magnitude); p += (2*magnitude)) {
      for (int i = 0; i < magnitude; i++){
        if ((p+i-s) >= 0 && p+i-s < strip1.numPixels()){
          strip1.setPixelColor(p+i-s, strip1.Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
        }
      }
      for (int i = magnitude; i > 0; i--) {
        if ((p-s+((magnitude * 2) - i)) >= 0 && (p-s+((magnitude * 2) - i)) < strip1.numPixels()){
          strip1.setPixelColor((p-s+((magnitude * 2) - i)), strip1.Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
        }
      }
    }
    strip1.show();
      delay(wait);
    }
  }
}

