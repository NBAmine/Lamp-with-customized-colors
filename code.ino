#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <Arduino.h>
#include <Adafruit_FT6206.h>
#include <Adafruit_NeoPixel.h>
#include <map>
#include <cmath>
using namespace std;

#define NUMPIXELS 16
#define NEO_PIN 14

Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

#define TFT_DC 12
#define TFT_CS 13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_FT6206 ts = Adafruit_FT6206();


int brightnessBarY = 40;
int redBarY = 90;
int greenBarY = 130;
int blueBarY = 170;

String bar;

int R,G,B,BRIGHT;

boolean tolerateFirstOutBound = false;

int red[8],green[8],blue[8];

std::map<string, string> bin_hex;

void setup() {
  bin_hex["0000"] = "0";
  bin_hex["0001"] = "1";
  bin_hex["0010"] = "2";
  bin_hex["0011"] = "3";
  bin_hex["0100"] = "4";
  bin_hex["0101"] = "5";
  bin_hex["0110"] = "6";
  bin_hex["0111"] = "7";
  bin_hex["1000"] = "8";
  bin_hex["1001"] = "9";
  bin_hex["1010"] = "A";
  bin_hex["1011"] = "B";
  bin_hex["1100"] = "C";
  bin_hex["1101"] = "D";
  bin_hex["1110"] = "E";
  bin_hex["1111"] = "F";

  Serial.begin(115200);

  pixels.begin();
  tft.begin();
  ts.begin();

  tft.setRotation(1); 
  tft.setTextSize(2);

  display();

  R = 255;
  G = 255;
  B = 255;
  BRIGHT = 255;

  pixels.setBrightness(BRIGHT);
}

void loop() {
  

  if(ts.touched()){
    barClicked();
    if(bar=="red"){
      modulateRed();
    }else if(bar=="green"){
      modulateGreen();
    }else if(bar=="blue"){
      modulateBlue();
    }else if(bar=="brightness"){
      modulateBrightness();
    }
    bar = "";
  }

  tolerateFirstOutBound = false;

  lightLamp();
}

void barClicked(){
  TS_Point p = ts.getPoint();
  p.x = ::map(p.x, 0, 240, 240, 0);
  p.y = ::map(p.y, 0, 320, 320, 0);
  int x = tft.width() - p.y;
  int y = p.x;
  int redY = redBarY-3;
  int greenY = greenBarY-3;
  int blueY = blueBarY-3;
  int brightnessY = brightnessBarY-3;

  for(int i = 0; i < 12 ; i++){

    ++redY;
    ++greenY;
    ++blueY;
    ++brightnessY;

    if(redY == y){
      bar = "red";
    }else if(greenY == y){
      bar = "green";
    }else if(blueY == y){
      bar = "blue";
    }else if(brightnessY == y){
      bar = "brightness";
    }
  }
}

void display(){

  brightnessInput();

  redInput();

  greenInput();

  blueInput();

  displayColorOnScreen();
}

void brightnessInput(){
  tft.setCursor(90,10);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Brightness");

  tft.fillRect(0, brightnessBarY, 300, 6,ILI9341_WHITE);
}

void redInput(){
  tft.setCursor(0, 70);
  tft.setTextColor(ILI9341_RED);
  tft.println("RED");

  tft.fillRect(0, redBarY, 300, 6, ILI9341_RED);
}

void greenInput(){
  tft.setCursor(0, 110);
  tft.setTextColor(ILI9341_GREEN);
  tft.println("GREEN");
  
  tft.fillRect(0, greenBarY, 300, 6, ILI9341_GREEN);
}

void blueInput(){
  tft.setCursor(0, 150);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("BLUE");

  tft.fillRect(0, blueBarY, 300, 6, ILI9341_BLUE);
}

void displayColorOnScreen(){
  tft.setCursor(0, 200);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Led Color");

  tft.fillRoundRect(120, 193, 188, 30, 5, ILI9341_WHITE);
}

