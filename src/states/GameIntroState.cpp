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


  if (arduboy.everyXFrames(16)) {
  this->smokeIndex++;
  if (this->smokeIndex >= 5) this->smokeIndex = 0;
  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void GameIntroState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	
  Sprites::drawExternalMask(0, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  Sprites::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);
  Sprites::drawExternalMask(0, 59, Images::Grass, Images::Grass_Mask, 0, 0);


  Sprites::drawOverwrite(15, 0, Images::Smoke, this->smokeIndex);



  // Draw Ambulance with lights ..

  Sprites::drawExternalMask(xAmbulance, 31, Images::Ambulance, Images::Ambulance_Mask, 0, 0);

  switch (this->lights) {

    case LightsState::Lights_1:
      Sprites::drawExternalMask(this->xAmbulance + 18, 31, Images::Ambulance_Lights_01, Images::Ambulance_Lights_Mask, 0, 0);
      break;

    case LightsState::Lights_2:
      Sprites::drawExternalMask(this->xAmbulance + 18, 31, Images::Ambulance_Lights_02, Images::Ambulance_Lights_Mask, 0, 0);
      break;

  }

  if (this->ambulanceDoor) {
    Sprites::drawExternalMask(this->xAmbulance - 8, 30, Images::Ambulance_Door, Images::Ambulance_Door_Mask, 0, 0);
  }

  arduboy.displayWithBackground(TimeOfDay::Day);

}
