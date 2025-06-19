#include "JOYSTICK.h"

JOYSTICK::JOYSTICK(int xPin, int yPin, int buttonPin)
    : _xPin(xPin), _yPin(yPin), _buttonPin(buttonPin){}

void JOYSTICK::begin() {
    pinMode(_buttonPin, INPUT_PULLUP);
}

int JOYSTICK::getX() {
    return analogRead(_xPin);
}

int JOYSTICK::getY() {
    return analogRead(_yPin);
}

bool JOYSTICK::isPressed() {
    return digitalRead(_buttonPin) == LOW;
}

char JOYSTICK::Lado(int x,int y,bool p) {
    if ( p == true)return 'S';
    else if ( y > 3900)return 'E';
    else if ( y < 1800)return 'D';
    else return 'Q';
    delay(300);
    
}
