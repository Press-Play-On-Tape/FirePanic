#include "BaseState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

void BaseState::renderScore(StateMachine & machine, int16_t score, uint8_t x, uint8_t y) {

	auto & arduboy = machine.getContext().arduboy;

  for (uint8_t j = 6, x2 = x - 4; j > 0; --j, x2 += 5) {
    
    uint8_t digits[6] = {};
    extractDigits(digits, static_cast<uint16_t>(absT(score)));

    font4x6.setCursor(x2, y);
    font4x6.print(digits[j - 1]);

  }

}

