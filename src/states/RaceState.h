#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "BaseState.h"

class RaceState : public BaseState {

  private:

    int8_t xAmbulance = 0;
    uint8_t yAmbulance = 31;

    int8_t xScenery = 0;
    int8_t xLine1 = 0;
    int8_t xLine2 = 0;
    
    LightsState lights = LightsState::Lights_1;

  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};

