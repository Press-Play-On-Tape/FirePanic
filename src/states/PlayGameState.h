#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../entities/Entities.h"

class PlayGameState : public GameState<GameContext, GameStateType> {

  private:

    uint8_t counter = 0;
  
    Victim victims[VICTIMS_MAX_NUMBER];
    Player player;
    Angel angel;

  public:
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};