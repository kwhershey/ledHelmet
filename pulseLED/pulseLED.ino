#include "FastLED.h"

// fast led constants
#define LED_PIN    22       // change to your data pin
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    900       // change to the number of LEDs in your strip
#define BRIGHTNESS 32
#define WRAP_NUM 55
#define LED_TYPE    WS2812B

#define SAMPLEPERIODUS 200

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
int startIndex=0;
CRGB leds[NUM_LEDS];
float sample, value, envelope, beat, thresh; 
unsigned long time = micros(); // Used to track rate

void setup()
{
  delay(3000);

    // Set ADC to 77khz, max for 10bit
  sbi(ADCSRA,ADPS2);
  cbi(ADCSRA,ADPS1);
  cbi(ADCSRA,ADPS0);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);


    int flip=0;
  
}

void loop()
{
    checkerboard();
}

// checkerboard 
void checkerboard()
{
    for(int i=0;i<50;i++){
        // Read ADC and center so +-512
        sample = (float)analogRead(0)-503.f;

        // Filter only bass component
        value = bassFilter(sample);

        // Take signal amplitude and filter
        if(value < 0)value=-value;
            envelope = envelopeFilter(value);

    }

    // Filter out repeating bass sounds 100 - 180bpm
    beat = beatFilter(envelope);

    // Threshold it based on potentiometer on AN1
    thresh = 0.005f * (float)analogRead(0);

    // If we are above threshold, light up LED
    if(beat > thresh){
        for(int i=0;i<WRAP_NUM;i++){
            for(int j=0;j<(NUM_LEDS/WRAP_NUM)+1;j++){
                if(j*WRAP_NUM+i<NUM_LEDS){
                    if((i/4)%2==(j/4)%2){
                        leds[j*WRAP_NUM+i].setHSV(startIndex*255/WRAP_NUM,255,255);
                }
                }
            }
        }
    } 
    else{ 
        FastLED.clear();
    }
    FastLED.show();



    // Consume excess clock cycles, to keep at 5000 hz
    for(unsigned long up = time+SAMPLEPERIODUS; time > 20 && time < up; time = micros());

    startIndex=(startIndex+1)%WRAP_NUM;
}

// 20 - 200hz Single Pole Bandpass IIR Filter
float bassFilter(float sample) {
        static float xv[3] = {0,0,0}, yv[3] = {0,0,0};
            xv[0] = xv[1]; xv[1] = xv[2]; 
                xv[2] = sample / 9.1f;
                    yv[0] = yv[1]; yv[1] = yv[2]; 
                        yv[2] = (xv[2] - xv[0])
                                    + (-0.7960060012f * yv[0]) + (1.7903124146f * yv[1]);
                            return yv[2];
}

// 10hz Single Pole Lowpass IIR Filter
float envelopeFilter(float sample) { //10hz low pass
        static float xv[2] = {0,0}, yv[2] = {0,0};
            xv[0] = xv[1]; 
                xv[1] = sample / 160.f;
                    yv[0] = yv[1]; 
                        yv[1] = (xv[0] + xv[1]) + (0.9875119299f * yv[0]);
                            return yv[1];
}

// 1.7 - 3.0hz Single Pole Bandpass IIR Filter
float beatFilter(float sample) {
        static float xv[3] = {0,0,0}, yv[3] = {0,0,0};
            xv[0] = xv[1]; xv[1] = xv[2]; 
                xv[2] = sample / 7.015f;
                    yv[0] = yv[1]; yv[1] = yv[2]; 
                        yv[2] = (xv[2] - xv[0])
                                    + (-0.7169861741f * yv[0]) + (1.4453653501f * yv[1]);
                            return yv[2];
}

