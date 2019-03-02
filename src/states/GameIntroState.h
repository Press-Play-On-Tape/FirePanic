#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../entities/Victim.h"
#include "../entities/Player.h"

class GameIntroState : public GameState<GameContext, GameStateType> {
  
  enum class LightsState : uint8_t {
    Lights_1,
    Lights_2,
    None
  };

  private:

    uint8_t xAmbulance = 156;
    uint8_t counter = 0;
    uint8_t smokeIndex = 0;
    bool ambulanceDoor = false;

    LightsState lights = LightsState::Lights_1;

  public:
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};