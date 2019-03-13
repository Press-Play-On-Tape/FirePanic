#pragma once

#include "../Utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"

class Frog {

  public:

    Frog();
     
    int16_t getX();
    int8_t getY();
    uint8_t getCountdown();
    uint8_t getLane();
    bool getEnabled();
    Direction getDirection();

    void setX(int16_t value);
    void setY(int8_t value);
    void setDirection(Direction value);
    void setEnabled(bool vlaue);

    void move();
    
  protected:

    int16_t x;
    int8_t y;
    uint8_t countdown;
    bool enabled;
    Direction direction = Direction::None;

};

