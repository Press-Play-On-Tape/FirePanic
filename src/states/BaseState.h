#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../fonts/Font4x6.h"

class BaseState : public GameState<GameContext, GameStateType> {

  protected:

    Font4x6 font4x6 = Font4x6();

    void renderScore(StateMachine & machine, TimeOfDay timeOfDay, bool renderHealth, uint8_t health);
    void renderCommonScenery(StateMachine & machine, bool incSmoke, bool incRHSBuilding);
    void renderLowerGrass(StateMachine & machine);
    void renderAmbulance(StateMachine & machine, int8_t x, int8_t y, bool doorOpen);
    void renderPuff(int8_t x, int8_t y, uint8_t puffIndex, uint8_t puffIndex_Mask);
    void renderGameOverOrPause(StateMachine & machine);
    void handlePauseButton(StateMachine & machine);
    bool getPaused();
    void setPaused(bool value);

    LightsState lights = LightsState::Lights_1;

	private:

    uint8_t smokeIndex;
    bool paused = false;

};