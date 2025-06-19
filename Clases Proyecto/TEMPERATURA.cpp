#include "TEMPERATURA.h"
#include <Arduino.h>

TemperaturaDS18B20::TemperaturaDS18B20(uint8_t p)
    : pin(p), oneWire(p), sensor(&oneWire) {}

void TemperaturaDS18B20::iniciar() {
    sensor.begin();
}

float TemperaturaDS18B20::leerTemperatura() {
    sensor.requestTemperatures(); // Solicita lectura
    return sensor.getTempCByIndex(0); // Primer sensor encontrado
    Serial.println(sensor.getTempCByIndex(0));
}
