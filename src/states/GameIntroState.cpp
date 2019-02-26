#include "GameIntroState.h"
#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void GameIntroState::activate(StateMachine & machine) {

  (void)machine;
  this->counter = 0;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void GameIntroState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
	auto justPressed = arduboy.justPressedButtons();

  if (arduboy.everyXFrames(2)) {

    switch (counter) {

      case 0 ... 59:
        this->xAmbulance--;
        if (arduboy.everyXFrames(8)) {
          this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
        }
        break;

      case 60 ... 90:
        if (arduboy.everyXFrames(8)) {
          this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
        }
        break;

      case 91 ... 140:
        this->lights = LightsState::None;
        this->ambulanceDoor = true;
        break;

      case 141 ... 190:
        this->ambulanceDoor = false;
        break;

      case 191:
        machine.changeState(GameStateType::PlayGameScreen); 
        break;

    }
    this->counter++;

  }

  // Skip intro ..
  
  if (justPressed & A_BUTTON) machine.changeState(GameStateType::PlayGameScreen); 

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void GameIntroState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  Sprites::drawExternalMask(0, 41, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);
  Sprites::drawExternalMask(81, 0, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);
  
  Sprites::drawExternalMask(xAmbulance, 31, Images::Ambulance, Images::Ambulance_Mask, 0, 0);

  switch (this->lights) {

    case LightsState::Lights_1:
      Sprites::drawSelfMasked(this->xAmbulance + 16, 28, Images::Ambulance_Lights_01, 0);
      break;

    case LightsState::Lights_2:
      Sprites::drawSelfMasked(this->xAmbulance + 16, 28, Images::Ambulance_Lights_02, 0);
      break;

  }

  if (this->ambulanceDoor) {
    Sprites::drawExternalMask(this->xAmbulance - 8, 30, Images::Ambulance_Door, Images::Ambulance_Door_Mask, 0, 0);
  }

}
