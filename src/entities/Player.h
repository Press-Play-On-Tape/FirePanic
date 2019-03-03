#pragma once

#include "../Utils/Arduboy2Ext.h"
  
enum class PlayerDirection : uint8_t {
  Left,
  Right,
  None
};

class Player {

  public:

    Player();
     
    uint8_t getX();
    uint8_t getY();
    PlayerDirection getPlayerDirection();

    void setX(uint8_t value);
    void setPlayerDirection(PlayerDirection value);

    void move();
    bool canChangeDirections();
    bool canMoveLeft();
    bool canMoveRight();
    uint8_t getImageIndex();
    
  protected:

    uint8_t x;
    uint8_t xIdx;
    uint8_t image;
    PlayerDirection playerDirection = PlayerDirection::None;

};

