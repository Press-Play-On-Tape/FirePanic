#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

  (void)machine;

//  this->victims[0].init();
  this->angel.setEnabled(false);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void PlayGameState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
	auto pressed = arduboy.pressedButtons();


  // Update victim positions ..
  {
    uint8_t playerXCentre = this->player.getX() + PLAYER_WIDTH_HALF;

    if (arduboy.everyXFrames(5)) {

      for (auto &victim : victims) {

        if (victim.getEnabled()) {

          uint8_t victimX = victim.getX();

          if (victimX == VICTIM_IN_AMBULANCE) {
            gameStats.score++;
          }
          else {

            uint8_t victimXCentre = victimX + VICTIM_WIDTH_HALF;
            uint8_t delta = absT(victimXCentre - playerXCentre);

            if (victim.getY() == VICTIM_BOUNCE_HEIGHT && delta > ACCURACY_TOLERANCE) {

              victim.setAlive(VICTIM_MISSED_TRAMPOLINE);
              gameStats.misses++;

              switch (victim.getX()) {

                case PLAYER_MIN_X_POS ... PLAYER_MID_X_POS - 1:
                  this->angel.init(0);
                  break;

                case PLAYER_MID_X_POS ... PLAYER_MAX_X_POS - 1:
                  this->angel.init(1);
                  break;

                case PLAYER_MAX_X_POS ... WIDTH:
                  this->angel.init(2);
                  break;

              }
              
            }  

          }

          victim.move();
          
        }

      }

    }

  }

  if (arduboy.everyXFrames(15)) {

    for (auto &victim : victims) {

      if (victim.getEnabled()) {
        victim.rotate();
      }

    }

  }


  // Launch a new victim?

  if (arduboy.everyXFrames(2)) {

    this->victimDelay--;

    if (this->victimDelay == 0) {

      switch (gameStats.score) {

        case 0 ... 10:
          this->victimDelay = random(VICTIM_DELAY_0_MIN, VICTIM_DELAY_0_MAX);
          this->victimCountdown = VICTIM_COUNTDOWN;
          this->victimLevel = 0;
          break;

        case 11 ... 20:
          this->victimDelay = random(VICTIM_DELAY_1_MIN, VICTIM_DELAY_1_MAX);
          this->victimCountdown = VICTIM_COUNTDOWN;
          this->victimLevel = random(2);
          break;

        default:
          this->victimDelay = random(VICTIM_DELAY_2_MIN, VICTIM_DELAY_2_MAX);
          this->victimCountdown = VICTIM_COUNTDOWN;
          this->victimLevel = random(3);
          break;

      }

    }

  }


  // Is a victim ready to jump?

  if (arduboy.everyXFrames(30)) {

    switch (this->victimCountdown) {

      case 0: break;

      case 1:
        {
          this->victimCountdown--;
          uint8_t nextAvailableVictim = getNextAvailable();
          this->victims[nextAvailableVictim].init();
        }
        break;

      default:
        this->victimCountdown--;
        break;

    }

  }



  // Update player position ..

  if ((pressed & LEFT_BUTTON) && this->player.canMoveLeft())      { this->player.setPlayerDirection(PlayerDirection::Left); }
  if ((pressed & RIGHT_BUTTON) && this->player.canMoveRight())    { this->player.setPlayerDirection(PlayerDirection::Right); }
  
  if (arduboy.everyXFrames(2)) {

    this->player.move();

  }


  // Update angel ..
  
  if (this->angel.getEnabled()) {
    
    if (arduboy.everyXFrames(6)) {

      this->angel.move();

    }

  }

  if (arduboy.everyXFrames(8)) {
    this->lights = (this->lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
  }



  if (arduboy.everyXFrames(16)) {
    this->smokeIndex++;
    if (this->smokeIndex >= 5) this->smokeIndex = 0;
  }

}


