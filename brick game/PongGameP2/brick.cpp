#include "brick.h"

bool brick::getBreakable()
{
	return this->breakable;
}

void brick::setBreakable(bool state)
{
	this->breakable = state;
}

void brick::setLevelOne()
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			Paddle x(j * 100 + 20, i * 50 + 20);//20 la wallwidth
			x.setPosition(j * 100 + 20, i * 50 + 20);
			x.setFillColor(sf::Color::Green);
			x.setOutlineColor(sf::Color::Black);
			x.setOutlineThickness(1.f);
			x.point = 1;
			vectorBrick.push_back(x);
		}
	}
}

const brick& brick::operator=(const brick& x)
{
	breakable = x.breakable;
	isLeft = x.isLeft;
	isRight = x.isRight;
	mScore = x.mScore;
	point = x.point;
	return(*this);
}
