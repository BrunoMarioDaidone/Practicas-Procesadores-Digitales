#ifndef BUZZ_H
#define BUZZ_H

#include <Arduino.h>

class BUZZ {
private:
    int pin;
    void ring(const int x);

public:
    BUZZ(int buzzerPin);
    void shortRing();
    void longRing();
};

#endif
