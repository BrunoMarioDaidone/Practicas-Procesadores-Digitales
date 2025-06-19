#include <Arduino.h>
#include <Preferences.h>
#include "RFID.h"
#include "RELE.h"
#include "JOYSTICK.h"
#include "OLED_DISPLAY.h"
#include "BUZZ.h"
#include "TEMPERATURA.h"
#include "HUMEDAD.h"
#include "BLEManager.h"

    void Seguridad(int & p);
    void LadoM(int & m,int & p);
    void Menu(int & p);
    bool search(String id);

    //JOYSTICK
    bool presion = false;

    //RFID
    bool enter = false;
    String ID;
    int maxStorage = 50;
    int KeyCount;

    //RELE
    #define S_RELE 7

    //RFID
    #define SS_PIN 5
    #define RST_PIN 4

    // HUMEDAD / TEMPERATURA 
    float humedad = 0.0;
    float temperatura = 0.0;
    
    //OLED
    int maxp = 4, max2 = 3, pag = 1, pag2 = 1;
    bool bli = false, m1 = true;

    volatile bool tim = false;

    RELE Crele(S_RELE);
    RFID Crfid(SS_PIN,RST_PIN);
    JOYSTICK Cjoystick(15, 16, 8);
    OLED_DISPLAY Coled_display1(0x3C);
    BUZZ Cbuzz(10);
    TemperaturaDS18B20 Ctemp(6);
    HumedadSuelo  Chumedad(3);
    BLEManager bleManager;

bool search(String id){
    for (int i = 0; i < maxStorage; i++)
    {
        if(Crfid.ExistID(i,id))return true;
    }
    return false;
}

TaskHandle_t ResetTimHandle;

void resetTimTask(void *parameter) {
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(600000)); 
        tim = false;
        Serial.println("tim reset to false!");
        vTaskDelete(ResetTimHandle);
    }
}

TaskHandle_t RiegoTaskHandle;

void riegoTask(void *parameter) {
    while (true) {
        Serial.println("Iniciando riego...");
        
        // Ajuste de tiempo según humedad y temperatura
        int duracionRiego = 5000;  // Tiempo base
        if (humedad < 30 && temperatura > 25) {
            duracionRiego = 10000;  // Riego más largo
        } else if (humedad < 30 && temperatura < 15) {
            duracionRiego = 7000;  // Tiempo medio
        }

        Coled_display1.changetext(" REGANDO");
        Cbuzz.shortRing();
        Crele.open();
        vTaskDelay(pdMS_TO_TICKS(duracionRiego));
        Crele.close();
        Coled_display1.showMessage("TERMINADO", 10, 2, 2);
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Esperar 12 horas antes de regar otra vez
        vTaskDelay(pdMS_TO_TICKS(43200000));  // 12 horas en milisegundos
    }
}



void setup() {
    Serial.begin(115200);
    Crfid.begin();
    Ctemp.iniciar();
    Cjoystick.begin();  
    Coled_display1.begin();
    bleManager.begin(&Crele, &Ctemp, &Chumedad);

    // Creación de la tarea de riego
    xTaskCreate(riegoTask, "RiegoTask", 2048, NULL, 1, &RiegoTaskHandle);
}

void loop() {

        // Parte de la pagina web
   // Leer sensores reales aquí, por ejemplo:
    // float temperaturaReal = leerTemperatura();
    // int humedadReal = leerHumedad();

   bleManager.notify();

        // Hasta aqui
    
    if (enter == false && Crfid.Exist()){
        Coled_display1.showMessage("SHOW ID",10,2,2);
        if(Crfid.isCardPresent()){
            ID = Crfid.getCardUID();
            if (Crfid.findKeyByID(ID,maxStorage) != "Not Found") 
            {
            Coled_display1.showMessage("ENTER",10,1,2);
            Cbuzz.shortRing();
            Serial.println("Correct card detected!");
            enter = true;
            } 
            else if (Crfid.isCardPresent())
            {
            Coled_display1.showMessage("...",10,1,2);
            }
            delay(1000);
        }
    } 
    else {
        if (m1) {
            Menu(pag);
        } else{
            Seguridad(pag2);
        }
        delay(100);
    }

}

