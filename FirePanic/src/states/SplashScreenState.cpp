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

    this->counter = 20;

  }

  if (justPressed > 0 && this->counter == 0) {

    this->counter = 1;

  }

  if (this->counter > 0) {

    this->counter++;

    if (this->counter == 21) machine.changeState(GameStateType::TitleScreen, GameStateType::None); 

  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SplashScreenState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  Sprites::drawOverwrite(32, 17, Images::PPOT, 0);

  uint8_t y = 17; // Default pixel position 1 is hidden in the top line of the image
  switch (arduboy.getFrameCount(48)) {

      case 12 ... 23:
          y = 30; // Move pixel down to position 2
          /*-fallthrough*/
      case 0 ... 11:
          Sprites::drawOverwrite(91, 25, Images::PPOT_Arrow, 0); // Flash 'Play' arrow
          break;

      case 24 ... 35:
          y = 31; // Move pixel down to position 3
          break;

      default: // 36 ... 47:
          y = 32; // Move pixel down to position 4
          break;

  }

  arduboy.drawPixel(52, y, WHITE); // Falling pixel represents the tape spooling
  if (y % 2 == 0) { // On even steps of pixel movement, update the spindle image
      Sprites::drawOverwrite(45, 28, Images::PPOT_Spindle, 0);
  }

	arduboy.display(true);

}
