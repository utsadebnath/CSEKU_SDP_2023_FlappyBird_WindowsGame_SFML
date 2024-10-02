#include <iostream>
using namespace std;

#include "header/textures.h"
#include "header/game.h"
Textures textures;
Game game;

// load font, set positions, scales
void Game::loadDesign() {
	font.loadFromFile("./fonts/FiraCode-SemiBold.ttf");
	background[0].setTexture(textures.background);
	background[1].setTexture(textures.background);
	background[2].setTexture(textures.background);
	background[0].setScale(1.15625, 1.171875);
	background[1].setScale(1.15625, 1.171875);
	background[2].setScale(1.15625, 1.171875);
	background[1].setPosition(333, 0);
	background[2].setPosition(666, 0);

	menu.setString("Play:Press spacebar");
	menu.setFont(game.font);
	menu.setFillColor(Color::White);
	menu.setCharacterSize(41);
	menu.setOrigin(game.menu.getLocalBounds().width / 2, 0);
	menu.setPosition(740, 219);

	scoreText.setFont(game.font);
	scoreText.setFillColor(Color::White);
	scoreText.setCharacterSize(75);
	scoreText.move(30, 0);

	highscoreText.setFont(game.font);
	highscoreText.setFillColor(Color::White);
	highscoreText.move(30, 80);

	gameover.setTexture(textures.gameover);
	gameover.setOrigin(192 / 2, 42 / 2);
	gameover.setPosition(500, 125);
	gameover.setScale(2, 2);

	title.setTexture(textures.title);
	title.setOrigin(192 / 2, 42 / 2);
	title.setPosition(500, 125);
	title.setScale(2, 2);

	pressR.setString("Restart:Press R");
	pressR.setFont(game.font);
	pressR.setFillColor(Color::White);
	pressR.setCharacterSize(51);
	pressR.setOrigin(game.pressR.getLocalBounds().width / 2, 0);
	pressR.setPosition(500, 270);
}