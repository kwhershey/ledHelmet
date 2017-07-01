#include "FastLED.h"

// fast led constants
#define LED_PIN    26       // change to your data pin
#define BUTTON_PIN 30 
//#define 
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    900       // change to the number of LEDs in your strip
#define BRIGHTNESS 32
#define WRAP_NUM 55
#define LED_TYPE    WS2812B

CRGB leds[NUM_LEDS];
int startIndex=0;
int bottom=2;
int buttonState=0;
int lastButtonState=0;
int pushCounter=0;
int numPrograms=8;

// matrix variables
#define numParticles 15
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
        if(i%WRAP_NUM==startIndex){
            leds[i].setHSV(startIndex*255/WRAP_NUM,255,255);
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
        if(i%WRAP_NUM==startIndex){
            leds[i].setRGB(0,abs(255-510*(float(startIndex)/WRAP_NUM)),255-abs(255-510*(float(startIndex)/WRAP_NUM)));
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
    static int heart[]={bottom*WRAP_NUM,(bottom+1)*WRAP_NUM-1,(bottom+1)*WRAP_NUM,(bottom+1)*WRAP_NUM+1,(bottom+2)*WRAP_NUM,(bottom+2)*WRAP_NUM-1,(bottom+2)*WRAP_NUM-2,(bottom+2)*WRAP_NUM+1,(bottom+2)*WRAP_NUM+2,(bottom+3)*WRAP_NUM-1,(bottom+3)*WRAP_NUM+1};
    for(int i=0;i<(sizeof(heart)/sizeof(int));i++)
    {
        leds[int(heart[i]+startIndex)]=CRGB::Red;
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}

// diamond
void diamondTwirl()
{
    FastLED.clear();
    static int diamond[]={bottom*WRAP_NUM,(bottom+1)*WRAP_NUM-1,(bottom+1)*WRAP_NUM+1,(bottom+2)*WRAP_NUM};
    for(int i=0;i<(sizeof(diamond)/sizeof(int));i++)
    {
        leds[int(diamond[i]+startIndex)]=CRGB::Red;
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}

// running man
void manTwirl()
{
    FastLED.clear();
    static int man[]={bottom*WRAP_NUM,(bottom+1)*WRAP_NUM+1, (bottom+2) *WRAP_NUM+1, (bottom+2) *WRAP_NUM+4, (bottom+3) *WRAP_NUM+2,(bottom+3) *WRAP_NUM+3,(bottom+3) *WRAP_NUM+4,(bottom+4) *WRAP_NUM+2,(bottom+5) *WRAP_NUM,(bottom+5) *WRAP_NUM+2,(bottom+6) *WRAP_NUM,(bottom+6) *WRAP_NUM+1,(bottom+6) *WRAP_NUM+2,(bottom+6) *WRAP_NUM+3,(bottom+6) *WRAP_NUM+4,(bottom+6) *WRAP_NUM+5,(bottom+7) *WRAP_NUM+2,(bottom+7) *WRAP_NUM+5,(bottom+8) *WRAP_NUM+1,(bottom+8) *WRAP_NUM+2,(bottom+9) *WRAP_NUM+1,(bottom+9) *WRAP_NUM+2,(bottom+9) *WRAP_NUM+3,(bottom+10) *WRAP_NUM+1,(bottom+10) *WRAP_NUM+2,(bottom+10) *WRAP_NUM+3, };
    static int eye[]={(bottom+8) *WRAP_NUM+3};
    for(int i=0;i<(sizeof(man)/sizeof(int));i++)
    {
        leds[int(man[i]+startIndex)]=CRGB::Green;
    }
    for(int i=0;i<(sizeof(eye)/sizeof(int));i++)
    {
        leds[int(eye[i]+startIndex)]=CRGB::Red;
    }
    FastLED.show();
    delay(30);

    startIndex=(startIndex+1)%WRAP_NUM;
}



// space invader 
void SITwirl()
{
    FastLED.clear();
    static int spaceInvader[]={(bottom)*WRAP_NUM,(bottom)*WRAP_NUM+1,(bottom)*WRAP_NUM+3,(bottom)*WRAP_NUM+4,(bottom+1)*WRAP_NUM-3,(bottom+1)*WRAP_NUM-1,(bottom+1)*WRAP_NUM+5,(bottom+1)*WRAP_NUM+7,(bottom+2)*WRAP_NUM-3,(bottom+2)*WRAP_NUM-1,(bottom+2)*WRAP_NUM,(bottom+2)*WRAP_NUM+1,(bottom+2)*WRAP_NUM+2,(bottom+2)*WRAP_NUM+3,(bottom+2)*WRAP_NUM+4,(bottom+2)*WRAP_NUM+5,(bottom+2)*WRAP_NUM+7,
    (bottom+3)*WRAP_NUM-3,(bottom+3)*WRAP_NUM-2,(bottom+3)*WRAP_NUM-1,(bottom+3)*WRAP_NUM,(bottom+3)*WRAP_NUM+1,(bottom+3)*WRAP_NUM+2,(bottom+3)*WRAP_NUM+3,(bottom+3)*WRAP_NUM+4,(bottom+3)*WRAP_NUM+5,(bottom+3)*WRAP_NUM+6,(bottom+3)*WRAP_NUM+7,(bottom+4)*WRAP_NUM-2,(bottom+4)*WRAP_NUM-1,(bottom+4)*WRAP_NUM+1,(bottom+4)*WRAP_NUM+2,(bottom+4)*WRAP_NUM+3,(bottom+4)*WRAP_NUM+5,(bottom+4)*WRAP_NUM+6,
    (bottom+5)*WRAP_NUM-1,(bottom+5)*WRAP_NUM,(bottom+5)*WRAP_NUM+1,(bottom+5)*WRAP_NUM+2,(bottom+5)*WRAP_NUM+3,(bottom+5)*WRAP_NUM+4,(bottom+5)*WRAP_NUM+5,(bottom+6)*WRAP_NUM,(bottom+6)*WRAP_NUM+4,(bottom+7)*WRAP_NUM-1,(bottom+7)*WRAP_NUM+5};
    for(int i=0;i<(sizeof(spaceInvader)/sizeof(int));i++)
    {
        leds[int(spaceInvader[i]+startIndex)]=CRGB::Red;
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
            if(j*WRAP_NUM+i<NUM_LEDS){
                if((i/4)%2==(startIndex+j/4)%2){
                    leds[j*WRAP_NUM+i].setHSV(startIndex*255/WRAP_NUM,255,255);
            }
            }
        }
    }
    FastLED.show();
    delay(600);

    startIndex=(startIndex+1)%WRAP_NUM;
}