void LadoM(int &m, int &p) {
    char Lado = Cjoystick.Lado(Cjoystick.getX(), Cjoystick.getY(), Cjoystick.isPressed());
    if (Lado == 'D' && p < m) { p++; }
    else if (Lado == 'E' && p > 0) { p--; }
    else if (Lado == 'S') { presion = true; }
    else presion = false;

    vTaskDelay(pdMS_TO_TICKS(150));  
}

void Menu(int &p) {
    humedad = Chumedad.porcentaje();
    temperatura = Ctemp.leerTemperatura();
    if (m1) {
        LadoM(maxp, p);
        switch (p) {
            case 1:
                Coled_display1.showMessage(" RIEGO      FORZADO   |- ->", 10, 1, 2);
                
                if (presion) {
                    Crele.open();
                    presion = false;
                    Coled_display1.changetext(" REGANDO");
                    Cbuzz.shortRing();

                    if (Coled_display1.blinkTaskHandle == NULL) {
                        xTaskCreate(OLED_DISPLAY::blinkTask, "BlinkTask", 2048, (void *)&Coled_display1, 1, &Coled_display1.blinkTaskHandle);
                    }
                    vTaskDelay(pdMS_TO_TICKS(5000));  // Avoid blocking

                    Crele.close();
                    Coled_display1.showMessage("TERMINADO", 10, 2, 2);
                    vTaskDelay(pdMS_TO_TICKS(2000));
                } 
                else {
                    if (Coled_display1.blinkTaskHandle != NULL) {
                        vTaskDelete(Coled_display1.blinkTaskHandle);
                        Coled_display1.blinkTaskHandle = NULL;
                    }
                }
                break;

            case 2:
                Coled_display1.showMessage(" HUMEDAD    " + String(humedad) + "%    <- ->", 10, 1, 2);
                break;

            case 3: 
                Coled_display1.showMessage("  TEMP     " + String(temperatura) + "C    <- ->", 10, 1, 2);
                break;

            case 4:
                Coled_display1.showMessage("SEGURIDAD             <- -|", 10, 1, 2);
                if (presion) {
                    m1 = false;
                    Seguridad(pag2);
                }
                break;
            default:
                break;

        }
    }
}

void Seguridad(int &p) {
    if (!m1) {
        LadoM(max2, p);

        switch (p) {
            case 1:
                Coled_display1.showMessage("SALIR", 10, 2, 2);
                if (presion) {
                    m1 = true;
                }
                break;

            case 2:
                Coled_display1.showMessage("ANADIR", 10, 2, 2);
                if(presion){
                    Coled_display1.showMessage(" ACERCA    EL ID", 10, 2, 2);
                    for(int x = 0 ; x < 10 && !Crfid.isCardPresent() ; x++){
                        if(x > 10){Cbuzz.shortRing();Seguridad(pag2);}
                        vTaskDelay(pdMS_TO_TICKS(200));
                    }
                    ID = Crfid.getCardUID();
                    if(Crfid.findKeyByID(ID,maxStorage) != "Not Found"){Coled_display1.showMessage("  EXISTE",10,2,2); delay(500);Cbuzz.longRing();}
                    else{
                    Cbuzz.shortRing();
                    Crfid.store(KeyCount,ID);
                    KeyCount = Crfid.countStoredIDs(maxStorage);
                    Seguridad(pag2);
                }
                }
                break;

            case 3:
                Coled_display1.showMessage("ELIMINAR", 10, 2, 2);
                if(presion){
                    Coled_display1.showMessage(" ACERCA    EL ID", 10, 2, 2);
                    for(int x = 0; x < 10 && !Crfid.isCardPresent() ; x++){
                        if(x > 10){Cbuzz.shortRing();Seguridad(pag2);}
                        vTaskDelay(pdMS_TO_TICKS(200));
                    }
                    if(Crfid.countStoredIDs(maxStorage) == 0){Coled_display1.showMessage("NO EXISTE",10,2,2); delay(500);Cbuzz.longRing();}
                    else{
                    ID = Crfid.getCardUID();
                        if(Crfid.findKeyByID(ID,maxStorage) != "Not Found"){
                            String c = Crfid.findKeyByID(ID,maxStorage);
                            Cbuzz.shortRing();
                            Crfid.delet(c);
                            Seguridad(pag2);
                        //KeyCount = Crfid.updateKeyCount(false);
                        }
                        else{
                            Coled_display1.showMessage("NO EXISTE",10,2,2); delay(500);Cbuzz.shortRing();
                        }
                    }
                    
                }
                break;
        }
    }
}
