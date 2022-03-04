//MODES

int numGrid = 30;   //the number of LEDs on the grid
int numFrames = 3;  //change depending on number of animation frames

char index[30] {
  // Insert Index Values Here
          0,
        1,  2,
  3,  4,  5,  6,  7,
    8,  9,  10, 11,
  12, 13, 14, 15, 16,
    17, 18, 19, 20,
  21, 22, 23, 24, 25,
    26, 27, 28, 29,
};

char colors[5][3] {   //colors[number of colors][keep at 3:(R,G,B)]
  // Create 3 Colors Here
  {255, 0, 0}, //0 - RED
  {255, 50, 0}, //1 - RED ORANGE
  {255, 120, 0}, //2 - ORANGE
  {240, 240, 240}, //3 - WHITE
  {0, 0, 0}, //4 - Nothing
};

char frames[3][30] {
  // Create 3 Animation Frames Here
  {       4,
        4,  4,
  4,  4,  4,  4,  4,
    4,  0,  0,  4,
  4,  4,  1,  4,  4,
    4,  0,  0,  4,
  4,  4,  4,  4,  4,
    4,  4,  4,  4,
  },
  {       4,
        4,  4,
  4,  0,  1,  0,  4,
    0,  1,  1,  0,
  4,  1,  2,  1,  4,
    0,  1,  1,  0,
  4,  0,  1,  0,  4,
    4,  4,  4,  4
  },
  {       1,
        1,  1,
  0,  1,  2,  1,  0,
    1,  2,  2,  1,
  1,  2,  3,  2,  1,
    1,  2,  2,  1,
  0,  1,  2,  1,  0,
    0,  1,  1,  0
  },
};

//MODE 1
//OFF
void offMode(){
  for (int i = 0; i < numGrid; i++) { //numGrid = 30
    strip.setPixelColor(i, 0, 0, 0);
  }
}

//MODE 2
//LIGHTNING
long lightningStart;
int lightningInterval = 4;
int lightPos1 = 0;  //initial position of the first light that cycles through
int lightPos2 = -1; //initial position of the second light that cycles through

void lightning(){
  strip.setBrightness(255);
  if(millis() - lightningStart >= lightningInterval){ //after a random interval, cycle through the neopixels rapidly
    strip.setPixelColor(lightPos1,255,200,0);
    strip.setPixelColor(lightPos1-1,0,0,0);
    lightPos1 += 1;
    strip.setPixelColor(lightPos2,255,255,0);
    strip.setPixelColor(lightPos2-1,0,0,0);
    lightPos2 += 1;

    if(lightPos1 > random(100,3000)){   //once the light has gotten to a random point, reset light position
      lightPos1 = 0;
      lightPos2 = -1;
    }

    lightningStart = millis();      //reset timer
  }
}

//MODE 3
//FIREBALL
long fireBallStart;
int fireBallInterval = 400; //TIME BETWEEN FRAMES

int whichFrame;
  
void fireBall(){
  strip.setBrightness(brightness);  //200
  if(millis() - fireBallStart >= fireBallInterval){ //after an interval
    whichFrame++;                                   //increase the frame
    if(whichFrame > 2){                             //reset to frame 0 after frame 2
      whichFrame = 0;
    }
    for (int i = 0; i < numGrid; i++) { //numGrid = 30
      int whichLED = i;
      int whichIndex = index[whichLED];
      int whichColor = frames[whichFrame][whichLED];

      int r = colors[whichColor][0];
      int g = colors[whichColor][1];
      int b = colors[whichColor][2];
      
      strip.setPixelColor(whichIndex, r, g, b);
    }
    strip.show();
    fireBallStart = millis();     //reset timer
  }    
}
