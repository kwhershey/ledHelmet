#include "FastLED.h"

// fast led constants
#define LED_PIN    26       // change to your data pin
#define BUTTON_PIN 30 
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    598       // change to the number of LEDs in your strip
#define BRIGHTNESS 32
#define WRAP_NUM 46 
#define LED_TYPE    WS2812B

CRGB leds[NUM_LEDS];
int startIndex=0;
int bottom=2;
int buttonState=0;
int lastButtonState=0;
int pushCounter=0;
int numPrograms=9;

// pong variables
int c_x=0;
int c_y=0;
int c_dx=1;
int c_dy=1;

// matrix variables
#define numParticles 30
int lastRow[numParticles];
int column[numParticles]; 


void setup()
{
  delay(3000);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(BUTTON_PIN,INPUT);
  
  for(int i=0;i<numParticles;i++){
      column[i]=random(WRAP_NUM);
      lastRow[i]=random(NUM_LEDS/WRAP_NUM);
  }
  //Serial.begin(9600);
  //Serial.println("Hello");
  
}

void loop()
{
    if(pushCounter%numPrograms==0){
        rainbowLineTwirl();
    }
    else if(pushCounter%numPrograms==1){
        lineTwirl();
    }
    else if(pushCounter%numPrograms==2){
        heartTwirl();
    }
    else if(pushCounter%numPrograms==3){
        diamondTwirl();
    }
    else if(pushCounter%numPrograms==4){
        matrix();
    }
    else if(pushCounter%numPrograms==5){
        checkerboard();
    }
    else if(pushCounter%numPrograms==6){
        manTwirl();
    }
    else if(pushCounter%numPrograms==7){
        pong();
    }
    else{
        SITwirl();
    }
    buttonState=digitalRead(BUTTON_PIN);
    if(buttonState != lastButtonState){
       if(buttonState==HIGH){
            pushCounter++;
        }
    }
    lastButtonState=buttonState;
}

