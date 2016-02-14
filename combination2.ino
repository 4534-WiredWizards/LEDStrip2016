#include <Adafruit_NeoPixel.h>

#define PIN 6 // the Data Pin for the strip.
#define NUMPIXELS 300 // how many pixels are on the strip

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int incoming;
boolean isBouncing = false;
boolean isFading = false;
boolean isCarnival = false;
boolean redAlliance = true;


void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  Serial.begin(115200);

}

void loop() {
  if (Serial.available() > 0) {
    incoming = Serial.read(); // reads the next thing sent on the serial line.
    if (incoming == 'f') {
      Serial.println ("Auto Enabled!");
     isFading = true;
     isCarnival = false;
     isBouncing = false;
    }
    if (incoming == 'b') {
      Serial.println ("Auto Enabled!");
      isBouncing = true;
      isCarnival = false;
      isFading = false;
    }
    if (incoming == 'c') {
      Serial.println ("Auto Enabled!");
      isCarnival = true;
      isFading = false;
      isBouncing = false;
    }
          if (incoming == 'r') {
      Serial.println ("Auto Enabled!");
     redAlliance = true;
    }
    if (incoming == 'n') {
      Serial.println ("Auto Enabled!");
      redAlliance = false;
    }
  }

  if (isBouncing){
      if (!redAlliance){
        bounce(0,0,156,5);
    }
     if (redAlliance){
        bounce(156,0,0,5);
    }
  }
  if (isFading){
    if (!redAlliance){
     fade(0,0,156,10);
    }
     if (redAlliance){
        fade(156,0,0,10);
    }
  }
  if (isCarnival){
    if (!redAlliance){
     carnival(0,0,156,55);
    }
       if (redAlliance){
        carnival(156,0,0,55);
    }
  }
}
void fade(int r,int g,int b, int wait){
  for(int q = 1; q <= 64; q += 1){
  for(int i = 0; i < strip1.numPixels(); i+=1){
    strip1.setPixelColor(i, strip1.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip1.show();
  delay(wait);
  }
  for(int q = 63; q >= 0; q -= 1){
  for(int i = 0; i < strip1.numPixels(); i+=1){
    strip1.setPixelColor(i, strip1.Color((q*r)/50,(q*g)/50,(q*b)/50));
    
  }
  strip1.show();
  delay(wait);
  }
}
void bounce(int r, int g, int b, int wait){
  for (int i = 299; i > 0; i = i -1){
    strip1.setPixelColor(i,strip1.Color(r,g,b));
    strip1.show();
    delay(wait);
    strip1.setPixelColor(i,strip1.Color(0,0,0));

  }

  for (int i = 0; i < 299; i = i +1){
     strip1.setPixelColor(i,strip1.Color(r,g,b));
    strip1.show();
    delay(wait);
    strip1.setPixelColor(i,strip1.Color(0,0,0));
    }
  }
void carnival(int r,int g,int b, int wait){
   for(int c = 0; c < 3; c++){ 
  for(int i = 0; i < strip1.numPixels(); i+=3){
    strip1.setPixelColor(i+c, strip1.Color(r,g,b));
    strip1.setPixelColor(i+c-1, strip1.Color(0,0,0));
    
  }
  strip1.show();
    delay(wait);
  }
}

