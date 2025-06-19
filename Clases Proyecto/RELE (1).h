#ifndef RELE_H
#define RELE_H

#include <Arduino.h>

class RELE {
public:
// Constructor
    RELE(uint8_t pin);  
// Functions
    void open();
    void close();

private:
    uint8_t _pin; 
};

#endif
