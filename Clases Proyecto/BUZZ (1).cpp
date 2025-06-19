#include "BUZZ.h"

BUZZ::BUZZ(int buzzerPin) {
    pin = buzzerPin;
    pinMode(pin, OUTPUT);
}

void BUZZ::ring(const int x) {
    analogWrite(pin, 50);
    tone(pin, 277,100);
    tone(pin, 329,100);
    tone(pin, 391,100);
    tone(pin, 493,100);
    delay(100);
    if(x == 1){
    tone(pin, 277,100);
    tone(pin, 329,100);
    tone(pin, 349,100);
    tone(pin, 391,100);
    }
    else{
    tone(pin, 277,100);
    tone(pin, 329,100);
    tone(pin, 369,100);
    }
    delay(100);
    noTone(pin);
}

void BUZZ::shortRing() {
    ring(1);
}

void BUZZ::longRing() {
    ring(2);
}
