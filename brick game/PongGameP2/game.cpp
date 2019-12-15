#include "game.h"



Game::Game()
	: mWindow(sf::VideoMode(wWidth, wHeight), "Pong Game")
{
	defaultWall();
	leftPaddle.defaultPaddle(); rightPaddle.defaultPaddle();
	defaultPaddleState();
	defaultBallState();
	middleLine.setSize(sf::Vector2f(1, wHeight));
	middleLine.setPosition(sf::Vector2f(wWidth / 2.f, 0));
	/*isPlaying = true;
	isSingle = true;*/
	NewBrick.setLevelOne();
	font.loadFromFile("resource\\SUBWT___.ttf");
	Score1.setFont(font);
	Score1.setString("0");
	Score1.setCharacterSize(50);
	Score1.setPosition((mWindow.getSize().x) / 4, 20);
	Score1.setFillColor(sf::Color::White);
	Score2.setFont(font);
	Score2.setString("0");
	Score2.setCharacterSize(50);
	Score2.setPosition(3 * (mWindow.getSize().x) / 4, 20);
	Score2.setFillColor(sf::Color::White);
	buffer.loadFromFile("resource\\bounce.wav");
	bounce.setBuffer(buffer);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
		/*processEvents();
		update(clock.restart());
		render();*/
	}
}



void Game::processEvents()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		switch (ev.type) {
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleInput(ev.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleInput(ev.key.code, false);
			break;
		}
	}
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (isPlaying && key == sf::Keyboard::W)
	{
		leftPaddle.setLeftState(isPressed);
	}
	if (isPlaying && key == sf::Keyboard::S)
	{
		leftPaddle.setRightState(isPressed);
	}
	if (!isSingle)
	{
		if (isPlaying && key == sf::Keyboard::Up)
		{
			rightPaddle.setLeftState(isPressed);
		}
		if (isPlaying && key == sf::Keyboard::Down)
		{
			rightPaddle.setRightState(isPressed);
		}
	}
	//Processed only when key is pressed
	if (isPressed)
	{
		if (isOver)
		{
			if (key == sf::Keyboard::Escape)
			{
				isMainMenu = true;
				isOver = false;
				reset();
			}
			if (key == sf::Keyboard::Enter)
			{
				isOver = false;
				isPlaying = true;
				reset();
			}
		}
		if (isMainMenu)
		{
			mainMenu.navigate(key);
			//Exit game from main menu
			if (key == sf::Keyboard::Escape)
			{
				mWindow.close();
			}
			//Start game in multiplayer mode
			if (mainMenu.getState() == 1 && key == sf::Keyboard::Enter)
			{
				isMainMenu = false;
				isSingle = false;
				isPlaying = true;
				defaultBallState();
			}
			//State game in single player mode
			if (mainMenu.getState() == 2 && key == sf::Keyboard::Enter)
			{
				isMainMenu = false;
				isSingle = true;
				isPlaying = true;
				defaultPaddleState();
				//rightPaddle.setSpeed(3);
			}
		}

		//Pause game;
		if (isPlaying && key == sf::Keyboard::Escape)
		{
			isPlaying = false;
		}
		//Pause menu input
		if (!isPlaying && !isMainMenu && !isOver)
		{
			pauseMenu.navigate(key);
			if (key == sf::Keyboard::Enter)
			{
				switch (pauseMenu.getState())
				{
				case 1:
					isPlaying = true;
					break;
				case 2:
					isPlaying = false;
					reset();
					isMainMenu = true;
					break;
				case 3:
					break;
				case 4:
					mWindow.close();
					break;
				default:
					break;
				}
			}
		}
	}
}

void Game::update(sf::Time TimePerFrame)
{
	if (isPlaying)
	{
		if (isSingle == true)
		{
			processBot();
		}
		updateBall();
		updatePaddle();
		updateScore();
		updateBrick();	
		processWinning();
		/*
		movement = sf::Vector2f(0, 0);
		movement = rightPaddle.getDirection() * rightPaddle.getSpeed();
		rightPaddle.move(movement);*/
	}
	else if (isMainMenu)
	{
		mainMenu.updateMenu();
	}
	else if (isOver)
	{

	}
	else
	{
		pauseMenu.updateMenu();
	}

}

