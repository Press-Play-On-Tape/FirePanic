#include "Player.h"

#include "../utils/Physics.h"
#include "../utils/Enums.h"

#define NUM_OF_ELEMENTS 11
const unsigned char PROGMEM steps[] = { // 21
  1, 1, 2, 2, 3, 3, 3, 2, 2, 1, 1
};

Player::Player() { 

    this->x = PLAYER_MIN_X_POS;

}

uint8_t Player::getX() {

  return this->x;

}

uint8_t Player::getY() {

  return PLAYER_Y_POS;

}

PlayerDirection Player::getPlayerDirection() {

  return this->playerDirection;

}

void Player::setX(uint8_t value) {

  this->x = value;

}

void Player::setPlayerDirection(PlayerDirection value) {

  this->playerDirection = value;

}

bool Player::canChangeDirections() {

  return this->xIdx == 0;

}

bool Player::canMoveLeft() {

  return (this->xIdx == 0) && (this->x > PLAYER_MIN_X_POS);

}

bool Player::canMoveRight() {

  return (this->xIdx == 0) && (this->x < PLAYER_MAX_X_POS);

}


void Player::move() {

  switch (this->playerDirection) {

    case PlayerDirection::Left:
      this->x = this->x - pgm_read_byte(&steps[this->xIdx++]);
      if (this->xIdx == NUM_OF_ELEMENTS) {
        this->xIdx = 0;
        this->playerDirection = PlayerDirection::None;
      }
      break;

    case PlayerDirection::Right:
      this->x = this->x + pgm_read_byte(&steps[this->xIdx++]);
      if (this->xIdx == NUM_OF_ELEMENTS) {
        this->xIdx = 0;
        this->playerDirection = PlayerDirection::None;
      }
      break;

    default: break;
    
  }

}

// void Player::incX() {

//   if (this->x < PLAYER_MAX_X_POS) this->x++;

// }

// void Player::decX() {

//   if (this->x > PLAYER_MIN_X_POS) this->x--;

// }
