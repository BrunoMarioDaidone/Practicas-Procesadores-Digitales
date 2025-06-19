#ifndef TEMPERATURA_DS18B20_H
#define TEMPERATURA_DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>

class TemperaturaDS18B20 {
private:
    uint8_t pin;
    OneWire oneWire;
    DallasTemperature sensor;

public:
    TemperaturaDS18B20(uint8_t p);
    void iniciar();
    float leerTemperatura(); // °C
};

#endif
