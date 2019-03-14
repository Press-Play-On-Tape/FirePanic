#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../fonts/Font4x6.h"

class BaseState : public GameState<GameContext, GameStateType> {

  protected:

    Font4x6 font4x6 = Font4x6();

    void renderScore(StateMachine & machine, TimeOfDay timeOfDay, uint16_t score, uint8_t x, uint8_t y);
    void drawCommonScenery(StateMachine & machine, bool incSmoke);
    void drawLowerGrass(StateMachine & machine);
    void drawAmbulance(StateMachine & machine, int8_t x, int8_t y, LightsState lightState, bool doorOpen);

	private:

    uint8_t smokeIndex;

};