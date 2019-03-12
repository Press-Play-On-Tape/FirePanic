#pragma once

#include "../Utils/Arduboy2Ext.h"

class Ambulance {

  public:

    Ambulance();
     
    int8_t getX();
    uint8_t getY();
    uint8_t getPuffIndex(Direction direction);
    Direction getDirection();

    void setX(int8_t value);
    void setY(uint8_t value);
    void setPuffIndex(Direction direction, uint8_t value);
    void setDirection(Direction value);

    void incX();
    void incY();
    void incPuffIndex(Direction direction);
    void incPuffIndexes();
    void decX();
    void decY();
    void incPuffIndexIfZero(Direction direction);

  protected:

    int8_t x;
    uint8_t y;
    uint8_t puffIndex[4];

    Direction direction = Direction::None;

};
