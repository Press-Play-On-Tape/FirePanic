#include "EEPROM_Utils.h"
#include "Arduboy2Ext.h"
#include "Enums.h"

/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'F' and 'P' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */

const char chars1[4] = { 'A', 'A', 'A', ' ' };
const char chars2[4] = { 'B', 'B', 'B', ' ' };
const char chars3[4] = { 'C', 'C', 'C', ' ' };

const uint8_t letter1 = 'F'; 
const uint8_t letter2 = 'P'; 

void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (forceClear || c1 != letter1 || c2 != letter2) { 

    EEPROM.update(EEPROM_START_C1, letter1);
    EEPROM.update(EEPROM_START_C2, letter2);

    for (uint8_t x = EEPROM_HS_NAME_1; x <= EEPROM_END; x++) {

       EEPROM.update(x, 0);

    }

    for (uint8_t x = 0; x < 3; x++) {

      EEPROM.update(EEPROM_HS_NAME_1 + x, chars1[x]);
      EEPROM.update(EEPROM_HS_NAME_2 + x, chars2[x]);
      EEPROM.update(EEPROM_HS_NAME_3 + x, chars3[x]);

    }

    int16_t score = 0;
    EEPROM.put(EEPROM_HS_SCORE_1, score);
    EEPROM.put(EEPROM_HS_SCORE_2, score);
    EEPROM.put(EEPROM_HS_SCORE_3, score);

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


/* -----------------------------------------------------------------------------
 *   Save score if it is in the top 3, return slot number (or NO_WINNER) .. 
 */
static uint8_t EEPROM_Utils::saveScore(int16_t score) {

  int16_t scores[3];
  uint8_t idx = NO_WINNER;

  for (uint8_t i = 0; i < 3; i++) {

    scores[i] = getHighScore(EEPROM_HS_SCORE_1 + (i * 2));

    if (score >= scores[i]) {

      idx = i;
      break;

    }

  }


  // New High Score ..

  if (idx < NO_WINNER) {

    for (uint8_t i = 2; i > idx; i--) {

      for (uint8_t j = 0; j < NAME_LENGTH_PLUS_TERM; j++) {

        uint8_t x = EEPROM.read(EEPROM_HS_NAME_1 + ((i - 1) * NAME_LENGTH_PLUS_TERM) + j);
        EEPROM.update(EEPROM_HS_NAME_1 + (i * NAME_LENGTH_PLUS_TERM) + j, x);

      }

      int16_t score = 0;
      EEPROM.get(EEPROM_HS_SCORE_1 + ((i -1) * 2), score);
      EEPROM.put(EEPROM_HS_SCORE_1 + (i * 2), score);

    }


    // Write out new name and score ..

    for (uint8_t j = 0; j < NAME_LENGTH_PLUS_TERM; j++) {

      EEPROM.update(EEPROM_HS_NAME_1 + (idx * NAME_LENGTH_PLUS_TERM) + j, '?');

    }

    EEPROM.put(EEPROM_HS_SCORE_1 + (idx * 2), score);

  }

  return idx;

}

static void EEPROM_Utils::saveChar(int8_t slotIdx, uint8_t charIdx, uint8_t newChar) {

  EEPROM.update(EEPROM_HS_NAME_1 + (slotIdx * NAME_LENGTH_PLUS_TERM) + charIdx, newChar);

}