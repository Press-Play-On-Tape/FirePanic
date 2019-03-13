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

Direction Frog::getDirection() {

  return this->direction;

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

void Frog::setDirection(Direction value) {

  this->direction = value;

}

void Frog::setEnabled(bool value) {

  this->enabled = value;

}

void Frog::move() {

  this->x--;

  if (x == -16) {

    this->enabled = false;

  }
  else {

    switch (this->direction) {

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