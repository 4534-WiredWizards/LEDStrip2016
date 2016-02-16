#include <Adafruit_NeoPixel.h>

#define PIN 6 // the Data Pin for the strip.
#define NUMPIXELS 300 // how many pixels are on the strip

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int incoming;
boolean isBouncing = false;
boolean isFading = false;
boolean isCarnival = false;
boolean isSolid = false;
boolean isRipple = false;
boolean isBlink = false;
boolean isEaster = false;

boolean redAlliance = true;
//int whichAnimation = 0; //Determines which animation will run


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
     isSolid = false;
     isBlink = false;
     isEaster = false;
     isRipple = false;
    }
    if (incoming == 'b') {
      Serial.println ("Auto Enabled!");
      isBouncing = true;
      isCarnival = false;
      isFading = false;
      isSolid = false;
      isBlink = false;
      isEaster = false;
      isRipple = false;
    }
    if (incoming == 'i') {
      Serial.println ("Auto Enabled!");
      isBouncing = false;
      isCarnival = false;
      isFading = false;
      isSolid = false;
      isBlink = false;
      isEaster = false;
      isRipple = true;
    }
    if (incoming == 'e') {
      Serial.println ("Auto Enabled!");
      isBouncing = false;
      isCarnival = false;
      isFading = false;
      isSolid = false;
      isBlink = false;
      isEaster = true;
      isRipple = false;
    }
    if (incoming == 'l') {
      Serial.println ("Auto Enabled!");
      isBouncing = false;
      isCarnival = false;
      isFading = false;
      isSolid = false;
      isBlink = true;
      isEaster = false;
      isRipple = false;
    }
    if (incoming == 's') {
      Serial.println ("Auto Enabled!");
      isBouncing = false;
      isCarnival = false;
      isFading = false;
      isSolid = true;
      isBlink = false;
      isEaster = false;
      isRipple = false;
    }
    if (incoming == 'c') {
      Serial.println ("Auto Enabled!");
      isCarnival = true;
      isFading = false;
      isBouncing = false;
      isSolid = false;
     isBlink = false;
     isEaster = false;
     isRipple = false;
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
  if (isSolid){
    if (!redAlliance){
     solidColor(0,0,156);
    }
       if (redAlliance){
        solidColor(156,0,0);
    }
  }
  if (isBlink){
    if (!redAlliance){
     blink(0,0,156,500);
    }
    if (redAlliance){
     blink(156,0,0,500);
    }
  }
  if (isEaster){
    if (!redAlliance){
     easter(0,0,156);
    }
       if (redAlliance){
        easter(156,0,0);
    }
  }
  if (isRipple){
    if (!redAlliance){
     ripple(0,0,156,8,30);
    }
       if (redAlliance){
        ripple(156,0,0,8,30);
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