void modulateRed(){
  while(ts.touched()){
    TS_Point p = ts.getPoint();
    p.y = ::map(p.y, 0, 320, 320, 0);
    int x = tft.width() - p.y;
    int X_axis = x; 
    x = ::map(x, 0, 300, 0, 255);
    if(x >255){
      x = 255;
    }

    R = x;

    lightLamp();

    updateRedBar(X_axis);

    updateColorOnScreen();
  }
}

void updateRedBar(int x){
  if(x <= 300){
    tft.fillRect(0, 90, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 90, x, 6, ILI9341_RED);
  }else if(!tolerateFirstOutBound){
    tolerateFirstOutBound = true;
    tft.fillRect(0, 90, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 90, 300, 6, ILI9341_RED);
  }
}

void modulateGreen(){
  while(ts.touched()){
    TS_Point p = ts.getPoint();
    p.y = ::map(p.y, 0, 320, 320, 0);
    int x = tft.width() - p.y;
    int X_axis = x;

    x = ::map(x, 0, 300, 0, 255);
    if(x >255){
      x = 255;
    }

    G = x;

    lightLamp();

    updateGreenBar(X_axis);

    updateColorOnScreen();
  }
}

void updateGreenBar(int x){
  if(x <= 300){
    tft.fillRect(0, 130, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 130, x, 6, ILI9341_GREEN);
  }else if(!tolerateFirstOutBound){
    tolerateFirstOutBound = true;
    tft.fillRect(0, 130, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 130, 300, 6, ILI9341_GREEN);
  }
}

void modulateBlue(){
  while(ts.touched()){
    TS_Point p = ts.getPoint();
    p.y = ::map(p.y, 0, 320, 320, 0);
    int x = tft.width() - p.y;
    int X_axis = x;

    x = ::map(x, 0, 300, 0, 255);
    if(x >255){
      x = 255;
    }

    B = x;

    updateBlueBar(X_axis);

    updateColorOnScreen();

    lightLamp();
  }
}

void updateBlueBar(int x){
  if(x <= 300){
    tft.fillRect(0, 170, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 170, x, 6, ILI9341_BLUE);
  }else if(!tolerateFirstOutBound){
    tolerateFirstOutBound = true;
    tft.fillRect(0, 170, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 170, 300, 6, ILI9341_BLUE);
  }
}

void modulateBrightness(){
  while(ts.touched()){
    TS_Point p = ts.getPoint();
    p.y = ::map(p.y, 0, 320, 320, 0);
    int x = tft.width() - p.y;
    int X_axis = x;

    x = ::map(x, 0, 300, 0, 255);
    if(x >255){
      x = 255;
    }

    BRIGHT = x;

    updateBrightnessBar(X_axis);

    updateColorOnScreen();

    pixels.setBrightness(BRIGHT);
  }
}

void updateBrightnessBar(int x){
  if(x <= 300){
    tft.fillRect(0, 40, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 40, x, 6, ILI9341_WHITE);
  }else if(!tolerateFirstOutBound){
    tolerateFirstOutBound = true;
    tft.fillRect(0, 40, 300, 6, ILI9341_BLACK);
    tft.fillRect(0, 40, 300, 6, ILI9341_WHITE);
  }
}

void updateColorOnScreen(){
  decimalToBinary(R, red);
  decimalToBinary(G, green);
  decimalToBinary(B, blue);

  int color[16];
  int counter = -1;
  
  for(int i= 3;i < 8;i++){
    color[++counter] = blue[i];
  }
  for(int i=2;i < 8;i++){
    color[++counter] = green[i];
  }
  for(int i= 3;i < 8;i++){
    color[++counter] = red[i];
  }

  uint16_t finalColor = binarytoDecimal(color);

  tft.fillRoundRect(120, 193, 188, 30, 5, finalColor);
}

void lightLamp(){
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(R, G, B));
    pixels.show();
  }
}

void decimalToBinary(int n, int* arr){
  int i = 0;
  for(int i = 0;i < 8;i++){
    if(n >= 1){
      arr[i] = n % 2;
      n = n/2;
    }else{
      arr[i] = 0;
    }
  }
}

uint16_t binarytoDecimal(int *arr){
  uint16_t color = 0;
  for(int i = 0; i < 16 ; i++){
    if(arr[i] == 1){
      color += pow(2,i);
    }
  }
  return color;
}
