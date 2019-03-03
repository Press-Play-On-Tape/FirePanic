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


  if (arduboy.everyXFrames(8)) {
    this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
  }
    
  if (arduboy.everyXFrames(2)) {

    switch (counter) {

      case 0 ... 49:
        this->xAmbulance--;
        break;

      case 50 ... 70:
        break;

      case 71 ... 90:
        this->ambulanceDoor = true;
        break;

      case 91 ... 161:
      
        this->ambulanceDoor = true;

        if (arduboy.everyXFrames(4)) {

          switch (this->xPlayer) {

            case PLAYER_MIN_X_POS : break;

            case PLAYER_MIN_X_POS + 1 ... PLAYER_MIN_X_POS + 3:
              this->xPlayer = this->xPlayer - 1;
              break;

            case PLAYER_MIN_X_POS + 4 ... PLAYER_MIN_X_POS + 8:
              this->xPlayer = this->xPlayer - 2;
              break;

            default:
              this->xPlayer = this->xPlayer - 3;
              break;

          }

        }

        break;

      case 162 ... 190:
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

  if (arduboy.everyXFrames(12) && this->xPlayer != PLAYER_MIN_X_POS) {
    this->playerImageIndex = !this->playerImageIndex;
  }
  

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void GameIntroState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;

  Sprites::drawExternalMask(0, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  Sprites::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);
  Sprites::drawExternalMask(0, 59, Images::Grass, Images::Grass_Mask, 0, 0);


  Sprites::drawOverwrite(16, 0, Images::Smoke, this->smokeIndex);

  if (this->xPlayer < 100) {
    uint8_t image = this->playerImageIndex ? 1 : 0;
    Sprites::drawExternalMask(xPlayer, PLAYER_Y_POS, Images::FireMen, Images::FireMen_Mask, image, image);

  }

  Sprites::drawExternalMask(104, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  Sprites::drawOverwrite(104, 38, Images::Ground_RHS, 0);
  Sprites::drawExternalMask(104, 59, Images::Grass, Images::Grass_Mask, 0, 0);


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
    Sprites::drawExternalMask(this->xAmbulance - 4, 36, Images::Ambulance_Door, Images::Ambulance_Door_Mask, 0, 0);
  }


  arduboy.displayWithBackground(gameStats.timeOfDay);

}
