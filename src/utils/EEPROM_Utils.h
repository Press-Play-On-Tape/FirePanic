#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM(bool forceClear);
    static void getName(char *name, uint8_t startLoc);
    static int16_t getHighScore(uint8_t startLoc);
    static uint8_t saveScore(int16_t score);
    static void saveChar(int8_t slotIdx, uint8_t charIdx, uint8_t newChar);

};

