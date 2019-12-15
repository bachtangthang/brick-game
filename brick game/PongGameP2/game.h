#ifndef __GAME_H__
#define __GAME_H__

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<ctime>
#include<random>
#include<cmath>
#include"ball.h"
#include"Paddle.h"
#include"MainMenu.h"
#include"PauseMenu.h"
#include"OverMessage.h"
#include"brick.h"

class Game
{
public:
	Game();
	void run();
	
private:
	void processEvents();
	void handleInput(sf::Keyboard::Key key, bool isPressed); 
	void update(sf::Time); //Change object
	void render(); //Draw object
	//Default value
	void defaultWall();
	void defaultPaddleState();
	void defaultBallState();

	void checkWallCollision(); 
	void checkPaddleCollision();
	void checkBrickCollision();
	void randomCollision(); //Nothing here
	void updateBall();
	void updatePaddle();
	void updateScore();
	void updateBrick();
	void processWinning();
	void processBot();
	void reset();

	sf::RenderWindow mWindow;
	Ball NewBall;
	sf::RectangleShape upperWall;
	sf::RectangleShape lowerWall;
	sf::RectangleShape leftWall;
	sf::RectangleShape rightWall;
	Paddle leftPaddle;
	Paddle rightPaddle;

	bool isPlaying = false;
	bool isOver = false;
	bool isSingle = false;
	bool isMainMenu = true;
	sf::Text Score1, Score2;
	sf::Font font;
	MainMenu mainMenu;
	PauseMenu pauseMenu;
	OverMessage over;
	sf::RectangleShape middleLine;
	sf::SoundBuffer buffer;
	sf::Sound bounce; //Play sound when bounce with paddle
	brick NewBrick;
};


#endif // !__GAME_H__