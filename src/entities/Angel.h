#pragma once

#include "../Utils/Arduboy2Ext.h"

class Angel {

  public:

    Angel();
     
    uint8_t getX();
    uint8_t getY();
    uint8_t getEnabled();

    void setEnabled(bool value);
    void setSequence(uint8_t sequence);
    void init(uint8_t sequence);
    void move();
    
  protected:

    uint8_t x;
    uint8_t y;
    bool enabled;
    uint8_t sequence;
    uint8_t sequenceLen;
    uint8_t posIndex;

};

