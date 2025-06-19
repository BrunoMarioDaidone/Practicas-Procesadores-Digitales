#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

class JOYSTICK {
public:
    JOYSTICK(int xPin, int yPin, int buttonPin);
    void begin();
    int getX();
    int getY();
    bool isPressed();
    char Lado(int x,int y,bool p);
   
private:
    int _xPin, _yPin, _buttonPin;
};

#endif