void Game::render()
{
	//Set background's color
	mWindow.clear(sf::Color(235, 128, 39));
	if (isPlaying)
	{
		//Draw game
		mWindow.draw(middleLine);
		mWindow.draw(leftPaddle);
		//mWindow.draw(rightPaddle);
		mWindow.draw(NewBall);
		mWindow.draw(upperWall);
		mWindow.draw(lowerWall);
		mWindow.draw(leftWall);
		mWindow.draw(rightWall);
		mWindow.draw(Score1);
		mWindow.draw(Score2);
		for (auto i = NewBrick.vectorBrick.begin(); i != NewBrick.vectorBrick.end(); i++)
		{
			mWindow.draw((*i));
		}
	}
	else if (isMainMenu)
	{
		//Draw main menu
		mWindow.draw(mainMenu.title);
		mWindow.draw(mainMenu.leftBox);
		mWindow.draw(mainMenu.rightBox);
		mWindow.draw(mainMenu.box3);
		mWindow.draw(mainMenu.box4);
		mWindow.draw(mainMenu.leftText);
		mWindow.draw(mainMenu.rightText);
		mWindow.draw(mainMenu.text3);
		mWindow.draw(mainMenu.text4);
	}
	else if (isOver)
	{
		//Draw over message
		mWindow.draw(over.guideMessage);
		if (leftPaddle.getScore() >= 10)
			mWindow.draw(over.P1Win);
		else
			mWindow.draw(over.P2Win);
	}
	else
	{
		//Draw pause menu
		mWindow.draw(pauseMenu.title);
		mWindow.draw(pauseMenu.upperBox);
		mWindow.draw(pauseMenu.upperText);
		mWindow.draw(pauseMenu.midleBox);
		mWindow.draw(pauseMenu.midleText);
		mWindow.draw(pauseMenu.box3);
		mWindow.draw(pauseMenu.text3);
		mWindow.draw(pauseMenu.bottomBox);
		mWindow.draw(pauseMenu.bottomText);
	}
	mWindow.display();
}


void Game::defaultWall()
{
	float wallWidth = 19.f;
	upperWall.setSize(sf::Vector2f(wWidth, wallWidth));
	lowerWall.setSize(sf::Vector2f(wWidth, wallWidth));
	leftWall.setSize(sf::Vector2f(wallWidth, wHeight));
	rightWall.setSize(sf::Vector2f(wallWidth, wHeight));
	upperWall.setFillColor(sf::Color::White);
	lowerWall.setFillColor(sf::Color::White);
	leftWall.setFillColor(sf::Color::White);
	rightWall.setFillColor(sf::Color::White);
	upperWall.setPosition(sf::Vector2f(0.f, 0.f));
	lowerWall.setPosition(sf::Vector2f(0.f, wHeight - wallWidth));
	leftWall.setPosition(sf::Vector2f(0.f, 0.f));
	rightWall.setPosition(sf::Vector2f(wWidth - wallWidth, 0.f));
}

void Game::defaultPaddleState()
{
	leftPaddle.setPosition(sf::Vector2f(wWidth / 2.f, wHeight / 2 + 300.f));//set vi tri ban dau thanh
	leftPaddle.setScore(0);
	leftPaddle.setSpeed(5);
	//rightPaddle.setPosition(sf::Vector2f(wWidth - rightPaddle.getSize().x, wHeight / 2.f));
	//rightPaddle.setScore(0);
	//if (isSingle)
	//	rightPaddle.setSpeed(3);
	//else
	//	rightPaddle.setSpeed(5);
}

void Game::defaultBallState()
{
	NewBall.setSpeed(2);
	NewBall.setPosition(sf::Vector2f(wWidth / 2.f, wHeight / 2.f));
	//Random element
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> uniform_distance(1, std::nextafter(360, DBL_MAX));
	float angle;
	float x, y;
	sf::Vector2f direction(1, 1);

	//Make ball move random when started
	/*do {
		angle = uniform_distance(gen);
		direction = MoveableObject::rolateVector(NewBall.getDirection(), angle);
		direction = MoveableObject::normalizeVector(direction);
		angle = MoveableObject::angleInDegree(direction);
		//Ensure ball angle not too vertical
	} while ((angle > 45 && angle < 135) || (angle < -45 && angle > -135));*/

	NewBall.setDirection(direction);
}

