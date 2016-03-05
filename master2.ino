 #include <Adafruit_NeoPixel.h>

#define PIN1 6 // the Data Pin for the strip.
#define PIN2 5 // the Data Pin for the strip.
#define PIN3 3 // the Data Pin for the strip.
#define NUMPIXELS 67 // how many pixels are on the strip

Adafruit_NeoPixel strip3 =  Adafruit_NeoPixel(17, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 =  Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 =  Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);

int incoming;

int animationID = 6;
int red = 0;
int green = 32;
int blue = 0;
unsigned long lastTick = 0;
unsigned long timeSince = 0;

boolean willReset = true;

boolean redAlliance = true;
boolean endGame = false;



void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  Serial.begin(115200);

}

void loop() {
  lastTick = micros();
  redo:
  if (Serial.available() > 0) {
    timeSince = millis();
    incoming = Serial.read(); // reads the next thing sent on the serial line.
    switch (incoming) {
      case 'f':
        Serial.println ("Fade");
        animationID = 1;
        willReset = false;
        solidColor(0,0,0);
        break;
      case '~':
        Serial.println ("Alive");
        //keeps the lights awake. Leave blank unless you've got something to do nearly every active frame.
        goto redo;
        break;
      case 'b':
        Serial.println ("Bounce");
        animationID = 2;
        willReset = true;
        solidColor(0,0,0);
        break;
      case 'i':
        Serial.println ("Teleop");
        animationID = 3;
        willReset = true;
        solidColor(0,0,0);
        break;
      case 'e':
        Serial.println ("Easter");
        animationID = 4;
        willReset = true;
        solidColor(0,0,0);
        break;
      case 'l':
        Serial.println ("Intake Running");
        animationID = 5;
        willReset = true;
        solidColor(0,64,0);
        break;
      case 's':
        Serial.println ("Shoot");
        animationID = 6;
        break;
      case 'c':
        Serial.println ("Autonomous");
        animationID = 7;
        willReset = true;
        solidColor(0,0,0);
        break;
      case 'n':
        Serial.println ("Blue");
        red = 0;
        green = 0;
        blue = 64;
        break;
      case 'r':
        Serial.println ("Red");
        red = 64;
        green = 0;
        blue = 0;
        break; 
      case 'v':
        Serial.println ("Violet");
        red = 30;
        green = 0;
        blue = 54;
        break;
      case 'g':
      Serial.println ("Green");
        red = 0;
        green = 64;
        blue = 0;
        break;
      case 't':
      Serial.println ("Teal");
        red = 0;
        green = 84;
        blue = 44;
        break;
      case 'z':
        Serial.println ("Final 20 Seconds");
        red = 64;
        green = 48;
        blue = 0;
        break;
       case 'w':
        Serial.println ("Disabled");
        animationID = 8;
        willReset = true;
        solidColor(0,0,0);
        break;
    }
  } else if (millis() - timeSince > 5000) {
    animationID = 2;
    willReset = true;
    solidColor(0,0,0);
  }

  switch (animationID){
      case 1:
        fade (red, green, blue, 10);
        fade2 (red, green, blue, 10);
        fade3 (red, green, blue, 10);
        break;
      case 2:
        bounce (red, green, blue, 5);
        bounce2 (red, green, blue, 5);
        bounce3 (red, green, blue, 5);
        break;
      case 3:
        ripple (red, green, blue, 8, 25);
        ripple2 (red, green, blue, 8, 25);
        ripple3 (red, green, blue, 8, 25);
        break;
      case 4:
        easter (red, green, blue);
        easter2 (red, green, blue);
        easter3 (red, green, blue);
        break;
      case 5:
        blink (red, green, blue, 100);
        blink2 (red, green, blue, 100);
        blink3 (red, green, blue, 100);
        break;
      case 6:
        solidColor (red, green, blue);
        solidColor2 (red, green, blue);
        solidColor3 (red, green, blue);
        break;
      case 7:
        carnival (red, green, blue, 40);
        carnival2 (red, green, blue, 40);
        carnival3 (red, green, blue, 40);
        break;
      case 8:
        rainbowBounce (red, green, blue);
        rainbowBounce2 (red, green, blue);
        rainbowBounce3 (red, green, blue);
        break;
      default:
      solidColor (16, 16, 16);
      solidColor2 (16, 16, 16);
      solidColor3 (16, 16, 16);
  }
  strip1.show();
  strip2.show();
  strip3.show();
  
  while(micros() - lastTick < 1000){
    delayMicroseconds(1);
  }
  Serial.println(micros()-lastTick);
}

