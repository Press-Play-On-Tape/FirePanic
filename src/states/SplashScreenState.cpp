#include "SplashScreenState.h"
#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void SplashScreenState::activate(StateMachine & machine) {

  (void)machine;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void SplashScreenState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
	auto justPressed = arduboy.justPressedButtons();

  if (justPressed > 0 && this->counter > 0) {

    this->counter = 124;

  }

  if (justPressed > 0 && this->counter == 0) {

    this->counter = 1;

  }

  if (this->counter > 0) {

    this->counter++;

    if (this->counter == 125) machine.changeState(GameStateType::TitleScreen, GameStateType::None); 

  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SplashScreenState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  arduboy.drawCompressed(47, 17, Images::Ppot_Buttons, WHITE);
  arduboy.drawCompressed(43, 26, Images::Ppot_ButtonUp, WHITE);
  arduboy.drawCompressed(73, 26, Images::Ppot_ButtonUp, WHITE);

  if (this->counter == 0) {

    arduboy.drawCompressed(58, 26, Images::Ppot_ButtonUp, WHITE);
    arduboy.drawCompressed(26, 46, Images::Ppot_Caption, WHITE);

  }
  else {

    arduboy.drawCompressed(58, 26, Images::Ppot_ButtonDown, WHITE);
    arduboy.drawCompressed(44, 46, Images::Ppot_Loading, WHITE);

    uint8_t i = (this->counter / 15) % 4;

    for (uint8_t j = 0; j < i; j++) {
      
        arduboy.drawPixel(79 + (j * 2), 49, WHITE);

    }

  }

	arduboy.display(true);

}
