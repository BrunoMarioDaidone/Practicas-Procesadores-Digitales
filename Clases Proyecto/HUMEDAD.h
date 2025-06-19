#ifndef HUMEDAD_H
#define HUMEDAD_H

#include <Arduino.h>

class HumedadSuelo {
private:
    uint8_t pin;

public:
    HumedadSuelo(uint8_t p);
    int leerHumedad();       // Valor crudo: 0-4095 (ADC)
    float porcentaje();      // Convertido a porcentaje
};

#endif
