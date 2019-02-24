#include "EEPROM_Utils.h"
#include "Arduboy2Ext.h"
#include "Enums.h"

/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'F' and 'A' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */

const char chars1[8] = { 'F', 'i', 'l', 'm', 'o', 't', 'e', ' ' };
const char chars2[8] = { 'V', 'a', 'm', 'p', 'i', 'r', 'i', 'c' };
const char chars3[8] = { 'H', 'e', 'c', 't', 'o', 'r', ' ', ' ' };

const uint8_t letter1 = 'F'; 
const uint8_t letter2 = 'A'; 

void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (forceClear || c1 != letter1 || c2 != letter2) { 

    EEPROM.update(EEPROM_START_C1, letter1);
    EEPROM.update(EEPROM_START_C2, letter2);

    for (uint8_t x = EEPROM_PLAYER1; x <= EEPROM_END; x++) {

      EEPROM.update(x, 0);

    }

    for (uint8_t x = EEPROM_PLAYER1 + 1, y = 0; x < EEPROM_PLAYER2 - 1; x++, y++) {

      EEPROM.update(x, 32);
      EEPROM.update(x + 10, 32);
      EEPROM.update(x + 20, 32);
      EEPROM.update(x + 30, 32);

      EEPROM.update(x + 39, chars1[y]);
      EEPROM.update(x + 49, chars2[y]);
      EEPROM.update(x + 59, chars3[y]);

    }

    int16_t score = 150;
    EEPROM.put(EEPROM_HS_SCORE_1, score);
    score = 100;
    EEPROM.put(EEPROM_HS_SCORE_1 + 2, score);
    score = 50;
    EEPROM.put(EEPROM_HS_SCORE_1 + 4, score);

  }

}


/* -----------------------------------------------------------------------------
 *   Get name ..
 */
void EEPROM_Utils::getName(char *name, uint8_t startLoc) {

  uint8_t chars[NAME_LENGTH + 1];

  for (uint8_t x = 0; x < NAME_LENGTH; x++) {
    
    chars[x] = EEPROM.read(startLoc + x);

  }

  chars[NAME_LENGTH] = 0;

  memcpy(name, &chars, NAME_LENGTH + 1);

}


/* -----------------------------------------------------------------------------
 *   Get name ..
 */
int16_t EEPROM_Utils::getHighScore(uint8_t startLoc) {

  int16_t score = 0;
  EEPROM.get(startLoc, score);

  return score;

}


static uint8_t EEPROM_Utils::saveScore(char *name, int16_t score) {

  int16_t scores[3];
  uint8_t idx = NO_WINNER;

  for (uint8_t i = 0; i < 3; i++) {

    scores[i] = getHighScore(EEPROM_HS_SCORE_1 + (i*2));

    if (score > scores[i]) {

      idx = i;
      break;

    }

  }


  // New High Score ..

  if (idx < NO_WINNER) {

    for (uint8_t i = 2; i > idx; i--) {

      for (uint8_t j = 0; j < NAME_LENGTH + 1; j++) {

        uint8_t x = EEPROM.read(EEPROM_HS_NAME_1 + ((i - 1) * 10) + j);
        EEPROM.update(EEPROM_HS_NAME_1 + (i * 10) + j, x);

      }

      int16_t score = 0;
      EEPROM.get(EEPROM_HS_SCORE_1 + ((i -1) * 2), score);
      EEPROM.put(EEPROM_HS_SCORE_1 + (i * 2), score);

    }


    // Write out new name and score ..

    for (uint8_t j = 1; j < NAME_LENGTH; j++) {

      EEPROM.update(EEPROM_HS_NAME_1 + (idx * 10) + j - 1, name[j]);

    }

    EEPROM.put(EEPROM_HS_SCORE_1 + (idx * 2), score);

  }

  return idx;

}
