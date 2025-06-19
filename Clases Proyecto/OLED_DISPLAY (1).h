#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define I2C_SDA       20
#define I2C_SCL       21

class OLED_DISPLAY {
public:
    OLED_DISPLAY(uint8_t address);

    bool begin();
    void showMessage(const String &message, const int x, const int y, const int size);
    static void blinkTask(void *pvParameters);
    void changetext(const String &text);
    void InverColor(bool type);
    TaskHandle_t blinkTaskHandle = NULL;
    String blinkMessage = "DEFAULT TEXT";

private:
    uint8_t i2cAddress;
    Adafruit_SSD1306 display;
};

#endif // OLED_DISPLAY_H
