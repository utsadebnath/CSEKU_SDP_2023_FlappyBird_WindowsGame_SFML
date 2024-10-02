#pragma once
//sounds
#include <SFML/Audio.hpp>
using namespace sf;

struct Sounds {
	SoundBuffer scoreBuffer;
	SoundBuffer audioBuffer;
	SoundBuffer crashBuffer;
	Sound score;
	Sound flap;
	Sound crash;
	void loadSounds();
};

