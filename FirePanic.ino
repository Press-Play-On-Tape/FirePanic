#include "src/Game.h"

#include "src/utils/Arduboy2Ext.h"

ARDUBOY_NO_USB 

Game game;

void setup() {
	game.setup();
}

void loop() {
	game.loop();
}
