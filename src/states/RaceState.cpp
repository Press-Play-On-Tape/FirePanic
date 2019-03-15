#include "RaceState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"
#include "../utils/Enums.h"

#define DIST_MAXIMUM 1000
#define DIST_NO_NEW_CARS 300
#define DIST_GO_TO_HOSPITAL 128
#define DIST_DELAY_AFTER_AMBULANCE_LEAVES_SCREEN 200


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void RaceState::activate(StateMachine & machine) {

  (void)machine;

  this->ambulance.setX(-40);
  this->ambulance.setY(31);
  this->paused = false;
  this->distance = DIST_MAXIMUM;
  this->slowDown = 3;
  this->showHospital = false;

  for (auto &car : this->otherCars) {

    car.setEnabled(false);

  }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void RaceState::update(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();

  if (!this->paused) {

    if(this->distance > 0) this->distance--;



    // Ambulance is still entering screen ..

    if (this->ambulance.getX() < 0) {

      if (arduboy.everyXFrames(5)) {
        this->ambulance.incX();
        this->ambulance.incX();
      }

    }


    // Have we completed the race?  If so, move the ambulance off to the right ..

    else if (this->distance == 0 && this->ambulance.getX() < DIST_DELAY_AFTER_AMBULANCE_LEAVES_SCREEN) {

      if (arduboy.everyXFrames(5)) {
        this->ambulance.incX();
        this->ambulance.incX();
      }

    }


    // If the game is over and the ambulance has left the screen, then move to the other game ..

    else if (this->distance == 0 && this->ambulance.getX() >= DIST_DELAY_AFTER_AMBULANCE_LEAVES_SCREEN) {

      machine.changeState(GameStateType::GameIntroScreen_ChangeDay, GameStateType::PlayGameScreen); 

    }


    // Play game ..

    else {


      // Clear 'do notmove flag'.  This is used to not move a car if it is being pushed by the ambulance ..

      for (auto &car : this->otherCars) {
        car.setDoNotMove(false);
      }


      // Left --------------------------------------------------------------------------------------------

      if ((pressed & LEFT_BUTTON) && this->ambulance.getX() > 0)           { this->ambulance.decX(); }


      // Right -------------------------------------------------------------------------------------------

      if ((pressed & RIGHT_BUTTON) && this->ambulance.getX() < 50) { 

        uint8_t carCollision = checkForCollisions(arduboy, this->ambulance.getX() + 1, this->ambulance.getY());

        if (carCollision > 0) {
          this->ambulance.incPuffIndexIfZero(Direction::Right);
          this->otherCars[carCollision].setX(this->ambulance.getX() + RACE_AMBULANCE_WIDTH);
          this->otherCars[carCollision].setDoNotMove(true);
        }
        else {
          this->ambulance.incX();
        }
        
      }

 
      // Up ----------------------------------------------------------------------------------------------
 
      if (pressed & UP_BUTTON && this->ambulance.getY() > 6) {

        if (checkForCollisions(arduboy, this->ambulance.getX(), this->ambulance.getY() - 1) > 0) {
          this->ambulance.incPuffIndexIfZero(Direction::Up);
        }
        else {
          this->ambulance.decY();
        }

      }

      if (this->ambulance.getDirection() == Direction::Up) {

        if (!(pressed & UP_BUTTON)) {
          if (checkForCollisions(arduboy, this->ambulance.getX(), this->ambulance.getY() - 1) > 0) {
            this->ambulance.incPuffIndexIfZero(Direction::Up);
          }
          else {
            this->ambulance.decY();
          }
        }

        if (this->ambulance.getY() == 6 || this->ambulance.getY() == 20 || this->ambulance.getY() == 33) {
          this->ambulance.setDirection(Direction::None);
        }

      }


      // Down ----------------------------------------------------------------------------------------------

      if (pressed & DOWN_BUTTON && this->ambulance.getY() < 33) {

        if (checkForCollisions(arduboy, this->ambulance.getX(), this->ambulance.getY() + 1) > 0) {
          this->ambulance.incPuffIndexIfZero(Direction::Down);
        }
        else {
          this->ambulance.incY();
        }

      }

      if (this->ambulance.getDirection() == Direction::Down) {

        if (!(pressed & DOWN_BUTTON)) {
          if (checkForCollisions(arduboy, this->ambulance.getX(), this->ambulance.getY() + 1) > 0) {
            this->ambulance.incPuffIndexIfZero(Direction::Down);
          }
          else {
            this->ambulance.incY();
          }
        }

        if (this->ambulance.getY() == 6 || this->ambulance.getY() == 20 || this->ambulance.getY() == 33) {
          this->ambulance.setDirection(Direction::None);
        }

      }


      // Launch another car?  Not if we are about to finish the race ..

      if (this->distance > DIST_NO_NEW_CARS) {

        for (auto &car : this->otherCars) {

          if (!car.getEnabled()) {

            do {
              car.setX(random(128, 300));
              car.setLane(random(0, 3));
              car.setType(random(0, 2));
              car.setSpeed(random(2, 4)); // rnadom(1,4) for fast!
              car.setEnabled(true);
            }
            while (checkLaunchCollisions(car.getX(), car.getLane()));

          }

        }

      }


      // Launch the jewel?  Not if we are about to finish the race ..

      if (this->distance > DIST_NO_NEW_CARS && jewel.getCountdown() == 0) {

        if (!jewel.getEnabled()) {

          this->jewel.setX(random(128, 340));
          this->jewel.setLane(random(0, 3));
          this->jewel.setEnabled(true);

        }

      }
      else {
        jewel.decCountdown();
      }


      // Update positions ..

      if (arduboy.everyXFrames(8)) {
        this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
      }

      if (arduboy.getFrameCount(3) < 2) {        

        if (this->jewel.getEnabled()) {
          
          this->jewel.move();

          Rect jewelRect = { this->jewel.getX(), 27 + (this->jewel.getLane() * 14), 8, 8 };
          Rect ambulanceRect = { this->ambulance.getX(), this->ambulance.getY() + 21, RACE_AMBULANCE_WIDTH, 10 };

          if (arduboy.collide(jewelRect, ambulanceRect)) {
            gameStats.score++;
            this->jewel.setEnabled(false);
          }

        }

      }


      // Update car positions ..

      for (auto &car : this->otherCars) {
        
        if (car.getEnabled() && !car.getDoNotMove()) {

          if (checkForCollision(arduboy, this->ambulance.getX(), this->ambulance.getY(), car.getX(), car.getLane())) {
            car.setX(ambulance.getX() + RACE_AMBULANCE_WIDTH);
            ambulance.incPuffIndexIfZero(Direction::Right);
          }
          else {
            car.setX(car.getX() - (arduboy.getFrameCount(car.getSpeed()) == 0/*< car.speed - 1*/ ? 2 : 1));
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

              if (car1.getEnabled() && car2.getEnabled() && car1.getLane() == car2.getLane() && absT(car1.getX() - car2.getX()) <= RACE_OTHERCAR_WIDTH) {

                if (car1.getX() > car2.getX()) {
                  car1.setX(car2.getX() + RACE_OTHERCAR_WIDTH + 1);
                }
                else {
                  car2.setX(car1.getX() + RACE_OTHERCAR_WIDTH + 1);
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

    updateSceneryPositions(arduboy);

  }

      
  if (arduboy.everyXFrames(6)) {
    this->ambulance.incPuffIndexes();
  }


  // Pause the game?

  if (justPressed & B_BUTTON) {
    this->paused = !this->paused; 
  }

}


// ----------------------------------------------------------------------------
//  Update positions of hte scenery elements .. 
//
void RaceState::updateSceneryPositions(Arduboy2Ext & arduboy) {

  if (arduboy.getFrameCount(3) < 2) {

    this->xScenery--;
    if (this->xScenery == -64) this->xScenery = 0;
    if (this->showHospital) this->xHospital--;

    if (this->distance == 0 && this->showHospital == false) {
      this->showHospital = true;
      this->xHospital = this->xScenery + (64 * 3);
    }

  }

  if (arduboy.getFrameCount(4) < 3) {        

    this->xLine1 = this->xLine1 - 2;
    if (this->xLine1 <= -32) this->xLine1 = 0;
  }

  if (arduboy.getFrameCount(5) < 3) {        

    this->xLine2 = this->xLine2 - 3;
    if (this->xLine2 <= -32) this->xLine2 = 0;

  }

}


// ----------------------------------------------------------------------------
//  Check for a collision between the car and others when launching .. 
//
bool RaceState::checkLaunchCollisions(int16_t x, uint8_t lane) {

  uint8_t collision = 0;

  for (auto &car : this->otherCars) {

    if (car.getEnabled() && car.getLane() == lane && absT(car.getX() - x) <= RACE_OTHERCAR_WIDTH) {
      collision++;
    }

  }

  return collision != 1;

}


// ----------------------------------------------------------------------------
//  Check for a collision between the ambulance and any car .. 
//
uint8_t RaceState::checkForCollisions(Arduboy2Ext & arduboy, int16_t x, uint8_t y) {

  Rect ambulanceRect = { x, y + 21, RACE_AMBULANCE_WIDTH, 10 };

  for (uint8_t i = 0; i < 3; i++) {

    auto &car = this->otherCars[i];

    if (car.getEnabled()) {

      Rect carRect = { car.getX(), 27 + (car.getLane() * 14), RACE_OTHERCAR_WIDTH, 10 };

      if (arduboy.collide(ambulanceRect, carRect)) return i;

    }

  }

  return 0;

}


// ----------------------------------------------------------------------------
//  Check for a front collision between the ambulance and a nominated car .. 
//
bool RaceState::checkForCollision(Arduboy2Ext & arduboy, int16_t ambulanceX, uint8_t ambulanceY, int16_t carX, uint8_t carLane) {

  Rect ambulanceRect = { ambulanceX + RACE_AMBULANCE_WIDTH - 1, ambulanceY + 21, 2, 10 };
  Rect carRect = { carX, 27 + (carLane * 14), 2, 10 };

  if (arduboy.collide(ambulanceRect, carRect)) return true;

  return false;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void RaceState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;


  // Render background ..

  for (uint8_t i = 0; i < 4; i++) {

    SpritesB::drawOverwrite(this->xScenery + (i*64), 0, Images::Building_BG, 0);

    if (this->showHospital) {

      SpritesB::drawOverwrite(this->xHospital, 0, Images::Hospital, 0);

    }

  }


  // Render score ..

  BaseState::renderScore(machine, TimeOfDay::Day, gameStats.score, 0, 0);


  // Render road lines ..

  for (uint8_t i = 0; i < 5; i++) {

    SpritesB::drawOverwrite(this->xLine1 + (i*32), 38, Images::Race_Line, 0);
    SpritesB::drawOverwrite(this->xLine2 + (i*32), 52, Images::Race_Line, 0);

  }


  // Render ambulance and cars from top to bottom ..

  for (uint8_t iLane = 0; iLane < 3; iLane++) {


    // Draw jewel ..

    if (this->jewel.getEnabled() && iLane == this->jewel.getLane()) {

      SpritesB::drawExternalMask(this->jewel.getX(), 29 + (this->jewel.getLane() * 13), Images::Race_Prize, Images::Race_Prize_Mask, static_cast<uint8_t>(this->lights), 0);

    }


    // Draw other cars ..

    for (auto &car : this->otherCars) {

      if (car.getEnabled() && car.getLane() == iLane) {

        #ifndef DEBUG_RACE
        SpritesB::drawExternalMask(car.getX(), 14 + (car.getLane() * 14), Images::Race_OtherCar, Images::Race_OtherCar_Mask, car.getType(), car.getType());
        #else
        arduboy.drawRect(car.getX(), 27 + (car.getLane() * 14), RACE_OTHERCAR_WIDTH, 10);
        #endif
        
      }

    }



    // Draw Ambulance ..

    if (iLane == this->ambulance.getLane()) {
      

      // Draw puff above (and behind) the ambulance if it has crashed into something above ..

      if (this->ambulance.getPuffIndex(Direction::Up) > 0) {

        uint8_t puffIndex_Mask = this->ambulance.getPuffIndex(Direction::Up) - 1;
        uint8_t puffIndex = (puffIndex_Mask * 2);

        BaseState::renderPuff(this->ambulance.getX() + (RACE_AMBULANCE_WIDTH / 2) - 16, this->ambulance.getY(), puffIndex, puffIndex_Mask);

      }


      #ifndef DEBUG_RACE
      if (this->ambulance.getX() > -RACE_AMBULANCE_WIDTH && this->ambulance.getX() < WIDTH) {
        BaseState::renderAmbulance(machine, this->ambulance.getX(), this->ambulance.getY(), this->lights, false);
      }
      #else
      arduboy.drawRect(this->ambulance.getX(), this->ambulance.getY() + 21, RACE_AMBULANCE_WIDTH, 10);
      #endif


      // Draw puffs if the ambulance has crashed into something ..

      if (this->ambulance.getPuffIndex(Direction::Right) > 0) {

        uint8_t puffIndex_Mask = this->ambulance.getPuffIndex(Direction::Right) - 1;
        uint8_t puffIndex = (puffIndex_Mask * 2);

        BaseState::renderPuff(this->ambulance.getX() + RACE_AMBULANCE_WIDTH - 8, this->ambulance.getY() + 16, puffIndex, puffIndex_Mask);

      }

      if (this->ambulance.getPuffIndex(Direction::Left) > 0) {

        uint8_t puffIndex_Mask = this->ambulance.getPuffIndex(Direction::Left) - 1;
        uint8_t puffIndex = (puffIndex_Mask * 2);

        BaseState::renderPuff(this->ambulance.getX() - 8, this->ambulance.getY() + 16, puffIndex, puffIndex_Mask);

      }


      // Draw puffs if the ambulance has crashed into something ..

      if (this->ambulance.getPuffIndex(Direction::Down) > 0) {

        uint8_t puffIndex_Mask = this->ambulance.getPuffIndex(Direction::Down) - 1;
        uint8_t puffIndex = (puffIndex_Mask * 2);

        BaseState::renderPuff(this->ambulance.getX() + (RACE_AMBULANCE_WIDTH / 2) - 8, this->ambulance.getY() + 12, puffIndex, puffIndex_Mask);

      }

    }

  }


  // Pause?

  if (this->paused) {

    SpritesB::drawExternalMask(39, 20, Images::Pause, Images::Pause_Mask, 0, 0); 

  }

	arduboy.displayWithBackground(TimeOfDay::Night);

}