// rainbow line
void rainbowLineTwirl()
{
    FastLED.clear();
    for(int i=0;i<NUM_LEDS;i++){
      for(int j=0;j<10;j++){
        if(i%WRAP_NUM==(startIndex+j*WRAP_NUM/10)%WRAP_NUM){
            leds[i].setHSV(startIndex*255/WRAP_NUM,255,255);
        }
      }
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}

// single color line
void lineTwirl()
{
    FastLED.clear();
    for(int i=0;i<NUM_LEDS;i++){
      for(int j=0;j<10;j++){
        if(i%WRAP_NUM==(startIndex+j*WRAP_NUM/10)%WRAP_NUM){
            leds[i].setRGB(0,abs(255-510*(float(startIndex)/WRAP_NUM)),255-abs(255-510*(float(startIndex)/WRAP_NUM)));
        }
      }
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
    
}

//heart
void heartTwirl()
{
    FastLED.clear();
    static int heart_x[]={0,-1,0,1,0,-1,-2,1,2,-1,1};
    static int heart_y[]={0,1,1,1,2,2,2,2,2,3,3};
    int x = 0;
    for(int i=0;i<(sizeof(heart_x)/sizeof(int));i++)
    {
        leds[int((heart_x[i]+startIndex+WRAP_NUM/4))%WRAP_NUM+(bottom+heart_y[i])*WRAP_NUM]=CRGB::Red;
        leds[int((heart_x[i]+startIndex+WRAP_NUM/2))%WRAP_NUM+(bottom+heart_y[i])*WRAP_NUM]=CRGB::Blue;
        leds[int((heart_x[i]+startIndex+WRAP_NUM*3/4))%WRAP_NUM+(bottom+heart_y[i])*WRAP_NUM]=CRGB::Green;
        leds[int((heart_x[i]+startIndex))%WRAP_NUM+(bottom+heart_y[i])*WRAP_NUM]=CRGB::Yellow;
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}

// diamond
void diamondTwirl()
{
    FastLED.clear();
    static int diamond[]={WRAP_NUM,(1)*WRAP_NUM-1,(1)*WRAP_NUM+1,(2)*WRAP_NUM};
    static int diamond_x[]={0,-1,1,0};
    static int diamond_y[]={0,1,1,2};
    for(int i=0;i<(sizeof(diamond)/sizeof(int));i++)
    {      
      for(int j=0;j<9;j++)
      {
        for(int k=0;k<3;k++)
        {   
          leds[(diamond_x[i]+startIndex+j*WRAP_NUM/9)%WRAP_NUM+(diamond_y[i]+k*4+1)*WRAP_NUM]=CRGB::Red;
        }
      }
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}

// running man
void manTwirl()
{
    FastLED.clear();
    static int man_x[]={0,1,1,4,2,3,4,2,0,2,0,1,2,3,4,5,2,5,1,2,1,2,3,1,2,3};
    static int eye_x[]={3};
    static int man_y[]={0,1,2,2,3,3,3,4,5,5,6,6,6,6,6,6,7,7,8,8,9,9,9,10,10,10};
    static int eye_y[]={9};
    for(int i=0;i<(sizeof(man_x)/sizeof(int));i++)
    {
        leds[int((man_x[i]+startIndex))%WRAP_NUM+man_y[i]*WRAP_NUM]=CRGB::Green;
    }
    for(int i=0;i<(sizeof(eye_x)/sizeof(int));i++)
    {
        leds[int((eye_x[i]+startIndex))%WRAP_NUM+eye_y[i]*WRAP_NUM]=CRGB::Red;
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}



// space invader 
void SITwirl()
{
    FastLED.clear();
    static int spaceInvader_x[]={0,1,3,4,-3,-1,5,7,-3,-1,0,1,2,3,4,5,7,-3,-2,-1,0,1,2,3,4,5,6,7,-2,-1,1,2,3,5,6,-1,0,1,2,3,4,5,0,4,-1,5};
    static int spaceInvader_y[]={0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,7,7};
    for(int i=0;i<(sizeof(spaceInvader_x)/sizeof(int));i++)
    {
        leds[int((spaceInvader_x[i]+startIndex))%WRAP_NUM+(spaceInvader_y[i]+bottom)*WRAP_NUM]=CRGB::Red;
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}


void matrix()
{
    for(int i=0;i<NUM_LEDS;i++){
        leds[i].fadeToBlackBy(128);
    }
    for(int i=0;i<numParticles;i++){

        if(lastRow[i]<1){
            column[i]=random(WRAP_NUM);
            lastRow[i]=NUM_LEDS/WRAP_NUM;
        }
        if(lastRow[i]*WRAP_NUM+column[i]<NUM_LEDS){
            //leds[lastRow[i]*WRAP_NUM+column[i]]=CRGB::Green;
            leds[lastRow[i]*WRAP_NUM+column[i]].g=255;
            lastRow[i]=lastRow[i]-1;
        }
        else {
            lastRow[i]=lastRow[i]-1;
        }

    }
    FastLED.show();
    delay(50);
}


// checkerboard 
void checkerboard()
{
    FastLED.clear();
    for(int i=0;i<WRAP_NUM;i++){
        for(int j=0;j<(NUM_LEDS/WRAP_NUM)+1;j++){
            if(j*WRAP_NUM+(i+WRAP_NUM/2)%WRAP_NUM<NUM_LEDS){
                if((i/4)%2==(startIndex+j/4)%2){
                    leds[j*WRAP_NUM+(i+WRAP_NUM/2)%WRAP_NUM].setHSV(startIndex*255/WRAP_NUM,255,255);
            }
            }
        }
    }
    FastLED.show();
    delay(600);

    startIndex=(startIndex+1)%WRAP_NUM;
}


// pong
void pong()
{
    FastLED.clear();
    leds[c_x%WRAP_NUM+c_y*WRAP_NUM]=CRGB::Red;
    if(c_x==17){
      c_dx=-1;
    }
    else if(c_x==-17){
      c_dx=1;
    }
    if(c_y==12){
      c_dy=-1;
    }
    else if(c_y==0){
      c_dy=1;
    }
    c_x=c_x+c_dx;
    c_y=c_y+c_dy;
    FastLED.show();
    delay(30);

}
