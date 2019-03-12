#include "RaceState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void RaceState::activate(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;

  this->ambulance.x = -40;
  this->ambulance.y = 31;
  this->paused = false;

  for (auto &car : this->otherCars) {

    car.enabled = false;

  }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void RaceState::update(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();


  if (!this->paused) {


    // Ambulance is still entereing screen ..

    if (this->ambulance.x < 0) {

      if (arduboy.everyXFrames(5)) {
        this->ambulance.x = this->ambulance.x + 2;
      }

    }

    // Play game ..

    else {

      if ((pressed & LEFT_BUTTON) && this->ambulance.x > 0)           { this->ambulance.x--; }
      if ((pressed & RIGHT_BUTTON) && this->ambulance.x < 50)         { this->ambulance.x++; }

      if (pressed & UP_BUTTON && this->ambulance.y > 6) {

        if (checkForCollisions(arduboy, this->ambulance.x, this->ambulance.y - 1)) {
          if (this->ambulance.puffIndex == 0) this->ambulance.puffIndex = 1;
        }
        else {
          this->ambulance.y--;
          this->ambulance.direction = AmbulanceDirection::Up;
        }

      }

      if (pressed & DOWN_BUTTON && this->ambulance.y < 33) {

        if (checkForCollisions(arduboy, this->ambulance.x, this->ambulance.y + 1)) {
          if (this->ambulance.puffIndex == 0) this->ambulance.puffIndex = 1;
        }
        else {
          this->ambulance.y++;
          this->ambulance.direction = AmbulanceDirection::Down;
        }

      }

      if (this->ambulance.direction == AmbulanceDirection::Up) {

        if (!(pressed & UP_BUTTON)) {
          if (checkForCollisions(arduboy, this->ambulance.x, this->ambulance.y - 1)) {
            if (this->ambulance.puffIndex == 0) this->ambulance.puffIndex = 1;
          }
          else {
              this->ambulance.y--;
          }
        }

        if (this->ambulance.y == 6 || this->ambulance.y == 20 || this->ambulance.y == 33) {
          this->ambulance.direction = AmbulanceDirection::None;
        }

      }

      if (this->ambulance.direction == AmbulanceDirection::Down) {

        if (!(pressed & DOWN_BUTTON)) {
          if (checkForCollisions(arduboy, this->ambulance.x, this->ambulance.y + 1)) {
            if (this->ambulance.puffIndex == 0) this->ambulance.puffIndex = 1;
          }
          else {
              this->ambulance.y++;
          }
        }

        if (this->ambulance.y == 6 || this->ambulance.y == 20 || this->ambulance.y == 33) {
          this->ambulance.direction = AmbulanceDirection::None;
        }

      }


      // Launch another car?

      for (auto &car : this->otherCars) {

        if (!car.enabled) {

          do {
            car.x = random(128, 340);
            car.lane = random(0, 3);
            car.speed = random(2, 4); // rnadom(1,4) for fast!
            car.enabled = true;
          }
          while (checkLaunchCollisions(car.x, car.lane));

        }

      }


      // Update positions ..
      
      if (arduboy.everyXFrames(8)) {
        this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
      }

      if (arduboy.getFrameCount(3) < 2) {
        this->xScenery--;
        if (this->xScenery == -8) this->xScenery = 0;
        this->xLine1--;
        if (this->xLine1 == -32) this->xLine1 = 0;
      }


      // Update car positions ..

      for (auto &car : this->otherCars) {
        
        if (car.enabled) {

          car.x = car.x - (arduboy.getFrameCount(car.speed) ==0/*< car.speed - 1*/ ? 2 : 1);

          if (car.x < -RACE_OTHERCAR_WIDTH) {
            car.enabled = false;
          }

        }

      }


      // Make sure one car is not going through another ..

      bool retest = true;

      while (retest) {

        retest = false;

        for (uint8_t i = 0; i < RACE_OTHERCARS_MAX; i++) {

          for (uint8_t j = 0; j < RACE_OTHERCARS_MAX; j++) {
    
            if (i != j) {

              OtherCar &car1 = this->otherCars[i];
              OtherCar &car2 = this->otherCars[j];

              if (car1.lane == car2.lane && absT(car1.x - car2.x) <= RACE_OTHERCAR_WIDTH) {

                if (car1.x > car2.x) {
                  car1.x = car2.x + RACE_OTHERCAR_WIDTH + 1;
                }
                else {
                  car2.x = car1.x + RACE_OTHERCAR_WIDTH + 1;
                }

                retest = true;
                break;

              }

            }

          }

          if (retest) break;

        }

      }
      

    }

  }


      
  if (arduboy.everyXFrames(6) && this->ambulance.puffIndex > 0) {
    this->ambulance.puffIndex++;
    if (this->ambulance.puffIndex == 6) this->ambulance.puffIndex = 0;
  }


  // Pause the game?

  if (justPressed & B_BUTTON) {
    this->paused = !this->paused; 
  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//

bool RaceState::checkLaunchCollisions(int16_t x, uint8_t lane) {

  uint8_t collision = 0;

  for (auto &car : this->otherCars) {

    if (car.enabled && car.lane == lane && absT(car.x - x) <= RACE_OTHERCAR_WIDTH) {
      collision++;
    }

  }

  return collision != 1;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//

bool RaceState::checkForCollisions(Arduboy2Ext & arduboy, int16_t x, uint8_t y) {

  Rect ambulanceRect = { x, y + 15, RACE_AMBULANCE_WIDTH, 15 };

  for (auto &car : this->otherCars) {

    if (car.enabled) {

      Rect carRect = { car.x, 21 + (car.lane * 14), RACE_OTHERCAR_WIDTH, 15 };

// Serial.println(" ");
// Serial.print("( ");
// Serial.print(ambulanceRect.x);
// Serial.print(",");
// Serial.print(ambulanceRect.y);
// Serial.print(",");
// Serial.print(ambulanceRect.width);
// Serial.print(",");
// Serial.print(ambulanceRect.height);
// Serial.print(") (");
// Serial.print(carRect.x);
// Serial.print(",");
// Serial.print(carRect.y);
// Serial.print(",");
// Serial.print(carRect.width);
// Serial.print(",");
// Serial.print(carRect.height);
// Serial.print(")  - ");


      if (arduboy.collide(ambulanceRect, carRect)) {
        
// Serial.println("true ");
        return true;

      }
// Serial.print("false ");

    }

  }
// Serial.println(" ");
  return false;

}

// ----------------------------------------------------------------------------
//  Render the state .. 
//
void RaceState::render(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;

  for (uint8_t i = 0; i < 17; i++) {

    SpritesB::drawOverwrite(this->xScenery + (i*8), 0, Images::Race_Background, 0);

  }

  for (uint8_t i = 0; i < 5; i++) {

    SpritesB::drawOverwrite(this->xLine1 + (i*32), 38, Images::Race_Line, 0);
    SpritesB::drawOverwrite(this->xLine1 + (i*32), 52, Images::Race_Line, 0);

  }

  for (uint8_t iLane = 0; iLane < 3; iLane++) {

    for (auto &car : this->otherCars) {

      if (car.enabled && car.lane == iLane) {

        SpritesB::drawExternalMask(car.x, 14 + (car.lane * 14), Images::Race_OtherCar, Images::Race_OtherCar_Mask, 0, 0);

      }

    }


    if ((iLane == 0 && this->ambulance.y >= 6 && this->ambulance.y <= 13) ||
        (iLane == 1 && this->ambulance.y >= 14 && this->ambulance.y <= 26) ||
        (iLane == 2 && this->ambulance.y >= 27 && this->ambulance.y <= 33)) {

      #ifndef DEBUG_RACE
      SpritesB::drawExternalMask(this->ambulance.x, this->ambulance.y, Images::Ambulance, Images::Ambulance_Mask, 0, 0);
      SpritesB::drawExternalMask(this->ambulance.x + 18, this->ambulance.y, Images::Ambulance_Lights, Images::Ambulance_Lights_Mask, static_cast<uint8_t>(this->lights), 0);
      #else
      arduboy.drawRect(this->ambulance.x, this->ambulance.y + 20, RACE_AMBULANCE_WIDTH, 10);
      #endif

      if (this->ambulance.puffIndex > 0) {

        uint8_t puffIndex_Mask = this->ambulance.puffIndex - 1;
        uint8_t puffIndex = (puffIndex_Mask * 2);//SJH + (gameStats.timeOfDay == TimeOfDay::Night ? 1 : 0);

        SpritesB::drawExternalMask(this->ambulance.x + RACE_AMBULANCE_WIDTH - 8, this->ambulance.y + 16, Images::Puff, Images::Puff_Mask, puffIndex, puffIndex_Mask);

      }

    }

  }

  // Pause?

  if (this->paused) {

    SpritesB::drawExternalMask(39, 20, Images::Pause, Images::Pause_Mask, 0, 0); 

  }

	arduboy.displayWithBackground(TimeOfDay::Night);

}
