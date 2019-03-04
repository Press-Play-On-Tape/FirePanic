#include "HighScoreState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"

// ----------------------------------------------------------------------------
//  Initialise state ..
//
void HighScoreState::activate(StateMachine & machine) {
	
	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;

	arduboy.setRGBled(0, 0, 0);

	// this->yLeft = -96;
	// this->yRight = 0;
	this->count = 0;

//  uint8_t winner = getWinner(machine);
//  winnerIdx = EEPROM_Utils::saveScore(gameStats.players[winner]->name, gameStats.players[winner]->score);

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


	// Handle other input ..

	if (justPressed & A_BUTTON) {
		machine.changeState(GameStateType::TitleScreen); 
	}

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void HighScoreState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;

	const bool flash = arduboy.getFrameCountHalf(FLASH_FRAME_COUNT_2);

	// SpritesB::drawOverwrite(27, 0, Images::HighScore, 0);

	// SpritesB::drawOverwrite(-4, this->yLeft, Images::Title_Dice_Vert, 0);
	// SpritesB::drawOverwrite(-4, this->yLeft + 96, Images::Title_Dice_Vert, 0);
	// SpritesB::drawOverwrite(103, this->yRight, Images::Title_Dice_Vert_Mirror, 0);
	// SpritesB::drawOverwrite(103, this->yRight + 96, Images::Title_Dice_Vert_Mirror, 0);

#define HS_CHAR_0_LEFT 37
#define HS_SCORE_LEFT 75
#define HS_CHAR_TOP 28
#define HS_CHAR_V_SPACING 9

    uint8_t playerIdx = 2;
    uint8_t charIndex = 1;

		font4x6.setCursor(HS_CHAR_0_LEFT, HS_CHAR_TOP);
		font4x6.print(this->player1);
		renderScore(machine, this->score1, HS_SCORE_LEFT, HS_CHAR_TOP);




		font4x6.setCursor(HS_CHAR_0_LEFT, HS_CHAR_TOP + HS_CHAR_V_SPACING);
		font4x6.print(this->player2);
		renderScore(machine, this->score2, HS_SCORE_LEFT, HS_CHAR_TOP + HS_CHAR_V_SPACING);

		font4x6.setCursor(HS_CHAR_0_LEFT, HS_CHAR_TOP + HS_CHAR_V_SPACING + HS_CHAR_V_SPACING);
		font4x6.print(this->player3);
		renderScore(machine, this->score3, HS_SCORE_LEFT, HS_CHAR_TOP + HS_CHAR_V_SPACING + HS_CHAR_V_SPACING);




    arduboy.fillRect(HS_CHAR_0_LEFT + (charIndex * 6) - 1, HS_CHAR_TOP + (playerIdx * HS_CHAR_V_SPACING), 6, 8, WHITE);
    font4x6.setTextColor(BLACK);

    switch (playerIdx) {

      case 0:
        font4x6.setCursor(HS_CHAR_0_LEFT + (charIndex * 6), HS_CHAR_TOP);
        font4x6.print(this->player1[charIndex]);
        break;

      case 1:
        font4x6.setCursor(HS_CHAR_0_LEFT + (charIndex * 6), HS_CHAR_TOP + HS_CHAR_V_SPACING);
        font4x6.print(this->player2[charIndex]);
        break;

      case 2:
        font4x6.setCursor(HS_CHAR_0_LEFT + (charIndex * 6), HS_CHAR_TOP + HS_CHAR_V_SPACING + HS_CHAR_V_SPACING);
        font4x6.print(this->player3[charIndex]);
        break;

      default: break;

    }
    font4x6.setTextColor(WHITE);


  arduboy.display(true);

}

