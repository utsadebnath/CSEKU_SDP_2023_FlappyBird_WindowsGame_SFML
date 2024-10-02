#include<iostream>
#include "header/textures.h"

// load textures
void Textures::loadTextures() {
	bird[0].loadFromFile("./images/bird1.png");
	bird[1].loadFromFile("./images/bird2.png");
	bird[2].loadFromFile("./images/bird3.png");
	title.loadFromFile("./images/title.png");
	pipe.loadFromFile("./images/pipe.png");
	background.loadFromFile("./images/background.png");
	gameover.loadFromFile("./images/gameover.png");

}