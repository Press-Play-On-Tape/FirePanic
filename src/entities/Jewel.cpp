#include "Jewel.h"
#include "../utils/Enums.h"


Jewel::Jewel() {}

int16_t Jewel::getX() {

  return this->x;

}

uint8_t Jewel::getLane() {

  return this->lane;

}

uint8_t Jewel::getCountdown() {

  return this->countdown;

}

bool Jewel::getEnabled() {

  return this->enabled;

}

void Jewel::setX(int16_t value) {

  this->x = value;

}

void Jewel::setLane(uint8_t value) {

  this->lane = value;

}

void Jewel::setEnabled(bool value) {

  this->enabled = value;

}

void Jewel::decCountdown() {

  this->countdown--;

}

void Jewel::move() {

  this->x--;

  if (x == -8) {

    this->enabled = false;
    this->countdown = random(10, 100);

  }

}
