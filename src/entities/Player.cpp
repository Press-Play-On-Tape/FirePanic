#include "Player.h"

#include "../utils/Physics.h"
#include "../utils/Enums.h"

Player::Player() { 

    this->x = PLAYER_MIN_X_POS;

}

uint8_t Player::getX() {

  return this->x;

}

uint8_t Player::getY() {

  return PLAYER_Y_POS;

}

void Player::setX(uint8_t value) {

  this->x = value;

}

void Player::incX() {

  if (this->x < PLAYER_MAX_X_POS) this->x++;

}

void Player::decX() {

  if (this->x > PLAYER_MIN_X_POS) this->x--;

}