void Game::checkWallCollision()
{
	//Bounce with upper wall
	if ((NewBall.getPosition().y - NewBall.getRadius()) <= upperWall.getSize().y)
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
	}
	//Bounce with lower wall
	if ((NewBall.getPosition().y + NewBall.getRadius()) >= (wHeight - lowerWall.getSize().y))
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
	}
	//Bounce with left wall
	if ((NewBall.getPosition().x - NewBall.getRadius()) <= leftWall.getSize().x)
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
	}
	//Bounce with right wall
	if ((NewBall.getPosition().x + NewBall.getRadius()) >= (wWidth - rightWall.getSize().x))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
	}
}

void Game::checkPaddleCollision()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> uniform_distance(1, std::nextafter(20, DBL_MAX));
	float rolate;
	float angle;
	sf::Vector2f ballDirection;
	//Bounce with left paddle
	if (NewBall.getPosition().x >= leftPaddle.getPosition().x && NewBall.getPosition().x <= (leftPaddle.getPosition().x + leftPaddle.getSize().x) && ((NewBall.getPosition().y + NewBall.getRadius() >= leftPaddle.getPosition().y && (NewBall.getPosition().y - NewBall.getRadius() <= (leftPaddle.getPosition().y + leftPaddle.getSize().y)))))//cham bien tren, duoi
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
		//	NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
		if (NewBall.getDirection().y > 0)//phan xa di xuong
		{

			NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y + NewBall.getRadius()));

		}
		else if (NewBall.getDirection().y < 0)//phan xa di len
		{
			NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y));
		}
		bounce.play();
	}
	else if((NewBall.getPosition().y >= leftPaddle.getPosition().y && NewBall.getPosition().y <= (leftPaddle.getPosition().y + leftPaddle.getSize().y) && (NewBall.getPosition().x + NewBall.getRadius()) >= leftPaddle.getPosition().x && (NewBall.getPosition().x - NewBall.getRadius()) <= leftPaddle.getPosition().x + leftPaddle.getSize().x))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
	//	NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
		if (NewBall.getDirection().x > 0)//phan xa sang phai
		{

			NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x , NewBall.getPosition().y));

		}
		else if (NewBall.getDirection().x < 0)// phan xa sang trai
		{
			NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y));
		}
		bounce.play();
	}
	/*else if (NewBall.getPosition().x < (leftPaddle.getPosition().x + leftPaddle.getSize().x) && std::abs(NewBall.getPosition().y - leftPaddle.getPosition().y) < std::abs(NewBall.getRadius() + leftPaddle.getSize().y / 2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, -NewBall.getDirection().y);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
		NewBall.setPosition(sf::Vector2f(NewBall.getRadius() + leftPaddle.getSize().x, NewBall.getPosition().y));
		bounce.play();
	}*/
	//Bounce with right paddle
	/*if ((NewBall.getPosition().x + NewBall.getRadius()) >= rightPaddle.getPosition().x && NewBall.getPosition().y >= (rightPaddle.getPosition().y - rightPaddle.getSize().y / 2.f) && NewBall.getPosition().y <= (rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
		rolate = uniform_distance(rd);
		ballDirection = NewBall.getDirection();
		angle = MoveableObject::angleInDegree(ballDirection);
		//Limit ball angle
		if (NewBall.getPosition().y > rightPaddle.getPosition().y)
		{
			if (angle > 120)
				ballDirection = MoveableObject::rolateVector(ballDirection, -rolate);
		}
		else
		{
			if (angle < -120)
				ballDirection = MoveableObject::rolateVector(ballDirection, rolate);
		}
		NewBall.setDirection(ballDirection);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
		NewBall.setPosition(sf::Vector2f(wWidth - rightPaddle.getSize().x - NewBall.getRadius(), NewBall.getPosition().y));
		bounce.play();
	}
	else if (NewBall.getPosition().x > rightPaddle.getPosition().x && std::abs(NewBall.getPosition().y - rightPaddle.getPosition().y) < std::abs(NewBall.getRadius() + rightPaddle.getSize().y / 2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, -NewBall.getDirection().y);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
		NewBall.setPosition(sf::Vector2f(wWidth - rightPaddle.getSize().x - NewBall.getRadius(), NewBall.getPosition().y));
		bounce.play();
	}*/
}

