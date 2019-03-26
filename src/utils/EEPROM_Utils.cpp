#include "EEPROM_Utils.h"
#include "Arduboy2Ext.h"
#include "Enums.h"

#include <avr/eeprom.h>

/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'F' and 'P' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */

constexpr uint8_t letter1 = 'F';
constexpr uint8_t letter2 = 'P';

namespace EEPROM_Utils {

  void initEEPROM(bool forceClear) {

    uint8_t * eepromStartChar1 = reinterpret_cast<uint8_t *>(EEPROM_START_C1);
    uint8_t * eepromStartChar2 = reinterpret_cast<uint8_t *>(EEPROM_START_C2);

    uint8_t * eepromHSName1 = reinterpret_cast<uint8_t *>(EEPROM_HS_NAME_1);
    uint8_t * eepromHSName2 = reinterpret_cast<uint8_t *>(EEPROM_HS_NAME_2);
    uint8_t * eepromHSName3 = reinterpret_cast<uint8_t *>(EEPROM_HS_NAME_3);
    uint8_t * eepromEnd = reinterpret_cast<uint8_t *>(EEPROM_END);

    const byte c1 = eeprom_read_byte(eepromStartChar1);
    const byte c2 = eeprom_read_byte(eepromStartChar2);

    if (!forceClear && (c1 == letter1) && (c2 == letter2)) {

      return;

    }

    eeprom_update_byte(eepromStartChar1, letter1);
    eeprom_update_byte(eepromStartChar2, letter2);

    for (uint8_t * x = eepromHSName1; x <= eepromEnd; ++x) {

      eeprom_update_byte(x, 0);

    }

    for (uint8_t x = 0; x < 3; ++x) {

      eeprom_update_byte(&eepromHSName1[x], 'A');
      eeprom_update_byte(&eepromHSName2[x], 'B');
      eeprom_update_byte(&eepromHSName3[x], 'C');

    }

    uint16_t * eepromHSScore1 = reinterpret_cast<uint16_t *>(EEPROM_HS_SCORE_1);
    uint16_t * eepromHSScore2 = reinterpret_cast<uint16_t *>(EEPROM_HS_SCORE_2);
    uint16_t * eepromHSScore3 = reinterpret_cast<uint16_t *>(EEPROM_HS_SCORE_3);

    eeprom_update_word(eepromHSScore1, 0);
    eeprom_update_word(eepromHSScore2, 0);
    eeprom_update_word(eepromHSScore3, 0);

  }


  /* -----------------------------------------------------------------------------
   *   Get name ..
   */
  void getName(char (&name)[NAME_LENGTH + 1], uint8_t startLoc) {

    const void * sourcePointer = reinterpret_cast<const void *>(startLoc);
    eeprom_read_block(name, sourcePointer, (NAME_LENGTH - 1));

    name[NAME_LENGTH] = '\0';

  }


  /* -----------------------------------------------------------------------------
   *   Get name ..
   */
  uint16_t getHighScore(uint8_t startLoc) {

    const uint16_t * scoreAddresss = reinterpret_cast<const uint16_t *>(startLoc);
    return eeprom_read_word(scoreAddresss);

  }


  /* -----------------------------------------------------------------------------
   *   Save score if it is in the top 3, return slot number (or NO_WINNER) ..
   */
  uint8_t saveScore(uint16_t newScore) {

    uint8_t idx = NO_WINNER;
    uint16_t * const eepromHSScore1 = reinterpret_cast<const uint16_t *>(EEPROM_HS_SCORE_1);

    for (uint8_t i = 0; i < 3; ++i) {

      const uint16_t oldScore = eeprom_read_word(&eepromHSScore1[i]);

      if (newScore >= oldScore) {

        return i;

      }

    }


    // New High Score ..

    uint8_t * const eepromHSName1 = reinterpret_cast<uint8_t *>(EEPROM_HS_NAME_1);

    if (idx < NO_WINNER) {

      for (uint8_t i = 2; i > idx; --i) {

        const size_t previousIndex = (i - 1);
        const size_t sourceBaseIndex = (previousIndex * NAME_LENGTH_PLUS_TERM);
        const size_t destinationBaseIndex = (i * NAME_LENGTH_PLUS_TERM);

        for (uint8_t j = 0; j < NAME_LENGTH_PLUS_TERM; ++j) {

          const uint8_t x = eeprom_read_byte(&eepromHSName1[sourceBaseIndex + j]);
          eeprom_update_byte(&eepromHSName1[destinationBaseIndex + j], x);

        }

        const uint16_t score = eeprom_read_word(&eepromHSScore1[previousIndex]);
        eeprom_update_word(&eepromHSScore1[i], score);

      }


      // Write out new name and score ..

      for (uint8_t j = 0; j < NAME_LENGTH_PLUS_TERM; j++) {

        eeprom_update_byte(&eepromHSName1[(idx * NAME_LENGTH_PLUS_TERM) + j], '?');

      }

      eeprom_write_word(&eepromHSScore1[idx], newScore);

    }

    return idx;

  }

  void saveChar(int8_t slotIdx, uint8_t charIdx, uint8_t newChar) {

    uint8_t * const eepromHSName1 = reinterpret_cast<uint8_t *>(EEPROM_HS_NAME_1);
    const size_t index = ((slotIdx * NAME_LENGTH_PLUS_TERM) + charIdx);
    eeprom_update_byte(&eepromHSName1[index], newChar);

  }

}