void fade(int r,int g,int b, int wait){
  
for(int q = 0; q < 64; q += 1){
  for(int i = 0; i < strip1.numPixels(); i+=1){
    strip1.setPixelColor(i, strip1.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip1.show();
  delay(wait);
  }
  for(int q = 64; q > 0; q -= 1){
  for(int i = 0; i < strip1.numPixels(); i+=1){
    strip1.setPixelColor(i, strip1.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip1.show();
  delay(wait);
  }
}

void bounce(int r, int g, int b, int wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  f %= ((strip1.numPixels() * 2) - 2);

  if (f <= strip1.numPixels()) {
    strip1.setPixelColor(f,strip1.Color(r,g,b));
    strip1.setPixelColor(f - 1,strip1.Color(0,0,0));
  }

  if (f > strip1.numPixels()){
    strip1.setPixelColor((strip1.numPixels() * 2) - f, strip1.Color(r,g,b));
    strip1.setPixelColor((strip1.numPixels() * 2) - f + 1, strip1.Color(0,0,0));
  }
  
}
  
void carnival(int r,int g,int b, int wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  int c = f % 3;
  for(int i = 0; i < strip1.numPixels()+1; i+=3){
    strip1.setPixelColor(i+c, strip1.Color(r,g,b));
    strip1.setPixelColor(i+c-1, strip1.Color(0,0,0));
  }
  
}

void solidColor(int r, int g, int b){
   for(int i = 0; i < strip1.numPixels(); i++){
    strip1.setPixelColor(i, strip1.Color(r,g,b));
  }
  strip1.show();
}

void blink(int r, int g, int b, int wait) {
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  if (f % 2) {
  solidColor(0,0,0);
  } else {
  solidColor(r,g,b);
  }
  if (f >= 2) {
    willReset = true;
  }
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
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  
  int s = (f % (magnitude * 2)) - (magnitude * 2);
  
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
}
void rainbowBounce(int r, int g, int b) {
    /*
    if (Serial.available() > 0) {
      incoming = Serial.read(); // reads the next thing sent on the serial line.
      if (incoming == 'a') {
        Serial.println ("Auto Enabled!");
      }
    }
  */ 
  
  for (int i = strip1.numPixels(); i > 0; i = i -1){
    strip1.setPixelColor(i,strip1.Color(255,0,0));
    strip1.setPixelColor(i + 1, strip1.Color(255,0,0));
    strip1.setPixelColor(i + 2, strip1.Color(255,0,0));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i + 3,strip1.Color(0,0,0));

   //red
  }

  for (int i = 0; i < strip1.numPixels(); i = i +1){
    strip1.setPixelColor(i,strip1.Color(255,65,0));
    strip1.setPixelColor(i - 1, strip1.Color(255,65,0));
    strip1.setPixelColor(i - 2, strip1.Color(255,65,0));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i - 3,strip1.Color(0,0,0));

    //orange
  }

  
  for (int i = strip1.numPixels(); i > 0; i = i -1){
    strip1.setPixelColor(i,strip1.Color(255,130,0));
    strip1.setPixelColor(i + 1, strip1.Color(255,130,0));
    strip1.setPixelColor(i + 2, strip1.Color(255,130,0));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i + 3,strip1.Color(0,0,0));

    //yellow
  }

 for (int i = 0; i < strip1.numPixels(); i = i +1){
    strip1.setPixelColor(i,strip1.Color(0,255,0));
    strip1.setPixelColor(i - 1, strip1.Color(0,255,0));
    strip1.setPixelColor(i - 2, strip1.Color(0,255,0));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i - 3,strip1.Color(0,0,0));

    //green
  }
for (int i = strip1.numPixels(); i > 0; i = i -1){
    strip1.setPixelColor(i,strip1.Color(0,0,230));
    strip1.setPixelColor(i + 1, strip1.Color(0,0,230));
    strip1.setPixelColor(i + 2, strip1.Color(0,0,230));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i + 3,strip1.Color(0,0,0));

    //blue
  }
   for (int i = 0; i < strip1.numPixels(); i = i +1){
    strip1.setPixelColor(i,strip1.Color(255,0,255));
    strip1.setPixelColor(i - 1, strip1.Color(255,0,255));
    strip1.setPixelColor(i - 2, strip1.Color(255,0,255));
    strip1.show();
    delay(5);
    strip1.setPixelColor(i - 3,strip1.Color(0,0,0));

    //violet
  }
}
void fade2(int r,int g,int b, int wait){
  
for(int q = 0; q < 64; q += 1){
  for(int i = 0; i < strip2.numPixels(); i+=1){
    strip2.setPixelColor(i, strip2.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip2.show();
  delay(wait);
  }
  for(int q = 64; q > 0; q -= 1){
  for(int i = 0; i < strip2.numPixels(); i+=1){
    strip2.setPixelColor(i, strip2.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip2.show();
  delay(wait);
  }
}

void bounce2(int r, int g, int b, int wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  f %= ((strip2.numPixels() * 2) - 2);

  if (f <= strip2.numPixels()) {
    strip2.setPixelColor(f,strip2.Color(r,g,b));
    strip2.setPixelColor(f - 1,strip2.Color(0,0,0));
  }

  if (f > strip2.numPixels()){
    strip2.setPixelColor((strip2.numPixels() * 2) - f, strip2.Color(r,g,b));
    strip2.setPixelColor((strip2.numPixels() * 2) - f + 1, strip2.Color(0,0,0));
  }
}
  
void carnival2(int r,int g,int b, int wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  int c = f % 3;
  for(int i = 0; i < strip2.numPixels()+1; i+=3){
    strip2.setPixelColor(i+c, strip2.Color(r,g,b));
    strip2.setPixelColor(i+c-1, strip2.Color(0,0,0));
  }
  
}

void solidColor2(int r, int g, int b){
   for(int i = 0; i < strip2.numPixels(); i++){
    strip2.setPixelColor(i, strip2.Color(r,g,b));
  }
  strip2.show();
}

void blink2(int r, int g, int b, int wait) {
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  if (f % 2) {
  solidColor(0,0,0);
  } else {
  solidColor(r,g,b);
  }
  if (f >= 2) {
    willReset = true;
  }
}

void easter2(int r,int g,int b){
    int num = 0;
  
  for(int i = strip2.numPixels(); i > 0; i--){
    int R = random(r);
    int G = random(g);
    int B = random(b);
    for(int r = num + 1; r <= i; r++){
      strip2.setPixelColor(r, strip2.Color(R,G,B));
      strip2.show();
      delayMicroseconds(10);
      strip2.setPixelColor(r, strip2.Color(0,0,0));
      }
    strip2.setPixelColor(i, strip2.Color(R,G,B));

     for(int k = i - 1; k >= num; k--){
        strip2.setPixelColor(k, strip2.Color(R,G,B));
        strip2.show();
        delayMicroseconds(10);
        strip2.setPixelColor(k, strip2.Color(0,0,0));
      }
   
   strip2.setPixelColor(num, strip2.Color(R,G,B));
   num++;
   
  }
  strip2.show();
}

void ripple2(int r, int g, int b, byte magnitude, byte wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  
  int s = (f % (magnitude * 2)) - (magnitude * 2);
  
    for (int p = 0; p < strip2.numPixels() + (2 * magnitude); p += (2*magnitude)) {
      for (int i = 0; i < magnitude; i++){
        if ((p+i-s) >= 0 && p+i-s < strip2.numPixels()){
          strip2.setPixelColor(p+i-s, strip2.Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
        }
      }
      for (int i = magnitude; i > 0; i--) {
        if ((p-s+((magnitude * 2) - i)) >= 0 && (p-s+((magnitude * 2) - i)) < strip2.numPixels()){
          strip2.setPixelColor((p-s+((magnitude * 2) - i)), strip2.Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
        }
      }
    }
}
void rainbowBounce2(int r, int g, int b) {
    /*
    if (Serial.available() > 0) {
      incoming = Serial.read(); // reads the next thing sent on the serial line.
      if (incoming == 'a') {
        Serial.println ("Auto Enabled!");
      }
    }
  */ 
  
  for (int i = strip2.numPixels(); i > 0; i = i -1){
    strip2.setPixelColor(i,strip2.Color(255,0,0));
    strip2.setPixelColor(i + 1, strip2.Color(255,0,0));
    strip2.setPixelColor(i + 2, strip2.Color(255,0,0));
    strip2.show();
    delay(5);
    strip2.setPixelColor(i + 3,strip2.Color(0,0,0));

   //red
  }

  for (int i = 0; i < strip2.numPixels(); i = i +1){
    strip2.setPixelColor(i,strip2.Color(255,65,0));
    strip2.setPixelColor(i - 1, strip2.Color(255,65,0));
    strip2.setPixelColor(i - 2, strip2.Color(255,65,0));
    strip2.show();
    delay(5);
    strip2.setPixelColor(i - 3,strip2.Color(0,0,0));

    //orange
  }

  
  for (int i = strip2.numPixels(); i > 0; i = i -1){
    strip2.setPixelColor(i,strip2.Color(255,130,0));
    strip2.setPixelColor(i + 1, strip2.Color(255,130,0));
    strip2.setPixelColor(i + 2, strip2.Color(255,130,0));
    strip2.show();
    delay(5);
    strip2.setPixelColor(i + 3,strip2.Color(0,0,0));

    //yellow
  }

 for (int i = 0; i < strip2.numPixels(); i = i +1){
    strip2.setPixelColor(i,strip2.Color(0,255,0));
    strip2.setPixelColor(i - 1, strip2.Color(0,255,0));
    strip2.setPixelColor(i - 2, strip2.Color(0,255,0));
    strip2.show();
    delay(5);
    strip2.setPixelColor(i - 3,strip2.Color(0,0,0));

    //green
  }
for (int i = strip2.numPixels(); i > 0; i = i -1){
    strip2.setPixelColor(i,strip2.Color(0,0,230));
    strip2.setPixelColor(i + 1, strip2.Color(0,0,230));
    strip2.setPixelColor(i + 2, strip2.Color(0,0,230));
    strip2.show();
    delay(5);
    strip2.setPixelColor(i + 3,strip2.Color(0,0,0));

    //blue
  }
   for (int i = 0; i < strip2.numPixels(); i = i +1){
    strip2.setPixelColor(i,strip2.Color(255,0,255));
    strip2.setPixelColor(i - 1, strip2.Color(255,0,255));
    strip2.setPixelColor(i - 2, strip2.Color(255,0,255));
    strip2.show();
    delay(5);
    strip2.setPixelColor(i - 3,strip2.Color(0,0,0));

    //violet
  }
}
void fade3(int r,int g,int b, int wait){
  
for(int q = 0; q < 64; q += 1){
  for(int i = 0; i < strip2.numPixels(); i+=1){
    strip3.setPixelColor(i, strip3.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip3.show();
  delay(wait);
  }
  for(int q = 64; q > 0; q -= 1){
  for(int i = 0; i < strip3.numPixels(); i+=1){
    strip3.setPixelColor(i, strip3.Color((q*r)/50,(q*g)/50,(q*b)/50));
  }
  strip3.show();
  delay(wait);
  }
}

void bounce3(int r, int g, int b, int wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  static int previous = 0;
  unsigned int f = (millis()-timer)/wait;
  f %= ((strip3.numPixels() * 2) - 2);

  if (f <= strip3.numPixels()) {
    strip3.setPixelColor(f,strip3.Color(r,g,b));
    strip3.setPixelColor(previous, strip3.Color(0,0,0));
    previous = f;
  }

  if (f > strip3.numPixels()){
    strip3.setPixelColor((strip3.numPixels() * 2) - f, strip3.Color(r,g,b));
    strip3.setPixelColor(previous, strip3.Color(0,0,0));
    previous = (strip3.numPixels() * 2) - f + 1;
  }
}
  
void carnival3(int r,int g,int b, int wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  int c = f % 3;
  for(int i = 0; i < strip3.numPixels()+1; i+=3){
    strip3.setPixelColor(i+c, strip3.Color(r,g,b));
    strip3.setPixelColor(i+c-1, strip3.Color(0,0,0));
  }
  
}

void solidColor3(int r, int g, int b){
   for(int i = 0; i < strip3.numPixels(); i++){
    strip3.setPixelColor(i, strip3.Color(r,g,b));
  }
  strip3.show();
}

void blink3(int r, int g, int b, int wait) {
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  if (f % 2) {
  solidColor(0,0,0);
  } else {
  solidColor(r,g,b);
  }
  if (f >= 2) {
    willReset = true;
  }
}

void easter3(int r,int g,int b){
    int num = 0;
  
  for(int i = strip3.numPixels(); i > 0; i--){
    int R = random(r);
    int G = random(g);
    int B = random(b);
    for(int r = num + 1; r <= i; r++){
      strip3.setPixelColor(r, strip3.Color(R,G,B));
      strip3.show();
      delayMicroseconds(10);
      strip3.setPixelColor(r, strip3.Color(0,0,0));
      }
    strip3.setPixelColor(i, strip3.Color(R,G,B));

     for(int k = i - 1; k >= num; k--){
        strip3.setPixelColor(k, strip3.Color(R,G,B));
        strip3.show();
        delayMicroseconds(10);
        strip3.setPixelColor(k, strip3.Color(0,0,0));
      }
   
   strip3.setPixelColor(num, strip3.Color(R,G,B));
   num++;
   
  }
  strip3.show();
}

void ripple3(int r, int g, int b, byte magnitude, byte wait){
  static unsigned long timer = millis();
  if(willReset){
    timer = millis();
    willReset = false;
  }
  unsigned int f = (millis()-timer)/wait;
  
  int s = (f % (magnitude * 2)) - (magnitude * 2);
  
    for (int p = 0; p < strip3.numPixels() + (2 * magnitude); p += (2*magnitude)) {
      for (int i = 0; i < magnitude; i++){
        if ((p+i-s) >= 0 && p+i-s < strip3.numPixels()){
          strip3.setPixelColor(p+i-s, strip3.Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
        }
      }
      for (int i = magnitude; i > 0; i--) {
        if ((p-s+((magnitude * 2) - i)) >= 0 && (p-s+((magnitude * 2) - i)) < strip3.numPixels()){
          strip3.setPixelColor((p-s+((magnitude * 2) - i)), strip3.Color((i*r)/magnitude, (i*g)/magnitude, (i*b)/magnitude));
        }
      }
    }
}
void rainbowBounce3(int r, int g, int b) {
    /*
    if (Serial.available() > 0) {
      incoming = Serial.read(); // reads the next thing sent on the serial line.
      if (incoming == 'a') {
        Serial.println ("Auto Enabled!");
      }
    }
  */ 
  
  for (int i = strip3.numPixels(); i > 0; i = i -1){
    strip3.setPixelColor(i,strip3.Color(255,0,0));
    strip3.setPixelColor(i + 1, strip3.Color(255,0,0));
    strip3.setPixelColor(i + 2, strip3.Color(255,0,0));
    strip3.show();
    delay(5);
    strip3.setPixelColor(i + 3,strip3.Color(0,0,0));

   //red
  }

  for (int i = 0; i < strip3.numPixels(); i = i +1){
    strip3.setPixelColor(i,strip3.Color(255,65,0));
    strip3.setPixelColor(i - 1, strip3.Color(255,65,0));
    strip3.setPixelColor(i - 2, strip3.Color(255,65,0));
    strip3.show();
    delay(5);
    strip3.setPixelColor(i - 3,strip3.Color(0,0,0));

    //orange
  }

  
  for (int i = strip3.numPixels(); i > 0; i = i -1){
    strip3.setPixelColor(i,strip3.Color(255,130,0));
    strip3.setPixelColor(i + 1, strip3.Color(255,130,0));
    strip3.setPixelColor(i + 2, strip3.Color(255,130,0));
    strip3.show();
    delay(5);
    strip3.setPixelColor(i + 3,strip3.Color(0,0,0));

    //yellow
  }

 for (int i = 0; i < strip3.numPixels(); i = i +1){
    strip3.setPixelColor(i,strip3.Color(0,255,0));
    strip3.setPixelColor(i - 1, strip3.Color(0,255,0));
    strip3.setPixelColor(i - 2, strip3.Color(0,255,0));
    strip3.show();
    delay(5);
    strip3.setPixelColor(i - 3,strip3.Color(0,0,0));

    //green
  }
for (int i = strip3.numPixels(); i > 0; i = i -1){
    strip3.setPixelColor(i,strip3.Color(0,0,230));
    strip3.setPixelColor(i + 1, strip3.Color(0,0,230));
    strip3.setPixelColor(i + 2, strip3.Color(0,0,230));
    strip3.show();
    delay(5);
    strip3.setPixelColor(i + 3,strip3.Color(0,0,0));

    //blue
  }
   for (int i = 0; i < strip3.numPixels(); i = i +1){
    strip3.setPixelColor(i,strip3.Color(255,0,255));
    strip3.setPixelColor(i - 1, strip3.Color(255,0,255));
    strip3.setPixelColor(i - 2, strip3.Color(255,0,255));
    strip3.show();
    delay(5);
    strip3.setPixelColor(i - 3,strip3.Color(0,0,0));

    //violet
  }
}

