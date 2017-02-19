#include "FastLED.h"

// fast led constants
#define DATA_PIN    5       // change to your data pin
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    600       // change to the number of LEDs in your strip
#define BRIGHTNESS 32
#define WRAP_NUM 55

// change WS2812B to match your type of LED, if different
// list of supported types is here:
// https://github.com/FastLED/FastLED/wiki/Overview
#define LED_TYPE    WS2812B

// this creates an LED array to hold the values for each led in your strip
CRGB leds[NUM_LEDS];
int startIndex=0;

void setup()
{
  delay(3000);
  
  // the wiki features a much more basic setup line:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //Serial.begin(9600);
  //Serial.print("Good to go");

  
  
}

void loop()
{
    shapeTwirl();
}

void lineTwirl()
{
    FastLED.clear();
    for(int i=0;i<NUM_LEDS;i++){
        if(i%WRAP_NUM==startIndex){
            leds[i]=CRGB::Red;
        }
    }
    FastLED.show();
    delay(30);

    //delay(5);
    startIndex=(startIndex+1)%WRAP_NUM;
    //Serial.print((startIndex-1)%WRAP_NUM);
}


void shapeTwirl()
{
    FastLED.clear();
    int bottom=6;
    static int diamond[]={bottom*WRAP_NUM,(bottom+1)*WRAP_NUM-1,(bottom+1)*WRAP_NUM+1,(bottom+2)*WRAP_NUM};
    for(int i=0;i<sizeof(diamond);i++)
    {
        leds[(diamond[i]+startIndex)]=CRGB::Red;
    }
    FastLED.show();
    delay(70);

    startIndex=(startIndex+1)%WRAP_NUM;
}
