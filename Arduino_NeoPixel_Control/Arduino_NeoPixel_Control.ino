/*
  Arduino Neopixel Control 1.0
  Created by Christian Marotta
*/

#include <FastLED.h>//Used for Neopixel

#define NUM_LEDS 25//Number of LEDS on the strip
#define DATA_PIN 2//Data pin for the strip, remember to attach a 100 ohm resistor between the pin and the input of the first led

#define CMD_LENGTH 32//This is the max length of the command, change it if a bigger command string is needed
#define CMD_START '['//Start point of the command, can be customized, but still use brackets
#define CMD_END ']'//End point of the command

char cmd[CMD_LENGTH];//Original command string
char cmdCopy[CMD_LENGTH];//Copy of the command, only used with "setRgb" command
char *cmdTemp;
bool newData = false;//Used to indicate if there's new data or not
bool isReceiving = false;//Turned true if the first char isn the CMD_START character
byte R = 0, G = 0, B = 0;
byte pixel = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);//GRB because the leds are inverted on the strip, could be different on yours
  randomSeed(analogRead(0));//We use the background noise on an unused pin to generate random numbers
  Serial.begin(9600);
  Serial.println("Ready to receive!");
}

void loop() {
  getData();//Stores a char string in cmd
  showData();//Shows the command entered
  vfx(cmdTemp);//Based on the command chooses an effect
}

//Input control from python script
void getData() {
  static byte nc = 0;
  char rc;
  while (Serial.available() > 0 and newData == false) {//If there're bytes coming in and newData is false we read from Serial
    rc = Serial.read();
    if (isReceiving == true) {//isReceiving is true only if the first char is the CMD_START character
      if (rc != CMD_END) {
        cmd[nc++] = rc;//If the char incoming isn't the CMD_END character, then it's stored in the cmd array
        if (nc >= CMD_LENGTH) {
          nc = CMD_LENGTH - 1;
        }
      } else {
        newData = true;//If the char incoming is the CMD_END character, the last char is set to '\0' and the receiving is stopped
        isReceiving = false;
        cmd[nc] = '\0';
        nc = 0;
      }
    } else if (rc == CMD_START) {//If the incoming char is the CMD_START character, start receiving
      isReceiving = true;
    }
  }
}

void showData() {
  if (newData == true) {
    Serial.println("Command entered:");//Outputs the command on Serial
    Serial.println(cmd);
    Serial.println("--------");
    strcpy(cmdCopy, cmd);//A copy of the cmd is created
    cmdTemp = strtok(cmd, ",");//The command itself gets extracted in cmdTemp from the original cmd, that gets inevitable trimmed. For this reason the cmdCopy
    newData = false;
  }
}

//Switch vfx, based on the command passed
void vfx(char *s) {
  if (String(s).equals("red")) {
    red();
    cmdTemp = "";//Only used in static effects, prevents entering again in the if
  } else if (String(s).equals("green")) {
    green();
    cmdTemp = "";
  } else if (String(s).equals("blue")) {
    blue();
    cmdTemp = "";
  } else if (String(s).equals("white")) {
    white();
    cmdTemp = "";
  } else if (String(s).equals("neonPurple")) {
    neonPurple();
    cmdTemp = "";
  } else if (String(s).equals("rgbLoop")) {
    rgbLoop();
  } else if (String(s).equals("strobe")) {
    strobe(random(255), random(255), random(255), 10, 50, 500);
  } else if (String(s).equals("sparkle")) {
    sparkle(random(255), random(255), random(255), 20);
  } else if (String(s).equals("rainbowCycle")) {
    rainbowCycle(10);
  } else if (String(s).equals("twinkleRandom")) {
    twinkleRandom(NUM_LEDS, 50, false);
  } else if (String(s).equals("theaterChaseRainbow")) {
    theaterChaseRainbow(250);
  } else if (String(s).equals("meteorRain")) {
    meteorRain(random(255), random(255), random(255), 5, 64, true, 50);
  } else if (String(s).equals("setRgb")) {
    setRgb();
    cmdTemp = "";//Really important, it would show the color for a fraction of a second
  } else if ( String(s).equals("setPixel")) {
    setPixel();
  } else if (String(s).equals("turnOff")) {
    turnOff();
  }
}

