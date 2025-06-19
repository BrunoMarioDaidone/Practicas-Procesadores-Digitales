#ifndef NIMBLE2902_H
#define NIMBLE2902_H

#include "NimBLEDescriptor.h"
#include "NimBLEUUID.h"

// Si no están definidos, definimos los permisos (estos valores son típicos)
#ifndef NIMBLE_ATT_READ
#define NIMBLE_ATT_READ  0x0002
#endif

#ifndef NIMBLE_ATT_WRITE
#define NIMBLE_ATT_WRITE 0x0008
#endif

class NimBLE2902 : public NimBLEDescriptor {
public:
    NimBLE2902();
};

NimBLE2902::NimBLE2902()
    : NimBLEDescriptor(
         NimBLEUUID((uint16_t)0x2902),         // UUID para CCCD
         NIMBLE_ATT_READ | NIMBLE_ATT_WRITE,   // Permisos de lectura y escritura
         2,                                    // Longitud del descriptor (2 bytes)
         nullptr                             // Se dejará asignar el puntero a la característica posteriormente
      )
{
}

#endif // NIMBLE2902_H
