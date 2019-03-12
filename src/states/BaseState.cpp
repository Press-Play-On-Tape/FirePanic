#include "BaseState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

void BaseState::renderScore(StateMachine & machine, TimeOfDay timeOfDay, uint16_t score, uint8_t x, uint8_t y) {

	auto & arduboy = machine.getContext().arduboy;

	uint8_t digits[6] = {};
	extractDigits(digits, score);

	for (uint8_t j = 6; j > 0; --j) {

    if (timeOfDay == TimeOfDay::Day) {
      SpritesB::drawErase(x - (j*5), y, Images::Scoreboard_Numbers, digits[j - 1]);
    }
    else {
      SpritesB::drawSelfMasked(x - (j*5), y, Images::Scoreboard_Numbers, digits[j - 1]);
    }

	}

}


void BaseState::drawCommonScenery(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    SpritesB::drawExternalMask(i, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  }

  SpritesB::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  SpritesB::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);

}



void BaseState::drawLowerGrass(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    SpritesB::drawExternalMask(i, 59, Images::Grass, Images::Grass_Mask, 0, 0);
  }

}

