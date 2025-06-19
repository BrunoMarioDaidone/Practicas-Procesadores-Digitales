#include "HUMEDAD.h"

HumedadSuelo::HumedadSuelo(uint8_t p) : pin(p) {
    pinMode(pin, INPUT);
}

int HumedadSuelo::leerHumedad() {
    return analogRead(pin);
}

float HumedadSuelo::porcentaje() {
    int valor = leerHumedad();
    // Ajusta los valores según tus pruebas/calibración:
    int seco = 4095;   // sin agua
    int mojado = 1500; // completamente húmedo

    valor = constrain(valor, mojado, seco);
    return 100.0 * (seco - valor) / (seco - mojado);
}
