# Informe de la Práctica de Laboratorio 4

## Introducción

En este informe se describe el trabajo realizado durante la cuarta práctica del laboratorio, cuyo objetivo fue comprender el funcionamiento de un sistema operativo en tiempo real (RTOS) utilizando el microcontrolador ESP32-S3 y el Visual Studio Code. Esta práctica nos permitió introducirnos en el uso de **FreeRTOS**, un sistema que facilita la ejecución concurrente de múltiples tareas en sistemas embebidos, optimizando el uso de los recursos del procesador.

---

## Configuración Inicial del Entorno

Para comenzar la práctica, se utilizó la placa de desarrollo **ESP32-S3** con soporte para doble núcleo. El entorno de desarrollo fue **Visual Studio Code**, configurado previamente con las herramientas necesarias para soportar la arquitectura del ESP32-S3 (Platform.IO).

Durante la configuración, se habilitó la funcionalidad multitarea que ofrece **FreeRTOS**, integrada de forma nativa en el framework de ESP32 para Arduino. Esto permitió crear y administrar tareas concurrentes, asignar prioridades, y observar cómo el sistema operativo gestiona el tiempo de CPU entre distintas funciones.

---

## Desarrollo de la Práctica

En esta práctica se llevaron a cabo dos ejercicios principales, cuyo objetivo fue aplicar los conceptos teóricos de FreeRTOS a través de ejemplos prácticos.

### Ejercicio Práctico 1

Se desarrolló un programa que incluye dos tareas independientes:
- Una tarea principal que imprime un mensaje a través del puerto serie cada cierto tiempo.
- Una segunda tarea que también imprime un mensaje distinto de forma periódica, pero que es creada y controlada mediante FreeRTOS.

Este ejercicio permitió observar el comportamiento concurrente de ambas tareas, verificando que el sistema operativo divide el tiempo de procesamiento y ejecuta ambas funciones de manera coordinada. Se analizó también el impacto de las prioridades asignadas a cada tarea en el orden de ejecución.

---

### Ejercicio Práctico 2 (Ejercicio para casa)

El segundo ejercicio consiste en diseñar un sistema con dos tareas sincronizadas:
- Una tarea debe encargarse de **encender un LED**.
- La otra debe encargarse de **apagar el mismo LED**.

Estas tareas deben trabajar de forma coordinada, de manera que no interfieran entre sí. Para lograr esta sincronización, se debe utilizar un mecanismo de FreeRTOS llamado **semáforo**, que permite controlar el acceso compartido a un recurso (en este caso, el LED).


---

## Conclusiones

Esta práctica fue fundamental para introducirnos en los conceptos de sistemas operativos en tiempo real aplicados a microcontroladores. Aprendimos a estructurar aplicaciones multitarea utilizando FreeRTOS y a sincronizar procesos mediante semáforos.

Además, entendimos cómo FreeRTOS organiza el tiempo de CPU entre varias tareas y la importancia de asignar correctamente las prioridades para garantizar el funcionamiento correcto del sistema.

Este conocimiento resulta clave para el desarrollo de aplicaciones IoT complejas, donde múltiples procesos deben ejecutarse en paralelo sin interferirse entre sí.

---
