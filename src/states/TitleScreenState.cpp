#include "TitleScreenState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"

constexpr const static uint8_t PRESS_A_DELAY = 200;
constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate(StateMachine & machine) {

	(void)machine;

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
		machine.changeState(GameStateType::GameIntroScreen); 
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

	SpritesB::drawOverwrite(0, 0, Images::FirePanic, 0);
  Sprites::drawSelfMasked(33, 1, Images::FirePanic_Logo_Anim, this->flameCounter);

  if (this->pressACounter == PRESS_A_DELAY) {

    Sprites::drawExternalMask(43, 52, Images::PressA, Images::PressA_Mask, 0, 0);

  }

  if (this->help) {

    Sprites::drawOverwrite(18, 16, Images::Help, 0);

  }

	arduboy.display(true);

}
