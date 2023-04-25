
//photoresistor
int photoPin = A0;
int photoReading = 0;
int brightness = 255;

//touch sensor
#include <CapacitiveSensor.h>

//neopixels
#include <Adafruit_NeoPixel.h>
//leds
Adafruit_NeoPixel strip(112, 10);
//touch sensor
CapacitiveSensor touch(2, 4);

//button
int buttonPin = 6;
//finite state
int patternState = 0;
boolean currentState = false;
boolean prevState = false;
//button reading
boolean buttonReading = false;
boolean lastButtonReading = false;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.clear();
  pinMode(buttonPin, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  power(buttonPin);
  touchSensor();

  photoReading = analogRead(photoPin);
  Serial.println(photoReading);
  brightness = map(photoReading, 200, 900, 0, 100);
  strip.setBrightness(brightness);
  strip.show();
}


void touchSensor() {
  int feel = touch.capacitiveSensor(30);
  static int state = 0;

  if (feel > 500) {
  //  Serial.println(feel);
    state++;

    if (state > 6) {
      state = 0;
    }
    delay(500);
  }

  switch (state) {
    case 0:
      setBlueSolid(strip.Color(83, 171, 238));
      //Serial.println("case 0");
      break;
    case 1:
      setLightBlueSolid(strip.Color(99, 203, 251));
      Serial.println("case 1");
      break;
    case 2:
      setGreenSolid(strip.Color(27, 111, 32));
      Serial.println("case 2");
      break;
    case 3:
      setLightGreenSolid(strip.Color(108, 172, 108));
      Serial.println("case 3");
      break;
    case 4:
      setGreySolid(strip.Color(211, 223, 230));
      Serial.println("case 4");
      break;
    case 5:
      setTealSolid(strip.Color(49, 103, 89));
      Serial.println("case 5");
      break;
    case 6:
      rainbowTimer();
      Serial.println("case 6");
      break;
  }
}

void power(int aButtonPin) {
  static boolean on = false;
  static boolean aState = false;
  static boolean aPrevState = false;

  aPrevState = aState;

  aState = debounce(aButtonPin, aPrevState);

  Serial.println(on);

  if (aState == true && aPrevState == false ) {
    on = !on;
  }

  if (on == true) {
    strip.show();
    strip.setBrightness(255);
  }
  if (on == false) {
    strip.clear();
    strip.show();
    strip.setBrightness(0);
  }

}

void setBlueSolid(uint32_t aColor) {
  for (int index = 0; index < strip.numPixels(); index++) {
    strip.setPixelColor(index, aColor);
  }
  strip.show();
}

void setLightBlueSolid(uint32_t aColor) {
  for (int index = 0; index < strip.numPixels(); index++) {
    strip.setPixelColor(index, aColor);
  }
  strip.show();
}

void setGreenSolid(uint32_t aColor) {
  for (int index = 0; index < strip.numPixels(); index++) {
    strip.setPixelColor(index, aColor);
  }
  strip.show();
}

void setLightGreenSolid(uint32_t aColor) {
  for (int index = 0; index < strip.numPixels(); index++) {
    strip.setPixelColor(index, aColor);
  }
  strip.show();
}

void setGreySolid(uint32_t aColor) {
  for (int index = 0; index < strip.numPixels(); index++) {
    strip.setPixelColor(index, aColor);
  }
  strip.show();
}

void setTealSolid(uint32_t aColor) {
  for (int index = 0; index < strip.numPixels(); index++) {
    strip.setPixelColor(index, aColor);
  }
  strip.show();
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void rainbowTimer() { // modified from Adafruit example to make it a state machine
  static unsigned long startTime = millis();
  int interval = 20;
  static uint16_t j = 0;


  if (millis() - startTime >= interval) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    j++;
    if (j >= 256) j = 0;
    startTime = millis(); // time for next change to the display
  }
}


//button debounce
boolean debounce(int aButtonPin, boolean aLastReading) {
  // get current reading of the button
  boolean currentReading = digitalRead(aButtonPin);

  // compare the current reading to the previous reading
  if (currentReading == true && aLastReading == false) {
    delay(20);
  }

  // return the reading
  return currentReading;
}
