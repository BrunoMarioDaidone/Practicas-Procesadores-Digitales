#include "OLED_DISPLAY.h"

OLED_DISPLAY::OLED_DISPLAY(uint8_t address) 
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), i2cAddress(address) {}

bool OLED_DISPLAY::begin() {
    Wire.begin(I2C_SDA, I2C_SCL);
    display.print("");
    if (!display.begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }
    display.clearDisplay();
    return true;
}

void OLED_DISPLAY::InverColor(bool type){
    display.invertDisplay(type); 
}
String blinkMessage = "DEFAULT TEXT";

void OLED_DISPLAY::changetext(const String &text) {
    blinkMessage = text; // Update object's variable
}
void OLED_DISPLAY::blinkTask(void *pvParameters) {
    OLED_DISPLAY *oled = static_cast<OLED_DISPLAY *>(pvParameters); // Get OLED instance
    while (true) {
        oled->showMessage(oled->blinkMessage, 10, 1, 2); // Use object's variable
        vTaskDelay(pdMS_TO_TICKS(500));
        oled->showMessage("     ", 10, 1, 2);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


void OLED_DISPLAY::showMessage(const String &message, const int x, const int y, const int size){
    display.clearDisplay();
    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.setCursor(x, y);
    display.println(message);
    display.display();
}

