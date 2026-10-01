# Informe de la Práctica de Laboratorio 7: Buses de Comunicación III (I2S)

## Introducción
El objetivo de esta práctica fue explorar el protocolo I2S (Inter-Integrated Circuit Sound), utilizado para la transmisión de señales de audio digital entre dispositivos. Se implementaron dos ejercicios principales: reproducción de audio desde la memoria interna del ESP32 y desde una tarjeta SD externa, utilizando el protocolo I2S y el amplificador MAX98357.

---
## Desarrollo de la Práctica

### Ejercicio 1: Reproducción desde Memoria Interna
- **Objetivo:** Reproducir un archivo de audio almacenado en la RAM del ESP32-S3.
- **Flujo de trabajo:**
  1. **Inicialización:** Configuración del generador de audio (`AudioGeneratorAAC`) y salida I2S (`AudioOutputI2S`).
  2. **Carga de datos:** Audio desde memoria PROGMEM (`AudioFileSourcePROGMEM`).
  3. **Reproducción:** Uso de `aac->loop()` para mantener el flujo de audio.
- **Resultados:**  
  El sistema reprodujo correctamente el audio muestreado, con salida serial indicando el estado del generador.

### Ejercicio 2: Reproducción desde Tarjeta SD
- **Objetivo:** Reproducir un archivo WAV almacenado en una tarjeta SD.
- **Flujo de trabajo:**
  1. **Inicialización:** Configuración de pines SPI para la SD y pines I2S para el amplificador.
  2. **Carga de archivo:** Lectura del archivo WAV desde la SD (`audio.connecttoFS(SD, "archivo.wav")`).
  3. **Manejo de eventos:** Callbacks para metadata (`audio_id3data`), fin de archivo (`audio_eof_mp3`), etc.
- **Resultados:**  
  El archivo WAV se reprodujo sin pérdida de calidad, con información de depuración (bitrate, metadatos) mostrada en el monitor serial.

---

## Conclusiones
- El protocolo I2S es esencial para aplicaciones de audio digital, garantizando transmisión sincronizada y sin pérdidas.
- El amplificador MAX98357 simplifica el diseño al integrar DAC y amplificación en un solo módulo.
- El ESP32-S3 es la plataforma ideal para proyectos de audio, dada su compatibilidad con I2S y capacidad para manejar tarjetas SD.
