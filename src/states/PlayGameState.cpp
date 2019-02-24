#include "PlayGameState.h"
#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

  (void)machine;

  this->victims[0].init();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void PlayGameState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
	auto pressed = arduboy.pressedButtons();


  // Update victim positions ..

  if (arduboy.everyXFrames(5)) {

    for (uint8_t i = 0; i < VICTIMS_MAX_NUMBER; i++) {

      if (this->victims[i].getEnabled()) {
        this->victims[i].move();
      }

    }

  }

  if (arduboy.everyXFrames(15)) {

    for (uint8_t i = 0; i < VICTIMS_MAX_NUMBER; i++) {

      if (this->victims[i].getEnabled()) {
        this->victims[i].rotate();
      }

    }

  }


  // Update player position ..

  if (pressed & LEFT_BUTTON && this->player.getX() > PLAYER_MIN_X_POS)    this->player.decX();
  if (pressed & RIGHT_BUTTON && this->player.getX() < PLAYER_MAX_X_POS)   this->player.incX();

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  Sprites::drawExternalMask(0, 41, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);
  Sprites::drawExternalMask(81, 0, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);
  

  // Render victims ..

  for (uint8_t i = 0; i < VICTIMS_MAX_NUMBER; i++) {

    Victim &victim = this->victims[i];

    if (this->victims[i].getEnabled()) {

      Sprites::drawExternalMask(victim.getX(), victim.getY(), (uint8_t *)pgm_read_word_near(&Images::Victims[victim.getRotation()]), (uint8_t *)pgm_read_word_near(&Images::Victims_Mask[victim.getRotation()]), 0, 0);

    }

  }

  uint8_t i = 0;



  Sprites::drawExternalMask(this->player.getX(), this->player.getY(), (uint8_t *)pgm_read_word_near(&Images::Firemen[i]), (uint8_t *)pgm_read_word_near(&Images::Firemen_Mask[i]), 0, 0);

  Sprites::drawExternalMask(96, 31, Images::Ambulance, Images::Ambulance_Mask, 0, 0);

}
