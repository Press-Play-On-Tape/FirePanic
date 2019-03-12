#pragma once

#include "../entities/OtherCar.h"
#include "../entities/Ambulance.h"
#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "BaseState.h"


class RaceState : public BaseState {

  private:

    Ambulance ambulance;

    int8_t xScenery = 0;
    int8_t xLine1 = 0;
    int8_t xLine2 = 0;

    OtherCar otherCars[3];
    
    bool paused = false;

    LightsState lights = LightsState::Lights_1;

    bool checkLaunchCollisions(int16_t x, uint8_t lane);
    uint8_t checkForCollisions(Arduboy2Ext & arduboy, int16_t x, uint8_t y);
    bool checkForCollision(Arduboy2Ext & arduboy, int16_t ambulanceX, uint8_t ambulanceY, int16_t carX, uint8_t carLane);


  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};

