#include "TitleScreenState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"

constexpr const static uint8_t PRESS_A_DELAY = 200;
constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;
  gameStats.resetGame();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void TitleScreenState::update(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();


	// Restart ?

	if (pressed & DOWN_BUTTON) {

		if (restart < UPLOAD_DELAY) {
			restart++;
		}
		else {
			arduboy.exitToBootloader();
		}

	}
	else {
		restart = 0;
	}


	// Handle other input ..

	if (justPressed & A_BUTTON) {
		machine.changeState(GameStateType::GameIntroScreen, GameStateType::PlayGameScreen); 
	}


  // Update flame counter.

  if (arduboy.everyXFrames(15)) {

    this->flameCounter++;
    if (this->flameCounter == 3) this->flameCounter = 0;

  }


  // Help !

  if (arduboy.everyXFrames(80)) {

    this->help = !this->help;

  }


  // Update 'Press A' counter / delay ..

  if (this->pressACounter < PRESS_A_DELAY) this->pressACounter++;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;

//	SpritesB::drawOverwrite(0, 0, Images::FirePanic, 0);
  Sprites::drawExternalMask(0, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  Sprites::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);
  Sprites::drawExternalMask(0, 59, Images::Grass, Images::Grass_Mask, 0, 0);  
  Sprites::drawOverwrite(112, 0, Images::Building_RHS, 0);
  
  Sprites::drawExternalMask(33, 1, Images::FirePanic_Logo, Images::FirePanic_Logo_Mask, 0, 0);
  Sprites::drawSelfMasked(42, 13, Images::FirePanic_Logo_Anim, this->flameCounter);

  if (this->pressACounter == PRESS_A_DELAY) {

    Sprites::drawExternalMask(43, 52, Images::PressA, Images::PressA_Mask, 0, 0);

  }

  Sprites::drawExternalMask(0, 14, Images::Victim_OnEdge_01, Images::Victim_OnEdge_01_Mask, 0, 0);

  if (this->help) {

    Sprites::drawOverwrite(17, 16, Images::Help, 0);

  }

	arduboy.displayWithBackground(TimeOfDay::Day);

}
