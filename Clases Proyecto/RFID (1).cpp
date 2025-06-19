#include "RFID.h"
#include <Arduino.h>
#include <Preferences.h>

RFID::RFID(uint8_t ssPin, uint8_t rstPin) : mfrc522(ssPin, rstPin) {}

void RFID::begin() {
    SPI.begin(18, 19, 11, 5);
    mfrc522.PCD_Init();
    Prefs.begin("Storage", false);
    Prefs.getInt("keyCount", 0);
}

bool RFID::isCardPresent() {
    return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

String RFID::getCardUID() {
    String rfidUID = "";

    for (byte i = 0; i < mfrc522.uid.size; i++) {
        rfidUID += String(mfrc522.uid.uidByte[i], HEX);
        if (i < mfrc522.uid.size - 1) rfidUID += ":";  // Add a separator
    }
    Serial.println("RFID UID: " + rfidUID);
    return rfidUID;
}

void RFID::store(int & k, String & ID){
    Prefs.begin("Storage", false);
    String keyName = "id_" + String(k);
    
    if (!Prefs.isKey(keyName.c_str())) { // Prevent overwriting
        Prefs.putString(keyName.c_str(), ID);
       // int currentCount = Prefs.getInt("keyCount", 0);
       // Prefs.putInt("keyCount", currentCount + 1);
        Serial.println("Added New ID: " + ID);
    } else {
        Serial.println("ID Already Exists!");
    }

    Prefs.end();
}
void RFID::delet(const String & k){
    Prefs.begin("Storage", false);
    
    String keyName = String(k); 
    Serial.println("Attempting to delete key: " + keyName);

    if (Prefs.isKey(keyName.c_str())) {
        Prefs.remove(keyName.c_str());
        //int currentCount = Prefs.getInt("keyCount", 0);
       // Prefs.putInt("keyCount", currentCount - 1);
        Serial.println("Key Removed: " + keyName);
    } else {
        Serial.println("Key Not Found!");
    }

    Prefs.end();
}

bool RFID::ExistID(int & k,String & ID){
    String keyName = "id_" + String(k);
    if(ID == Prefs.getString(keyName.c_str() , "not exist"))return true;
    else return false;
}

bool RFID::Exist(){
    if(Prefs.isKey("id_0")){return true;}
    else {return false;}
}

String RFID::findKeyByID(String ID, int maxKeys) {
    Prefs.begin("Storage", false); // Open Preferences

    for (int i = 0; i < maxKeys; i++) {
         String keyName = "id_" + String(i);
        String storedID = Prefs.getString(keyName.c_str(), "");
        
        if (storedID == ID) {
            Prefs.end(); // Close Preferences
            return keyName.c_str(); // Return matching key
        }
    }

    Prefs.end(); // Close Preferences
    return "Not Found"; // No match found
}

int RFID::updateKeyCount(bool isAdding) {
    Prefs.begin("Storage", false); // Open Preferences

    int currentCount = Prefs.getInt("keyCount", 0); // Get stored count

    // Increase or decrease key count based on operation
    if (isAdding) {
        Prefs.putInt("keyCount", currentCount + 1);
        return currentCount;
        Serial.println("Key Added! New Count: " + String(currentCount + 1));
    } else {
        if (currentCount > 0) { // Prevent negative count
            Prefs.putInt("keyCount", currentCount - 1);
            return currentCount;
            Serial.println("Key Removed! New Count: " + String(currentCount - 1));
        } else {
            Serial.println("Key Count is already 0!");
        }
        return 0;
    }

    Prefs.end(); // Close Preferences
}

int RFID::countStoredIDs(int maxKeys) {
    Prefs.begin("Storage", false); // Open Preferences

    int storedCount = 0; 

    for (int i = 0; i < maxKeys; i++) {
        String keyName = "id_" + String(i); // Construct key
        if (Prefs.isKey(keyName.c_str())) { 
            storedCount++; // Increment count if key exists
        }
    }

    Prefs.end(); // Close Preferences
    return storedCount; // Return number of stored IDs
}
