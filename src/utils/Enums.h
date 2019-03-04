#pragma once

#include <stdint.h>
#include "Utils.h"

// #define _DEBUG
// #define SOUND

#define VICTIMS_MAX_NUMBER 10

#define VICTIM_ON_GROUND_1 43
#define VICTIM_ON_GROUND_2 50
#define VICTIM_HALO_DELAY 4
#define VICTIM_HALO_MAX 60
#define VICTIM_MISSED_TRAMPOLINE 1
#define VICTIM_BOUNCE_HEIGHT 37
#define VICTIM_WIDTH_HALF 8
#define VICTIM_IN_AMBULANCE 102


#define VICTIM_DELAY_0_MIN 150
#define VICTIM_DELAY_0_MAX 200
#define VICTIM_DELAY_1_MIN 120
#define VICTIM_DELAY_1_MAX 170
#define VICTIM_DELAY_2_MIN 80
#define VICTIM_DELAY_2_MAX 130
#define VICTIM_COUNTDOWN 6

#define PLAYER_MIN_X_POS 18
#define PLAYER_MID_X_POS 39
#define PLAYER_MAX_X_POS 60
#define PLAYER_WIDTH_HALF 20

#define ACCURACY_TOLERANCE 10

#define PLAYER_RANGE1_X_LEFT_START_POS PLAYER_MIN_X_POS
#define PLAYER_RANGE1_X_LEFT_END_POS PLAYER_RANGE1_X11_POS + 3
#define PLAYER_RANGE1_X_MID_START_POS PLAYER_MIN_X_POS
#define PLAYER_RANGE1_X_MID_END_POS PLAYER_RANGE1_X11_POS + 3
#define PLAYER_RANGE1_X_RIGHT_START_POS PLAYER_MID_X_POS - 4
#define PLAYER_RANGE1_X_RIGHT_END_POS PLAYER_MID_X_POS - 1

#define PLAYER_RANGE1_X_21_POS PLAYER_MID_X_POS
#define PLAYER_RANGE1_X_22_POS PLAYER_RANGE1_X21_POS + 3
#define PLAYER_RANGE1_X_23_POS PLAYER_MAX_X_POS - 4
#define PLAYER_RANGE1_X_24_POS PLAYER_MAX_X_POS - 1

#define PLAYER_Y_POS 42
#define PLAYER_STEP_INC 6 

#define NAME_LENGTH 3

#define NO_WINNER 255
// #define NUMBER_OF_FIREWORKS 5

#define EEPROM_START                  100
#define EEPROM_START_C1               101
#define EEPROM_START_C2               102
#define EEPROM_HS_NAME_1              103
#define EEPROM_HS_NAME_2              107
#define EEPROM_HS_NAME_3              111
#define EEPROM_HS_SCORE_1             115
#define EEPROM_HS_SCORE_2             117
#define EEPROM_HS_SCORE_3             119
#define EEPROM_END                    121

#define FLASH_FRAME_COUNT_2 56


enum class TimeOfDay : uint8_t {
  Day,
  Night,
};

enum class GameStateType : uint8_t {
	SplashScreen,
	TitleScreen,
  GameIntroScreen,
  PlayGameScreen,
  HighScoreScreen
};
  
enum class LightsState : uint8_t {
  Lights_1,
  Lights_2
};

struct GameStats {

  public: 
    
    GameStats() { };

    uint16_t score = 0;
    uint16_t misses = 0;
    TimeOfDay timeOfDay = TimeOfDay::Day;

    void resetGame() {

      score = 0;
      misses = 0;
      timeOfDay = TimeOfDay::Day;

    }

};