#include "RELE.h"
#include <Arduino.h>


    RELE::RELE(uint8_t pin) : _pin(pin) {
        pinMode(_pin, OUTPUT);
        close(); // Make sure the valve is initially closed.
    }
    
    // Opens the valve. Depending on your relay logic, HIGH may open it.
    void RELE::open() {
        digitalWrite(_pin, HIGH);
    }
    
    // Closes the valve.
    void RELE::close() {
        digitalWrite(_pin, LOW);
    }
