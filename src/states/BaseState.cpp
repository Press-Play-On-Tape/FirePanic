#include "BaseState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

void BaseState::renderScore(StateMachine & machine, TimeOfDay timeOfDay, bool renderHealth, uint8_t health) {
  	
  auto & gameStats = machine.getContext().gameStats;
  auto & arduboy = machine.getContext().arduboy;

  if (timeOfDay == TimeOfDay::Day) {
    SpritesB::drawExternalMask(89, 0, Images::Scoreboard, Images::Scoreboard_Mask, 1, 0);
  }
  else {
    SpritesB::drawExternalMask(89, 0, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);
  }

  if (!renderHealth) {

    uint8_t digits[6] = {};
    extractDigits(digits, gameStats.score);

    for (uint8_t j = 6; j > 0; --j) {

      if (timeOfDay == TimeOfDay::Day) {
        SpritesB::drawErase(124 - (j*5), 3, Images::Scoreboard_Numbers, digits[j - 1]);
      }
      else {
        SpritesB::drawSelfMasked(124 - (j*5), 3, Images::Scoreboard_Numbers, digits[j - 1]);
      }

    }

  }
  else {

    for (uint8_t i = 0; i < health; i = i + 2) {
      
      arduboy.drawFastVLine(94 + i, 3, 8);

    }

  }

}


void BaseState::renderCommonScenery(StateMachine & machine, bool incSmoke, bool incRHSBuilding) {

  auto & gameStats = machine.getContext().gameStats;
	auto & arduboy = machine.getContext().arduboy;

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    SpritesB::drawExternalMask(i, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  }

  SpritesB::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);


  // Draw smoke if specified ..

  #ifndef DEBUG

  if (incSmoke) {
    
    uint8_t x = cloud_X_Pos[this->smokeIndex];
    uint8_t y = cloud_Y_Pos[this->smokeIndex];

    SpritesB::drawOverwrite(x, y, pgm_read_word_near(&Images::Smoke[this->smokeIndex]), static_cast<uint8_t>(gameStats.timeOfDay));

    if (arduboy.everyXFrames(16)) {
      this->smokeIndex++;
      if (this->smokeIndex >= 5) this->smokeIndex = 0;
    }

  }

  #endif

  SpritesB::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);

  if (incRHSBuilding) {
    SpritesB::drawExternalMask(112, 0, Images::Building_RHS, Images::Building_RHS_Mask, 0, 0);
  }

}


void BaseState::renderLowerGrass(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    SpritesB::drawExternalMask(i, 59, Images::Grass, Images::Grass_Mask, 0, 0);
  }

}


void BaseState::renderAmbulance(StateMachine & machine, int8_t x, int8_t y, bool doorOpen) {

	auto & arduboy = machine.getContext().arduboy;


  // Alternate lights ..

  if (arduboy.everyXFrames(8)) {
    this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
  }


  // Draw Ambulance with lights ..

  SpritesB::drawExternalMask(x, y, Images::Ambulance, Images::Ambulance_Mask, 0, 0);
  SpritesB::drawExternalMask(x + 18, y, Images::Ambulance_Lights, Images::Ambulance_Lights_Mask, static_cast<uint8_t>(this->lights), 0);

  if (doorOpen) {
    SpritesB::drawExternalMask(x - 4, y + 5, Images::Ambulance_Door, Images::Ambulance_Door_Mask, 0, 0);
  }

}

void BaseState::renderPuff(int8_t x, int8_t y, uint8_t puffIndex, uint8_t puffIndex_Mask) {

  SpritesB::drawExternalMask(x, y, Images::Puff, Images::Puff_Mask, puffIndex, puffIndex_Mask);

}

bool BaseState::getPaused() {

  return this->paused;

}

void BaseState::setPaused(bool value) {
  
  this->paused = value;

}

void BaseState::handlePauseButton(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();

  if (justPressed & B_BUTTON) {
    this->paused = !this->paused; 
  }

}

void BaseState::renderGameOverOrPause(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;


  // Game Over?

  if (gameStats.gameOver) {

    SpritesB::drawExternalMask(32, 20, Images::GameOver, Images::GameOver_Mask, 0, 0); 

  }

  // Pause?

  if (this->paused) {

    SpritesB::drawExternalMask(39, 20, Images::Pause, Images::Pause_Mask, 0, 0); 

  }

}