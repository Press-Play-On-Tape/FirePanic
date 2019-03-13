#include "Frog.h"
#include "../utils/Enums.h"


Frog::Frog() { 

    this->x = 0;
    this->y = 0;

}

int16_t Frog::getX() {

  return this->x;

}

int8_t Frog::getY() {

  return this->y;

}

uint8_t Frog::getXDirection() {

  return this->xDirection;

}

Direction Frog::getYDirection() {

  return this->yDirection;

}

uint8_t Frog::getCountdown() {

  return this->countdown;

}

bool Frog::getEnabled() {

  return this->enabled;

}

void Frog::setX(int16_t value) {

  this->x = value;

}

void Frog::setY(int8_t value) {

  this->y = value;

}

void Frog::setXDirection(uint8_t value) {

  this->xDirection = value;

}

void Frog::setYDirection(Direction value) {

  this->yDirection = value;

}

void Frog::setEnabled(bool value) {

  this->enabled = value;

}

void Frog::decCountdown() {

  this->countdown--;

}

void Frog::move() {

  this->x = this->x - xDirection;

  if (x == -16) {

    this->enabled = false;

  }
  if (x < 128) {

    switch (this->yDirection) {

      case Direction::Up:
        this->y--;
        if (this->y == -16) {
          this->enabled = false;
          this->countdown = random(0, 100);
        }
        break;

      case Direction::Down:
        this->y++;
        if (this->y == 80) {
          this->enabled = false;
          this->countdown = random(0, 100);
        }
        break;
        
    }

  }

}

uint8_t Frog::getLane() {

  switch (this->y) {

    case  0 ... 13: return 0;
    case 14 ... 26: return 1;
    default:        return 2;

  }

}