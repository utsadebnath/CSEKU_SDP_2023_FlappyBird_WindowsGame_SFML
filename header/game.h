#pragma once
//game
#include <SFML/Graphics.hpp>
using namespace sf;

enum GameState {
	waiting,
	started,
	gameover
};

struct Game {
	int score = 0;
	int highscore = 0;
	int frames = 0;
	GameState gameState = waiting;
	Sprite background[3];
	Sprite gameover;
	Sprite title;
	Text pressR;
	Text menu;
	Text scoreText;
	Text highscoreText;
	Font font;
	void loadDesign();
};
