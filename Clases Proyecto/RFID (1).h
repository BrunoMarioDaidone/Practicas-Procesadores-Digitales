#ifndef RFID_H
#define RFID_H

#include <MFRC522.h>
#include <Preferences.h>

class RFID {
public:
    RFID(uint8_t ssPin, uint8_t rstPin);
    void begin();
    bool isCardPresent();
    String getCardUID();

    void store(int & k,String & ID);
    bool ExistID(int & k,String & ID);
    bool Exist();
    void delet(const String & k);
    String findKeyByID(String ID, int maxKeys);
    int updateKeyCount(bool isAdding);
    int countStoredIDs(int maxKeys);
    
private:
    MFRC522 mfrc522;
    Preferences Prefs;
};

#endif
