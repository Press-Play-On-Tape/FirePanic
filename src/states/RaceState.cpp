#include "RaceState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void RaceState::activate(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;

  this->xAmbulance = -40;
  this->yAmbulance = 31;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void RaceState::update(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();


  if (this->xAmbulance < 0) {

    if (arduboy.everyXFrames(5)) {
      this->xAmbulance = this->xAmbulance + 2;
    }

  }
  else {

    if ((pressed & LEFT_BUTTON) && this->xAmbulance > 0)           { this->xAmbulance--; }
    if ((pressed & RIGHT_BUTTON) && this->xAmbulance < 50)         { this->xAmbulance++; }

    if ((pressed & UP_BUTTON) && this->yAmbulance > 8)             { this->yAmbulance--; }
    if ((pressed & DOWN_BUTTON) && this->yAmbulance < 33)          { this->yAmbulance++; }
    

  }

  if (arduboy.everyXFrames(8)) {
    this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
  }

  if (arduboy.getFrameCount(3) < 2) {
    this->xScenery--;
    if (this->xScenery == -8) this->xScenery = 0;
    this->xLine1--;
    if (this->xLine1 == -32) this->xLine1 = 0;
  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void RaceState::render(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;

  for (uint8_t i = 0; i < 17; i++) {

    Sprites::drawOverwrite(this->xScenery + (i*8), 0, Images::Race_Background, 0);

  }

  for (uint8_t i = 0; i < 5; i++) {

    Sprites::drawOverwrite(this->xLine1 + (i*32), 42, Images::Race_Line, 0);
    Sprites::drawOverwrite(this->xLine1 + (i*32), 56, Images::Race_Line, 0);

  }

  Sprites::drawExternalMask(this->xAmbulance, this->yAmbulance, Images::Ambulance, Images::Ambulance_Mask, 0, 0);
  Sprites::drawExternalMask(this->xAmbulance + 18, this->yAmbulance, Images::Ambulance_Lights, Images::Ambulance_Lights_Mask, static_cast<uint8_t>(this->lights), 0);

	arduboy.displayWithBackground(TimeOfDay::Night);

}