//Trims the command, obtaining 3 RGB values
void getRgbValues() {
  char *values;
  if (String(cmdTemp).equals("setPixel")) {//If cmdTemp equals to "setPixel" then it gets another valus, which is the led position
    values = strtok(cmdCopy, ",");
    values = strtok(NULL, ",");
    pixel = atoi(values);
    values = strtok(NULL, ",");
    R = atoi(values);
    values = strtok(NULL, ",");
    G = atoi(values);
    values = strtok(NULL, ",");
    B = atoi(values);
  } else {
    values = strtok(cmdCopy, ",");
    values = strtok(NULL, ",");
    R = atoi(values);
    values = strtok(NULL, ",");
    G = atoi(values);
    values = strtok(NULL, ",");
    B = atoi(values);
  }

}

//Animations
//Sets a custom RGB color
void setRgb() {
  getRgbValues();
  fill_solid(leds, NUM_LEDS, CRGB(R, G, B));
  showStrip();
  delay(100);
}

//Sets a specific led to a RGB color
void setPixel() {
  getRgbValues();
  leds[pixel].setRGB(R, G, B);
  showStrip();
  delay(100);
}

//Sets red at full brightness
void red() {
  fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
  showStrip();
  delay(100);
}

//Sets green at full brightness
void green() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 255, 0));
  showStrip();
  delay(100);
}

//Sets blue at full brightness
void blue() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 255));
  showStrip();
  delay(100);
}

//Sets white at full brightness
void white() {
  fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
  showStrip();
  delay(100);
}

void neonPurple() {
  fill_solid(leds, NUM_LEDS, CRGB(117, 0, 215));
  showStrip();
  delay(100);
}

void rgbLoop() {
  for (int j = 0; j < 3; j++ ) {
    // Fade IN
    for (int k = 0; k < 256; k++) {
      switch (j) {
        case 0: setAll(k, 0, 0); break;
        case 1: setAll(0, k, 0); break;
        case 2: setAll(0, 0, k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for (int k = 255; k >= 0; k--) {
      switch (j) {
        case 0: setAll(k, 0, 0); break;
        case 1: setAll(0, k, 0); break;
        case 2: setAll(0, 0, k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAll(red, green, blue);
    showStrip();
    delay(FlashDelay);
    setAll(0, 0, 0);
    showStrip();
    delay(FlashDelay);
  }

  delay(EndPause);
}

void sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel, red, green, blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel, 0, 0, 0);
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

void twinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
    showStrip();
    delay(SpeedDelay);
    if (OnlyOne) {
      setAll(0, 0, 0);
    }
  }

  delay(SpeedDelay);
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        c = Wheel( (i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2)); //turn every third pixel on
      }
      showStrip();

      delay(SpeedDelay);

      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
  setAll(0, 0, 0);

  for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++) {


    // fade brightness all LEDs one step
    for (int j = 0; j < NUM_LEDS; j++) {
      if ( (!meteorRandomDecay) || (random(10) > 5) ) {
        fadeToBlack(j, meteorTrailDecay );
      }
    }

    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
      if ( ( i - j < NUM_LEDS) && (i - j >= 0) ) {
        setPixel(i - j, red, green, blue);
      }
    }

    showStrip();
    delay(SpeedDelay);
  }
}

//Animations functions
void showStrip() {
  FastLED.show();
}

void turnOff() {
  FastLED.clear();//All leds off
  showStrip();
  delay(100);
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void fadeToBlack(int ledNo, byte fadeValue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  uint32_t oldColor;
  uint8_t r, g, b;
  int value;

  oldColor = strip.getPixelColor(ledNo);
  r = (oldColor & 0x00ff0000UL) >> 16;
  g = (oldColor & 0x0000ff00UL) >> 8;
  b = (oldColor & 0x000000ffUL);

  r = (r <= 10) ? 0 : (int) r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int) g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int) b - (b * fadeValue / 256);

  strip.setPixelColor(ledNo, r, g, b);
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[ledNo].fadeToBlackBy( fadeValue );
#endif
}
