#include "BLEManager.h"
#include <NimBLE2902.h>
#include <string.h> // para strlen()

// Definición de UUIDs para el servicio y las características
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define TEMP_CHAR_UUID      "12345678-1234-1234-1234-1234567890ac"
#define HUMEDAD_CHAR_UUID   "12345678-1234-1234-1234-1234567890ad"
#define RIEGO_CHAR_UUID     "12345678-1234-1234-1234-1234567890ae"

// Callback para la característica de riego
class RiegoCallback : public NimBLECharacteristicCallbacks {
public:
    RiegoCallback(RELE* rele) : _rele(rele) {}
    void onWrite(NimBLECharacteristic* pCharacteristic) override {
        std::string value = pCharacteristic->getValue();
        if (!value.empty() && value[0] == 0x01) {
            Serial.println("🟢 Riego activado desde BLE");
            _rele->open();
            delay(2000);
            _rele->close();
            Serial.println("🔴 Riego terminado");
        }
    }
private:
    RELE* _rele;
};

BLEManager::BLEManager() 
    : _rele(nullptr),
      _temp(nullptr),
      _hum(nullptr),
      tempChar(nullptr),
      humChar(nullptr),
      releChar(nullptr) {
}

void BLEManager::begin(RELE* rele, TemperaturaDS18B20* tempSensor, HumedadSuelo* humSensor) {
    _rele = rele;
    _temp = tempSensor;
    _hum = humSensor;

    // Inicializa el BLE con el nombre "RiegoBLE"
    NimBLEDevice::init("RiegoBLE");
    NimBLEServer* pServer = NimBLEDevice::createServer();
    NimBLEService* pService = pServer->createService(SERVICE_UUID);

    // Característica de temperatura: lectura y notificación
    tempChar = pService->createCharacteristic(
        TEMP_CHAR_UUID, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    tempChar->addDescriptor(new NimBLE2902());

    // Característica de humedad: lectura y notificación
    humChar = pService->createCharacteristic(
        HUMEDAD_CHAR_UUID, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    humChar->addDescriptor(new NimBLE2902());

    // Característica de riego: sólo escritura
    releChar = pService->createCharacteristic(
        RIEGO_CHAR_UUID, NIMBLE_PROPERTY::WRITE);
    releChar->setCallbacks(new RiegoCallback(_rele));

    pService->start();

    // Configuración de la publicidad del servicio BLE
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    Serial.println("✅ BLE iniciado desde BLEManager");
}

void BLEManager::notify() {
    if (!_temp || !_hum || !tempChar || !humChar) return;

    float temp = _temp->leerTemperatura();
    int hum = _hum->porcentaje();

    // Convertimos la temperatura a una cadena con dos decimales.
    char tempStr[10];
    snprintf(tempStr, sizeof(tempStr), "%.2f", temp);

    // Convertimos la humedad a cadena.
    char humStr[5];
    snprintf(humStr, sizeof(humStr), "%d", hum);

    // Enviamos únicamente los bytes correspondientes al string, realizando el casting adecuado.
    tempChar->setValue((const uint8_t*)tempStr, strlen(tempStr));
    tempChar->notify();

    humChar->setValue((const uint8_t*)humStr, strlen(humStr));
    humChar->notify();

    Serial.printf("🌡 Notificado: %s °C | 💧 %s %%\n", tempStr, humStr);
}
