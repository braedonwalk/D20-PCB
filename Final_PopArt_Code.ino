#include <Bounce2.h>

#include <Adafruit_NeoPixel.h>

//Button
Bounce b = Bounce();
int buttonPin = 1;

//NeoPixel
int npPixelCount = 30;
int pixelPin = 0;
int brightness = 200;
Adafruit_NeoPixel strip(npPixelCount, pixelPin, NEO_GRB + NEO_KHZ800);  //set up neopixel strip

//State Machine
int mode = 0; //controls visual mode of PCB

//SETUP
void setup() {
  b.attach(buttonPin, INPUT);  //set up button
  b.interval(25);              //set debounce interval

  initNeopixels();             //initialize neopixels

  randomSeed(analogRead(0));  //set random seed (true random)
}

//LOOP
void loop() {
  b.update(); //update buttons
  changeState();  //update state on button press
  //FINITE STATE MACHINE
  switch (mode) {
    case 0: offMode(); break;
    case 1: lightning(); break;
    case 2: fireBall(); break;
  }
  strip.show();
}

//INITIALIZE NEOPIXELS
void initNeopixels() {
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(brightness);
}

//BUTTON CHANGE STATE
void changeState() {
  if (b.rose()) {
    mode++;
    if(mode>2){
      mode = 0;
    }
  }
}
