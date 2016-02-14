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
  for(int b = 0; b < 4; b++){
blink(0,0,64,500);
}
easter(50,79,100);
  for(int b = 0; b < 4; b++){
ripple(0,0,64,6,35);
  }
}

void solidColor(int r, int g, int b){
   for(int i = 0; i < strip1.numPixels(); i++){
    strip1.setPixelColor(i, strip1.Color(r,g,b));
  }
  
  strip1.show();
}
void blink(int r, int g, int b, int wait) {
  solidColor(r,g,b);
 delay(wait);
 solidColor(0,0,0);
 delay(wait);
 
}
void easter(int r,int g,int b){
    int num = 0;
  
  for(int i = strip1.numPixels(); i > 0; i--){
    int R = random(r);
    int G = random(g);
    int B = random(b);
    for(int r = num + 1; r <= i; r++){
      strip1.setPixelColor(r, strip1.Color(R,G,B));
      strip1.show();
      delayMicroseconds(10);
      strip1.setPixelColor(r, strip1.Color(0,0,0));

     
    }
    strip1.setPixelColor(i, strip1.Color(R,G,B));

     for(int k = i - 1; k >= num; k--){
        strip1.setPixelColor(k, strip1.Color(R,G,B));
        strip1.show();
        delayMicroseconds(10);
        strip1.setPixelColor(k, strip1.Color(0,0,0));
      }
   
   strip1.setPixelColor(num, strip1.Color(R,G,B));
   num++;

   
  }
  strip1.show();
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
