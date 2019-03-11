#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "BaseState.h"

enum class AmbulanceDirection : uint8_t {
  Up,
  Down,
  None
};

class RaceState : public BaseState {

  struct OtherCar {
    int16_t x;
    int8_t y;
    uint8_t lane;
    bool enabled;
    uint8_t speed;
  };

  struct Ambulance {
    int8_t x;
    uint8_t y;
    uint8_t puffIndex;
    AmbulanceDirection direction = AmbulanceDirection::None;
  };


  private:

    Ambulance ambulance;

    int8_t xScenery = 0;
    int8_t xLine1 = 0;
    int8_t xLine2 = 0;

    OtherCar otherCars[3];
    
    bool paused = false;

    LightsState lights = LightsState::Lights_1;

    bool checkLaunchCollisions(int16_t x, uint8_t lane);
    bool checkForCollisions(Arduboy2Ext & arduboy, int16_t x, uint8_t y);


  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};

