#include <iostream>
#include "header/sounds.h"

// load sounds
void Sounds::loadSounds() {
	scoreBuffer.loadFromFile("./audio/score.wav");
	audioBuffer.loadFromFile("./audio/flap.wav");
	crashBuffer.loadFromFile("./audio/crash.wav");
	score.setBuffer(scoreBuffer);
	flap.setBuffer(audioBuffer);
	crash.setBuffer(crashBuffer);
}
