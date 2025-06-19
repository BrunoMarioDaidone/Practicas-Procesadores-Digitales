
#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <NimBLEDevice.h>
#include "RELE.h"
#include "TEMPERATURA.h"
#include "HUMEDAD.h"

class BLEManager {
public:
    BLEManager();
    void begin(RELE* rele, TemperaturaDS18B20* tempSensor, HumedadSuelo* humSensor);
    void notify();

private:
    RELE* _rele;
    TemperaturaDS18B20* _temp;
    HumedadSuelo* _hum;

    NimBLECharacteristic* tempChar;
    NimBLECharacteristic* humChar;
    NimBLECharacteristic* releChar;
};

#endif
