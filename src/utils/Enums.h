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

#define NAME_LENGTH 9
// #define NAME_CHARACTER_SPACING 6
// #define NAME_UNDERLINE_WIDTH 3

// #define ASCII_SPACE 32
// #define ASCII_CAPITAL_A 65
// #define ASCII_CAPITAL_B 66
// #define ASCII_CAPITAL_Y 89
// #define ASCII_CAPITAL_Z 90
// #define ASCII_LOWER_A 97
// #define ASCII_LOWER_B 98
// #define ASCII_LOWER_Y 121
// #define ASCII_LOWER_Z 122

// #define KEY_REPEAT_DELAY 24
// #define FLASH_FRAME_COUNT 20
// #define FLASH_FRAME_COUNT_2 56
// #define ICON_MAX 8
// #define PLAYER_MAX 4
// #define FARKLE_DELAY 14

// #define FARKLE_PENALTY 500
// #define MINIMUM_HAND_SCORE 300
// #define NUMBER_OF_ROUNDS_PER_GAME 10//sjh
#define NO_WINNER 255
// #define NUMBER_OF_FIREWORKS 5

#define EEPROM_START                  100
#define EEPROM_START_C1               101
#define EEPROM_START_C2               102
#define EEPROM_PLAYER1                103
#define EEPROM_PLAYER2                113
#define EEPROM_PLAYER3                123
#define EEPROM_PLAYER4                133
#define EEPROM_HS_NAME_1              143
#define EEPROM_HS_NAME_2              153
#define EEPROM_HS_NAME_3              163
#define EEPROM_HS_SCORE_1             173
#define EEPROM_HS_SCORE_2             175
#define EEPROM_HS_SCORE_3             177
#define EEPROM_END                    179

enum class TimeOfDay : uint8_t {
  Day,
  Night,
};

enum class GameStateType : uint8_t {
	SplashScreen,
	TitleScreen,
  GameIntroScreen,
  PlayGameScreen,
};

// struct Player {

//   public: 
   
//     Player() {

//       for (uint8_t x = 1; x < NAME_LENGTH; x++) {
//         name[x] = ' ';
//       }

//       name[NAME_LENGTH - 1] = 0;

//     };

//     uint8_t getIcon() {
//       return static_cast<uint8_t>(this->name[0]);
//     }

//     void setIcon(uint8_t val) {
//       this->name[0] = static_cast<char>(val);
//     }

//     char name[NAME_LENGTH + 1];
//     int16_t score = 0;

// };

struct GameStats {

  public: 
    
    GameStats() { };

    uint16_t score = 0;
    uint16_t misses = 2;

    void resetGame() {

      score = 0;
      misses = 0;

    }

};