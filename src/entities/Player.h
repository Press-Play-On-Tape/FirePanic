#pragma once

#include "../Utils/Arduboy2Ext.h"

class Player {

  public:

    Player();
     
    uint8_t getX();
    uint8_t getY();

    void setX(uint8_t value);
    
    void incX();
    void decX();

  protected:

    uint8_t x;

};

