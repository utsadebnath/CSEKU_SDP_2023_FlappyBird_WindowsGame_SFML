//Flappy Bird using c++ and SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "header/collision.h"
#include "header/sounds.h"
#include "header/textures.h"
#include "header/game.h"

int main() {
	// window configuration
	RenderWindow window(VideoMode(1000, 599), "Flappy Bird");
	window.setFramerateLimit(59);
	window.setKeyRepeatEnabled(false);
	srand(time(0));

	// sounds
	Sounds sounds;
	sounds.loadSounds();

	//textures
	extern Textures textures;
	textures.loadTextures();

	//Game
	extern Game game;
	game.loadDesign();

	// flappy 
	struct Flappy {
		double v = 0;
		int frame = 0;
		Sprite sprite;
	} flappy;

	// flappy's initial position
	flappy.sprite.setPosition(251, 300);
	flappy.sprite.setScale(2, 2);

	// resizable array of sprites for pipes
	vector<Sprite> pipes;


	// main loop
	while (window.isOpen()) {

		// update score text
		flappy.sprite.setTexture(textures.bird[1]);
		game.scoreText.setString(to_string(game.score));
		game.highscoreText.setString("HS " + to_string(game.highscore));

		// flappy's recent position
		float fx = flappy.sprite.getPosition().x;
		float fy = flappy.sprite.getPosition().y;
		float fw = 34 * flappy.sprite.getScale().x;
		float fh = 24 * flappy.sprite.getScale().y;

		// flap the wings
		if (game.gameState == waiting || game.gameState == started) {

			if (game.frames % 5 == 0) {
				flappy.frame += 1;
			}
			if (flappy.frame == 3) {
				flappy.frame = 0;
			}
		}
		flappy.sprite.setTexture(textures.bird[flappy.frame]);

		// move flappy
		if (game.gameState == started) {
			flappy.sprite.move(0, flappy.v);
			flappy.v += 0.5;
		}

		// hits ceiling - stop ascending
		// out of screen - game over
		if (game.gameState == started) {
			if (fy < 0) {
				flappy.sprite.setPosition(251, 0);
				flappy.v = 0;
			}
			else if (fy > 599) {
				flappy.v = 0;
				game.gameState = gameover;
				sounds.crash.play();
			}
		}

		// count the score
		for (vector<Sprite>::iterator itr = pipes.begin(); itr != pipes.end(); itr++) {
			if (game.gameState == started && (*itr).getPosition().x == 250) {
				game.score++;
				sounds.score.play();

				if (game.score > game.highscore) {
					game.highscore = game.score;
				}
				break;
			}
		}

		// generate pipes
		if (game.gameState == started && game.frames % 150 == 0) {
			int r = rand() % 275 + 75;
			int gap = 224;

			// lower pipe
			Sprite pipeL;
			pipeL.setTexture(textures.pipe);
			pipeL.setPosition(1000, r + gap);
			pipeL.setScale(2, 2);

			// upper pipe
			Sprite pipeU;
			pipeU.setTexture(textures.pipe);
			pipeU.setPosition(1000, r);
			pipeU.setScale(2, -2);

			// push to the array
			pipes.push_back(pipeL);
			pipes.push_back(pipeU);
		}

		// move pipes
		if (game.gameState == started) {
			for (vector<Sprite>::iterator itr = pipes.begin(); itr != pipes.end(); itr++) {
				(*itr).move(-3, 0);
			}
		}

		// remove pipes if offscreen
		if (game.frames % 100 == 0) {
			vector<Sprite>::iterator startitr = pipes.begin();
			vector<Sprite>::iterator enditr = pipes.begin();

			for (; enditr != pipes.end(); enditr++) {
				if ((*enditr).getPosition().x > -104) {
					break;
				}
			}
			pipes.erase(startitr, enditr);
		}

		// collision detection
		if (game.gameState == started) {
			for (vector<Sprite>::iterator itr = pipes.begin(); itr != pipes.end(); itr++) {

				float px, py, pw, ph;

				if ((*itr).getScale().y > 0) {
					px = (*itr).getPosition().x;
					py = (*itr).getPosition().y;
					pw = 52 * (*itr).getScale().x;
					ph = 320 * (*itr).getScale().y;
				}
				else {
					pw = 52 * (*itr).getScale().x;
					ph = -320 * (*itr).getScale().y;
					px = (*itr).getPosition().x;
					py = (*itr).getPosition().y - ph;
				}

				if (collision(fx, fy, fw, fh, px, py, pw, ph)) {
					game.gameState = gameover;
					sounds.crash.play();
				}
			}
		}

		// events
		Event event;
		while (window.pollEvent(event)) {

			// End game
			if (event.type == Event::Closed) {
				window.close();
			}

			// play : Press spacebar
			else if (event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Space) {
				if (game.gameState == waiting) {
					game.gameState = started;
				}

				if (game.gameState == started) {
					flappy.v = -8;
					sounds.flap.play();
				}
			}
			// Restart : Press R
			else if (event.type == Event::KeyPressed &&
				event.key.code == Keyboard::R &&
				game.gameState == gameover) {
				game.gameState = waiting;
				flappy.sprite.setPosition(251, 300);
				game.score = 0;
				pipes.clear();
			}
		}

		// clear, draw, display
		window.clear();
		window.draw(game.background[0]);
		window.draw(game.background[1]);
		window.draw(game.background[2]);
		window.draw(flappy.sprite);


		// draw pipes
		for (vector<Sprite>::iterator itr = pipes.begin(); itr != pipes.end(); itr++) {
			window.draw(*itr);
		}

		// draw scores
		window.draw(game.scoreText);
		window.draw(game.highscoreText);

		// Title and Menu
		if (game.gameState == waiting) {
			window.draw(game.title);
			window.draw(game.menu);
		}

		// Restart : Press R
		if (game.gameState == gameover) {
			window.draw(game.gameover);

			window.draw(game.pressR);
		}
		window.display();

		// update total frames
		game.frames++;
	}
	return 0;
}