# Informe de la Práctica de Laboratorio 5: Buses de Comunicación I (I2C)

## Introducción

La práctica tuvo como objetivo principal comprender el funcionamiento del bus **I2C**, un protocolo de comunicación ampliamente utilizado en sistemas embebidos. A través del uso del microcontrolador **ESP32-S3**, se integraron y controlaron dispositivos periféricos como una **pantalla OLED** y un **sensor biométrico MAX30102**, lo cual permitió aplicar los conceptos teóricos del protocolo en una implementación práctica y funcional.

---

## Marco Teórico

### Características del Bus I2C

- **Arquitectura maestro-esclavo:** Un maestro controla la comunicación con uno o más dispositivos esclavos.
- **Conexión física simple:** Utiliza solo dos líneas, SDA (datos) y SCL (reloj), compartidas entre todos los dispositivos del bus.
- **Direccionamiento único:** Cada dispositivo I2C tiene una dirección única de 7 bits, permitiendo la conexión de hasta 112 dispositivos diferentes en el mismo bus.
- **Velocidad de transmisión:** El estándar básico opera a 100 kHz, aunque existen modos rápidos de hasta 400 kHz o superiores.

Este protocolo es ideal para aplicaciones donde se requiera comunicación eficiente y con pocos pines, como es común en sistemas embebidos y dispositivos portátiles.

---

## Desarrollo de la Práctica

La práctica se dividió en tres ejercicios principales para demostrar distintas aplicaciones del bus I2C con el ESP32.

### Ejercicio 1: Escáner I2C

- **Objetivo:** Detectar dispositivos I2C conectados al bus mediante la búsqueda de direcciones activas.
- **Descripción:** Se implementó un escáner que recorre todas las direcciones válidas del protocolo y muestra aquellas que responden.
- **Resultados:** Se identificaron correctamente los dispositivos conectados: la pantalla OLED en la dirección `0x3C` y el sensor MAX30102 en la dirección `0x57`.

---

### Ejercicio 2: Control de Pantalla OLED

- **Objetivo:** Mostrar información gráfica y textual en una pantalla OLED mediante comunicación I2C.
- **Descripción:** Se emplearon librerías específicas para la pantalla, utilizando funciones gráficas para visualizar texto, figuras y datos.
- **Resultados:** La pantalla respondió correctamente a los comandos enviados desde el ESP32, mostrando el contenido programado de forma clara y sin errores de comunicación.

---

### Ejercicio 3: Sensor Biométrico MAX30102

- **Objetivo:** Capturar mediciones de frecuencia cardíaca y saturación de oxígeno en sangre.
- **Descripción:** Se inicializó el sensor mediante I2C, configurando su funcionamiento y lectura de datos provenientes de sus LEDs infrarrojo y rojo.
- **Resultados:** El sensor proporcionó lecturas en tiempo real que fueron mostradas por el monitor serial, evidenciando un correcto funcionamiento y procesamiento básico de las señales biométricas.

---

## Conclusiones

La práctica permitió aplicar los conocimientos teóricos sobre el protocolo I2C en un entorno práctico con hardware real. Se logró:

- Establecer comunicación exitosa con varios dispositivos I2C.
- Visualizar información útil en una pantalla OLED.
- Leer datos biométricos en tiempo real con el sensor MAX30102.

Estos ejercicios demostraron la versatilidad del bus I2C para conectar múltiples dispositivos utilizando un mínimo de conexiones, así como la importancia de una correcta configuración eléctrica y lógica del sistema.

---

## Anexos
- **Foto del funcionamiento del dispaly**
- ![Display](Imagenes_Practicas/DisplayFuncionamiento.jpg)
-  
- **Foto del montaje**
- ![Montaje](Imagenes_Practicas/SensorHyT_Montaje.jpg)
- 
- **Foto del funcionamiento**
- ![Funcionamiento](Imagenes_Practicas/SensorHyT_Funcionamiento.jpg)
---
