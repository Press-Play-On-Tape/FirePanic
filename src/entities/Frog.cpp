#include "Frog.h"
#include "../utils/Enums.h"


Frog::Frog() {}

int16_t Frog::getX() {

  return this->x;

}

uint8_t Frog::getLane() {

  return this->lane;

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

void Frog::setLane(uint8_t value) {

  this->lane = value;

}

void Frog::setEnabled(bool value) {

  this->enabled = value;

}

void Frog::decCountdown() {

  this->countdown--;

}

void Frog::move() {

  this->x--;

  if (x == -8) {

    this->enabled = false;
    this->countdown = random(10, 100);

  }

}
