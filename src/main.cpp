// Le code minimal

#include <FastLED.h>
#include <Arduino.h> 
#include <MicroOscSlip.h>
#define MA_BROCHE_BOUTON 39
#define MA_BROCHE_ANGLE 32

CRGB pixelAtom;

MicroOscSlip<128> monOsc(&Serial);

void setup() {
  Serial.begin(115200);
  pinMode( MA_BROCHE_BOUTON , INPUT );
  FastLED.addLeds<WS2812, 27, GRB>(&pixelAtom, 1); 
  
}

void loop() {
  int maLectureBouton = digitalRead( MA_BROCHE_BOUTON );
  int maLectureAnalogique = analogRead(MA_BROCHE_ANGLE);
  

  monOsc.sendInt( "/bouton" , maLectureBouton); // <------ Le nouveau "print" qui remplace serial.print pr le MicroOscSlip
  monOsc.sendInt( "/analog" , maLectureAnalogique); // Pr le analog

  // Serial.println(maLectureBouton);
  // On enlève le serial print pcq dès qu'on utilise OSC slip, il faut le faire
  // info: https://t-o-f.info/aide/#/microosc/initialisation/

  delay(100);

if (maLectureAnalogique < 4095 / 3) {
  pixelAtom = CRGB(0,0,255);
} else if (maLectureAnalogique < 4095 / 3 * 2) {
    pixelAtom = CRGB(0, 255, 0);
} else {
  pixelAtom = CRGB(255, 0, 0);
}

  FastLED.show();
  
}