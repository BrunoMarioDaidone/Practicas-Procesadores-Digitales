# Informe de la Práctica de Laboratorio 2

## Introducción

En este informe se detalla el trabajo realizado durante la segunda práctica del laboratorio, cuyo objetivo principal fue estudiar y experimentar con diferentes tipos de interrupciones programables en la placa Arduino ESP32-S3. Las interrupciones son fundamentales para la gestión eficiente de eventos en sistemas embebidos, permitiendo responder rápidamente a señales externas o internas.

---

## Objetivos de la Práctica

La práctica se dividió en dos actividades principales, cada una enfocada en un tipo distinto de interrupción:

1. **Interrupción por GPIO (General Purpose Input/Output)**
2. **Interrupción por temporizador (Timer Interrupt)**

---

## Actividad 1: Interrupción por GPIO

En esta actividad, realizamos un montaje sencillo en el que un pulsador estaba conectado a un pin GPIO específico de la placa. El objetivo era configurar una interrupción que se activara cuando el pulsador fuera presionado.

- **Montaje:**  
  El pulsador se conectó al pin designado de la placa ESP32-S3.
  
- **Funcionamiento:**  
  La interrupción se activaba mientras el pulsador permaneciera presionado, y el programa podía detectar la duración de la pulsación para ejecutar acciones específicas.

Este tipo de interrupción es útil para detectar eventos externos inmediatos, como la interacción del usuario con un dispositivo.

---

## Actividad 2: Interrupción por Temporizador

La segunda parte de la práctica consistió en configurar una interrupción basada en un temporizador interno del microcontrolador.

- **Configuración:**  
  Se programó un temporizador para que generara una interrupción periódica cada 'x' segundos, con una duración de 'y' segundos.

- **Funcionamiento:**  
  Cada vez que ocurría la interrupción, se podía ejecutar una función determinada, permitiendo realizar tareas periódicas sin la necesidad de usar retardos (delays) que bloquean el flujo del programa.

Esta técnica es esencial para la ejecución eficiente y precisa de tareas repetitivas en sistemas embebidos.

---

## Conclusiones

La práctica nos permitió comprender la importancia y el funcionamiento de las interrupciones en sistemas embebidos. La interrupción por GPIO demostró cómo responder a eventos externos de forma inmediata, mientras que la interrupción por temporizador mostró cómo programar tareas periódicas sin afectar el rendimiento general del programa.