// ----------------------------------------------------------------------------
//  Get index of next available victim.
//
uint8_t PlayGameState::getNextAvailable() {

  for (uint8_t i = 0; i < VICTIMS_MAX_NUMBER; i++) {

    if (!this->victims[i].getEnabled()) {
      return i;
    }

  }

  return 255;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;

  Sprites::drawExternalMask(0, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  Sprites::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);

  if (gameStats.timeOfDay == TimeOfDay::Day) {
    Sprites::drawErase(89, 0, Images::Scoreboard, 0);
  }
  else {
    Sprites::drawExternalMask(89, 0, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);
  }
  
  Sprites::drawOverwrite(16, 0, Images::Smoke, this->smokeIndex);



  // Render misses ..

  switch (gameStats.misses) {

    case 0: break;

    case 1:
      if (!this->angel.getEnabled()) {
        Sprites::drawExternalMask(76, 2, Images::Misses, Images::Misses_Mask, 0, 0); 
      }
      break;

    case 2:
      Sprites::drawExternalMask(76, 2, Images::Misses, Images::Misses_Mask, 0, 0); 
      if (!this->angel.getEnabled()) {
        Sprites::drawExternalMask(63, 2, Images::Misses, Images::Misses_Mask, 0, 0); 
      }
      break;
      
    default: 
      Sprites::drawExternalMask(76, 2, Images::Misses, Images::Misses_Mask, 0, 0); 
      Sprites::drawExternalMask(63, 2, Images::Misses, Images::Misses_Mask, 0, 0); 
      break;

  }


  // Render score ..

	uint8_t digits[6] = {};
	extractDigits(digits, gameStats.score);

	for (uint8_t j = 6; j > 0; --j) {

    if (gameStats.timeOfDay == TimeOfDay::Day) {
      Sprites::drawErase(124 - (j*5), 3, Images::Scoreboard_Numbers, digits[j - 1]);
    }
    else {
      Sprites::drawSelfMasked(124 - (j*5), 3, Images::Scoreboard_Numbers, digits[j - 1]);
    }

	}



  uint8_t i = 0;

  Sprites::drawExternalMask(this->player.getX(), this->player.getY(), (uint8_t *)pgm_read_word_near(&Images::Firemen[i]), (uint8_t *)pgm_read_word_near(&Images::Firemen_Mask[i]), 0, 0);
  
  // Render Foreground grass ..
  Sprites::drawExternalMask(0, 59, Images::Grass, Images::Grass_Mask, 0, 0);


  // Render victims ..

  for (auto &victim : this->victims) {

    if (victim.getEnabled()) {

      uint8_t imageIndex = victim.getRotation();
      Sprites::drawExternalMask(victim.getX(), victim.getY(), Images::Victims, Images::Victims_Mask, imageIndex, imageIndex);

      uint8_t isAlive = victim.getAlive();

      if (isAlive >= 2) {
        
        uint8_t haloIndexMask = victim.getHaloIndex();
        uint8_t haloIndex = haloIndexMask * 2;

        if (gameStats.timeOfDay == TimeOfDay::Night) haloIndex++; 
        Sprites::drawExternalMask(victim.getX(), victim.getY() - 5, Images::Victim_Halos, Images::Victim_Halos_Mask, haloIndex, haloIndexMask);

      }

    }

  }


  // Render victim about to jump ..

  const int8_t edgePos[] = { 0, -5, 17, -1, 0, 12, 17, 13, 0, 28, 17, 29 };

  if (this->victimCountdown > 0) {

    Sprites::drawExternalMask(edgePos[this->victimLevel * 4], edgePos[(this->victimLevel * 4) + 1], Images::Victim_OnEdge_01, Images::Victim_OnEdge_01_Mask, 0, 0);

    if (this->victimCountdown % 2 == 0) {

      Sprites::drawExternalMask(edgePos[(this->victimLevel * 4) + 2], edgePos[(this->victimLevel * 4) + 3], Images::Victim_OnEdge_02, Images::Victim_OnEdge_02_Mask, 0, 0);

    }

  }



  // Render angel if required ..

  if (this->angel.getEnabled() && this->angel.renderImage()) {

    uint8_t imageIndex = this->angel.getImageIndex();
    Sprites::drawExternalMask(this->angel.getX(), this->angel.getY(), Images::Angels, Images::Angels_Mask, imageIndex, imageIndex);

  }

  Sprites::drawExternalMask(96, 31, Images::Ambulance, Images::Ambulance_Mask, 0, 0);

  switch (this->lights) {

    case LightsState::Lights_1:
      Sprites::drawExternalMask(114, 31, Images::Ambulance_Lights_01, Images::Ambulance_Lights_Mask, 0, 0);
      break;

    case LightsState::Lights_2:
      Sprites::drawExternalMask(114, 31, Images::Ambulance_Lights_02, Images::Ambulance_Lights_Mask, 0, 0);
      break;

  }

  arduboy.displayWithBackground(gameStats.timeOfDay);

}
