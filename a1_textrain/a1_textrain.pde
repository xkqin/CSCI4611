/**
    CSci-4611 Assignment #1 Text Rain
**/


import processing.video.*;

// Global variables for handling video data and the input selection screen
String[] cameras;
Capture cam;

Movie mov;
PImage inputImage;
PImage outputImage;
boolean inputMethodSelected = false;
boolean ifBlack = false;
float value = 0.5;
int ht, wid;
ArrayList arrayRain;
String words = "Blue mountains lie across the northern outskirts white water circles around the eastern town Once we part from this place a lone thistledown will be on a thousand-mile journey A floating cloud is what you want to be like the setting sun is how your old friend feels A wave of the hand and we go our own way Whinny whinny the horses neigh";
PFont font;
float timeIntervel = 50;
int timeControl = -1;


void setup() {
  size(1280, 720);  
  inputImage = new PImage(width, height, RGB);
  font = loadFont("TimesNewRomanPSMT-48.vlw");
  textFont(font, 32);
  arrayRain = new ArrayList<TextRain>();
}


PImage flip (PImage orImage) {
  PImage fianl = new PImage(orImage.width, orImage.height, RGB);
  for (int j = 0; j < orImage.height; j++) {
    for (int i = 0; i < orImage.width; i++) {
      fianl.pixels[(orImage.width - i - 1) + orImage.width*j] = orImage.pixels[i + orImage.width*j];
    }
  }
  return fianl;
}



void draw() {
  // When the program first starts, draw a menu of different options for which camera to use for input
  // The input method is selected by pressing a key 0-9 on the keyboard
    if (timeControl != -1) {
    timeIntervel = millis() - timeControl;
  }
  timeControl = millis();
  if (!inputMethodSelected) {
    cameras = Capture.list();
    int y=40;
    text("O: Offline mode, test with TextRainInput.mov movie file instead of live camera feed.", 20, y);
    y += 40; 
    for (int i = 0; i < min(9,cameras.length); i++) {
      text(i+1 + ": " + cameras[i], 20, y);
      y += 40;
    }
    return;
  }


  // This part of the draw loop gets called after the input selection screen, during normal execution of the program.

  
  // STEP 1.  Load an image, either from a movie file or from a live camera feed. Store the result in the inputImage variable
  
  if ((cam != null) && (cam.available())) {
    cam.read();

    inputImage.copy(cam, 0,0,cam.width,cam.height, 0,0,inputImage.width,inputImage.height);
    inputImage = flip(inputImage);
  }
  else if ((mov != null) && (mov.available())) {
    mov.read();
    inputImage.copy(mov, 0,0,mov.width,mov.height, 0,0,inputImage.width,inputImage.height);
    inputImage = flip(inputImage);
  }
  wid = inputImage.width;
  ht = inputImage.height;

  // Fill in your code to implement the rest of TextRain here..

  PImage blackImg;
  PImage makeone = new PImage(inputImage.width, inputImage.height, RGB);
  for (int j = 0; j < inputImage.height; j++)
    for (int i = 0; i < inputImage.width; i++) {
      makeone.pixels[i + inputImage.width * j] = inputImage.pixels[i + inputImage.width * j];
    }
  blackImg = makeone;
  blackImg.filter(THRESHOLD,value);
  // Tip: This code draws the current input image to the screen
  if (ifBlack) {
    outputImage = blackImg;
  }
  else {
    inputImage.filter(GRAY);
    outputImage = inputImage;
    
  }
  set(0, 0, outputImage);
  
  TextRain rains = new TextRain();
  if (rains.x >= 0 && rains.x + rains.size < blackImg.width &&
        rains.y >= 0 && rains.y + rains.size < blackImg.height){

        if (random(0, 13) < 3) {
          arrayRain.add(new TextRain());
        }
  }
  for (int i = arrayRain.size() - 1; i >= 0; i--) {
    
     rains = (TextRain) arrayRain.get(i);
  if (rains.x >= 0 && rains.x + rains.size < blackImg.width &&
        rains.y >= 0 && rains.y + rains.size < blackImg.height){
    rains.checkPoint(blackImg);
    textFont(font, rains.size);
    fill(rains.clr);
    text(rains.letter, rains.x, rains.y);
     }
  }
}



void keyPressed() {
  
  if (!inputMethodSelected) {
    // If we haven't yet selected the input method, then check for 0 to 9 keypresses to select from the input menu
    if ((key >= '0') && (key <= '9')) { 
      int input = key - '0';
      if (input == 0) {
        println("Offline mode selected.");
        mov = new Movie(this, "TextRainInput.mov");
        mov.loop();
        inputMethodSelected = true;
      }
      else if ((input >= 1) && (input <= 9)) {
        println("Camera " + input + " selected.");           
        // The camera can be initialized directly using an element from the array returned by list():
        cam = new Capture(this, cameras[input-1]);
        cam.start();
        inputMethodSelected = true;
      }
    }
    return;
  }


  // This part of the keyPressed routine gets called after the input selection screen during normal execution of the program
  // Fill in your code to handle keypresses here..
  
  if (key == CODED) {
    if (keyCode == UP) {
      // up arrow key pressed
      value += 0.01;
    }
    else if (keyCode == DOWN) {
      // down arrow key pressed
      value -= 0.01;
    }
  }
  else if (key == ' ') {
    // space bar pressed
    ifBlack = !ifBlack;
  }
  
}

class TextRain{
  int x;
  int y;
  char letter;
  int yVelocity;
  int xVelocity;
  int size;
  color clr;

  TextRain() {
    y = 0;
    x = (int) random(0, wid);
    letter = (char)words.charAt(int(random(0,273)));
    yVelocity = int((random(3, 6))  * (timeIntervel / 50.0));
    xVelocity = 1;
    size = int(random(30, 40));
    clr = color(0, 0, 255);
  }

  void checkPoint(PImage blackImg) {

    color dark = color(0,0,0);
    int downCheck = (x + size/2) + blackImg.width * (y + size);
    if ((blackImg.pixels[downCheck] != dark))
      y += yVelocity;


    if ((blackImg.pixels[downCheck] == dark))
    {
      y -= xVelocity - 1;
       clr = color(255, 0, 30);
  }
      int upCheck = (x + size/2 ) + blackImg.width * y;
    if((blackImg.pixels[downCheck] == dark) && (blackImg.pixels[upCheck] == dark))
    {
      y -=8;
    }
     int goLeft = (x) + blackImg.width * (y + size * 8/9 );
    if ((blackImg.pixels[goLeft] !=dark))
      x -= xVelocity;
    int goRight = (x + size) + blackImg.width * (y + size *8/9);
    if ((blackImg.pixels[goRight] != dark))
      x += xVelocity;
    
  }


}