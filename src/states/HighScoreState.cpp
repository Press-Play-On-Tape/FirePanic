#include "HighScoreState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"

// ----------------------------------------------------------------------------
//  Initialise state ..
//
void HighScoreState::activate(StateMachine & machine) {
	
	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;

  this->charIdx = 0;
  this->clearScores = 0;
  this->pressACounter = HS_PRESS_A_DELAY;
  this->winnerIdx = EEPROM_Utils::saveScore(gameStats.score);

	arduboy.setRGBled(0, 0, 0);
  arduboy.clearButtonState();


  // Retrieve existing names and scores ..

  EEPROM_Utils::getName(this->player1, EEPROM_HS_NAME_1);
  EEPROM_Utils::getName(this->player2, EEPROM_HS_NAME_2);
  EEPROM_Utils::getName(this->player3, EEPROM_HS_NAME_3);

  this->score1 = EEPROM_Utils::getHighScore(EEPROM_HS_SCORE_1);
  this->score2 = EEPROM_Utils::getHighScore(EEPROM_HS_SCORE_2);
  this->score3 = EEPROM_Utils::getHighScore(EEPROM_HS_SCORE_3);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void HighScoreState::update(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();


  // Is the new score a high score ?

  if (this->winnerIdx < NO_WINNER) {

    if (arduboy.everyXFrames(12)) {

      if (pressed & UP_BUTTON) {

        char *player = this->players[this->winnerIdx];
        player[this->charIdx]++;
        if (player[this->charIdx] > 90) player[this->charIdx] = 65;
        if (player[this->charIdx] == 64) player[this->charIdx] = 65;

      }

      if (pressed & DOWN_BUTTON) {

        char *player = this->players[this->winnerIdx];
        player[this->charIdx]--;
        if (player[this->charIdx] < 65) player[this->charIdx] = 90;
        if (player[this->charIdx] == 62) player[this->charIdx] = 90;

      }

      if (pressed & LEFT_BUTTON && this->charIdx > 0) {
        this->charIdx--;
      }

      if (pressed & RIGHT_BUTTON && this->charIdx < 2) {
        this->charIdx++;
      }

      if (pressed & A_BUTTON) {

        char *player = this->players[this->winnerIdx];

        if (player[0] != 63 && player[1] != 63 && player[2] != 63) {
          
          for (uint8_t i = 0; i < 3; i++) {
            EEPROM_Utils::saveChar(this->winnerIdx, i, player[i]);
          }
          
          this->winnerIdx = NO_WINNER;
          this->pressACounter = HS_PRESS_A_DELAY;

        }

      }

    }

  }
  else {


    // Handle other input ..

    if (justPressed & A_BUTTON && this->pressACounter == 0) {

      machine.changeState(GameStateType::TitleScreen, GameStateType::None); 
    }

  }


	// Clear scores ..

	if ((pressed & UP_BUTTON) && (pressed & DOWN_BUTTON)) {

		clearScores++;

		switch (clearScores) {

			case 21 ... 60:

				arduboy.setRGBled(128 - (clearScores * 2), 0, 0);
				break;

			case 61:

				clearScores = 0;
				arduboy.setRGBled(0, 0, 0);
				EEPROM_Utils::initEEPROM(true);

				EEPROM_Utils::getName(this->player1, EEPROM_HS_NAME_1);
				EEPROM_Utils::getName(this->player2, EEPROM_HS_NAME_2);
				EEPROM_Utils::getName(this->player3, EEPROM_HS_NAME_3);

				this->score1 = EEPROM_Utils::getHighScore(EEPROM_HS_SCORE_1);
				this->score2 = EEPROM_Utils::getHighScore(EEPROM_HS_SCORE_2);
				this->score3 = EEPROM_Utils::getHighScore(EEPROM_HS_SCORE_3);

				break;

		}

	}
	else {

		if (clearScores > 0) {
		
			arduboy.setRGBled(0, 0, 0);
			clearScores = 0;

		}
		
	}


  // Decrement the 'Press A' counter if it has been set ..

  if (this->pressACounter > 0) pressACounter--;

}


void HighScoreState::renderHighScore(int16_t score, uint8_t x, uint8_t y) {
  
  for (uint8_t j = 6, x2 = x - 4; j > 0; --j, x2 += 5) {
    
    uint8_t digits[6] = {};
    extractDigits(digits, static_cast<uint16_t>(absT(score)));

    font4x6.setCursor(x2, y);
    font4x6.print(digits[j - 1]);

  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void HighScoreState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;

	const bool flash = arduboy.getFrameCountHalf(FLASH_FRAME_COUNT_2);

  BaseState::renderCommonScenery(machine, false, true);
  SpritesB::drawExternalMask(31, 3, Images::HighscoreText, Images::HighscoreText_Mask, 0, 0);
  SpritesB::drawExternalMask(29, 16, Images::HighscorePanel, Images::HighscorePanel_Mask, 0, 0);
  


  // Render scores ..

  font4x6.setCursor(HS_NAME_LEFT - 2, HS_CHAR_TOP);
  font4x6.print(this->player1);
  renderHighScore(this->score1, HS_SCORE_LEFT, HS_CHAR_TOP);

  font4x6.setCursor(HS_NAME_LEFT - 2, HS_CHAR_TOP + HS_CHAR_V_SPACING);
  font4x6.print(this->player2);
  renderHighScore(this->score2, HS_SCORE_LEFT, HS_CHAR_TOP + HS_CHAR_V_SPACING);

  font4x6.setCursor(HS_NAME_LEFT - 2, HS_CHAR_TOP + HS_CHAR_V_SPACING + HS_CHAR_V_SPACING);
  font4x6.print(this->player3);
  renderHighScore(this->score3, HS_SCORE_LEFT, HS_CHAR_TOP + HS_CHAR_V_SPACING + HS_CHAR_V_SPACING);



  // Render edit field if the slot is being editted ..

  if (this->winnerIdx < NO_WINNER && flash) {

    char *player = this->players[this->winnerIdx];

    arduboy.fillRect(HS_NAME_LEFT - 2 + (this->charIdx * 6) - 1, HS_CHAR_TOP + (winnerIdx * HS_CHAR_V_SPACING), 6, 8, WHITE);
    font4x6.setTextColor(BLACK);
    font4x6.setCursor(HS_NAME_LEFT - 2 + (this->charIdx * 6), HS_CHAR_TOP + (HS_CHAR_V_SPACING * this->winnerIdx));
    font4x6.print(player[this->charIdx]);
    font4x6.setTextColor(WHITE);

  }



  // Display Press A message?

  if (this->winnerIdx == NO_WINNER && this->pressACounter == 0) {

    SpritesB::drawExternalMask(43, 52, Images::PressA, Images::PressA_Mask, 0, 0);

  }

  arduboy.displayWithBackground(TimeOfDay::Day);

}