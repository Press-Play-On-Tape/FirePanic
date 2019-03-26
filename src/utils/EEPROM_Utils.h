#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

namespace EEPROM_Utils {

  void initEEPROM(bool forceClear);
  void getName(char (&name)[NAME_LENGTH + 1], uint8_t startLoc);
  uint16_t getHighScore(uint8_t startLoc);
  uint8_t saveScore(uint16_t score);
  void saveChar(int8_t slotIdx, uint8_t charIdx, uint8_t newChar);

};

