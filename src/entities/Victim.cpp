#include "Victim.h"
#include "../utils/Physics.h"

Victim::Victim() { 

  this->enabled = false;
  this->posIndex = 0;
  this->x = pgm_read_byte(&Physics_Arc[this->posIndex * 2]);
  this->y = pgm_read_byte(&Physics_Arc[(this->posIndex * 2) + 1]);

}

uint8_t Victim::getX() {

  return this->x;

}

uint8_t Victim::getY() {

  return this->y;

}

uint8_t Victim::getRotation() {

  if (this->y >= 37) {
    return this->rotIndex;
  }
  else {
    return 5;
  }

}

uint8_t Victim::getEnabled() {

  return this->enabled;

}

void Victim::setEnabled(bool value) {

  this->enabled = value;

}

void Victim::init() {

  this->enabled = true;
  this->posIndex = 0;  

  if (this->posIndex > 67) this->posIndex = 0;

  this->x = pgm_read_byte(&Physics_Arc[this->posIndex * 2]);
  this->y = pgm_read_byte(&Physics_Arc[(this->posIndex * 2) + 1]);

}

void Victim::move() {
  
  this->posIndex++;  

  if (this->posIndex == 76) this->posIndex = 0;

  this->x = pgm_read_byte(&Physics_Arc[this->posIndex * 2]);
  this->y = pgm_read_byte(&Physics_Arc[(this->posIndex * 2) + 1]);


}

void Victim::rotate() {

  this->rotIndex++;
  if (this->rotIndex == 8) this->rotIndex = 0;

}