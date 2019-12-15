#include "Paddle.h"

Paddle::Paddle()
{
}

void Paddle::setScore(const int& score)
{
	mScore = score;
}

int Paddle::getScore()
{
	return mScore;
}

void Paddle::defaultPaddle()
{
	setSize(sf::Vector2f(100.f, 100.f));
	mSpeed = 3;
	mDirection = sf::Vector2f(0, 0);
	setOrigin(sf::Vector2f(0, 0));
}

void Paddle::setLeftState(bool state)
{
	isLeft = state;
}

void Paddle::setRightState(bool state)
{
	isRight = state;
}

bool Paddle::getLeftState()
{
	return isLeft;
}

bool Paddle::getRightState()
{
	return isRight;
}

Paddle::Paddle(float x, float y)
{
	setSize(sf::Vector2f(100.f, 50.f));
	setOrigin(sf::Vector2f(0,0));
}