void Game::checkBrickCollision()
{
	for (auto i = NewBrick.vectorBrick.begin(); i != NewBrick.vectorBrick.end(); i++)
	{
		if (NewBall.getPosition().x >= (*i).getPosition().x && NewBall.getPosition().x <= ((*i).getPosition().x + (*i).getSize().x) && ((NewBall.getPosition().y + NewBall.getRadius() >= (*i).getPosition().y && (NewBall.getPosition().y - NewBall.getRadius() <= ((*i).getPosition().y + (*i).getSize().y)))))//cham bien tren, duoi
		{
			(*i).point--;
			NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
			if (NewBall.getDirection().y > 0)//phan xa di xuong
			{

				NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y + NewBall.getRadius()));

			}
			else if (NewBall.getDirection().y < 0)//phan xa di len
			{
				NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y));
			}
			bounce.play();
		}
		else if ((NewBall.getPosition().y >= (*i).getPosition().y && NewBall.getPosition().y <= ((*i).getPosition().y + (*i).getSize().y) && (NewBall.getPosition().x + NewBall.getRadius()) >= (*i).getPosition().x && (NewBall.getPosition().x - NewBall.getRadius()) <= (*i).getPosition().x + (*i).getSize().x))
		{
			(*i).point--;
			NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
			if (NewBall.getDirection().x > 0)//phan xa sang phai
			{

				NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y));

			}
			else if (NewBall.getDirection().x < 0)// phan xa sang trai
			{
				NewBall.setPosition(sf::Vector2f(NewBall.getPosition().x, NewBall.getPosition().y));
			}
			bounce.play();
		}
	}
}

void Game::randomCollision()
{

}

void Game::updateBall()
{
	checkWallCollision();
	if ((NewBall.getPosition().x + NewBall.getRadius()) <= 0)
	{
		//P2 scored
		rightPaddle.setScore(rightPaddle.getScore() + 1);
		defaultBallState();
	}
	if ((NewBall.getPosition().x - NewBall.getRadius()) >= wWidth)
	{
		//P1 scored
		leftPaddle.setScore(leftPaddle.getScore() + 1);
		defaultBallState();
	}
	sf::Vector2f movement;
	movement = NewBall.getDirection() * NewBall.getSpeed();
	NewBall.move(movement);
}

void Game::updatePaddle()
{
	checkPaddleCollision();
	sf::Vector2f leftMove(0, 0);
	sf::Vector2f rightMove(0, 0);
	//Move left paddle
	if (isPlaying && leftPaddle.getLeftState() && (leftPaddle.getPosition().y - leftPaddle.getSize().y / 2.f) >= upperWall.getSize().y)
	{
		leftPaddle.setDirection(-1.f, 0.f);
	}
	if (isPlaying && leftPaddle.getRightState() && (leftPaddle.getPosition().y + leftPaddle.getSize().y / 2.f) <= (wHeight - lowerWall.getSize().y))
	{
		leftPaddle.setDirection(1.f, 0.f);
	}
	leftMove = leftPaddle.getSpeed() * leftPaddle.getDirection();
	leftMove = leftPaddle.getSpeed() * leftPaddle.getDirection();

	leftPaddle.move(leftMove);

	//Reset paddle direction
	leftPaddle.setDirection(0.f, 0.f);

}

void Game::updateScore()
{
	Score1.setString(std::to_string(leftPaddle.getScore()));
	Score2.setString(std::to_string(rightPaddle.getScore()));
}

void Game::updateBrick()
{
	checkBrickCollision();
	for (auto i = NewBrick.vectorBrick.begin(); i != NewBrick.vectorBrick.end(); i++)
	{
		if ((*i).point == 0)
		{
			NewBrick.vectorBrick.erase(i);
			break;
		}
	}

}

void Game::processWinning()
{
	//Game over when one player scores 10 point first
	if (leftPaddle.getScore() >= 10 || rightPaddle.getScore() >= 10)
	{
		isPlaying = false;
		isOver = true;
	}
}

void Game::processBot()
{
	sf::Vector2f ballPosition(NewBall.getPosition());
	sf::Vector2f botPosition(rightPaddle.getPosition());
	float paddleLength = rightPaddle.getSize().y;
	//Move bot
	if (NewBall.getDirection().x > 0)
	{
		if (ballPosition.y < botPosition.y - paddleLength / 2 + paddleLength / 4)
		{
			rightPaddle.setDirection(sf::Vector2f(0, -1));
		}
		else if (ballPosition.y > botPosition.y + paddleLength / 2 - paddleLength / 4)
		{
			rightPaddle.setDirection(sf::Vector2f(0, 1));
		}
		else
		{
			rightPaddle.setDirection(sf::Vector2f(0, 0));
		}
	}
}

void Game::reset()
{
	//Reset ball and paddle to default
	defaultBallState();
	defaultPaddleState();
}
