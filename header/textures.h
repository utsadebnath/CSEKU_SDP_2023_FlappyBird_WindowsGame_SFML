#pragma once
// textures
#include <SFML/Graphics.hpp>
using namespace sf;

struct Textures {
	Texture bird[3];
	Texture title;
	Texture pipe;
	Texture background;
	Texture gameover;
	void loadTextures();
};



