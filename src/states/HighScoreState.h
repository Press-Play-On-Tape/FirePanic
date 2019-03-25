#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "BaseState.h"

class HighScoreState : public BaseState {

  private:

    uint8_t winnerIdx = 0;
    uint8_t charIdx = 0;
    uint8_t clearScores = 0;
    uint8_t pressACounter = HS_PRESS_A_DELAY;

    char player1[NAME_LENGTH + 1];
    char player2[NAME_LENGTH + 1];
    char player3[NAME_LENGTH + 1];

    char * players[3] = { player1, player2, player3 };

    int16_t score1;
    int16_t score2;
    int16_t score3;

    void renderHighScore(uint8_t y, uint8_t chars[], int16_t score);

  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};

