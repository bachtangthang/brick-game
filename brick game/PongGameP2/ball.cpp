#include "ball.h"

Ball::Ball()
{
	mSpeed = 1;
	mDirection.x = sqrt(2)/2;
	mDirection.y = sqrt(2)/2;
	mDirection = normalizeVector(mDirection);
	setRadius(10);
	setOrigin(getRadius(), getRadius());
	setPosition((float)wWidth / 2, (float)wHeight / 2);
}

Ball::Ball(float radius, float speed, float x, float y)
{
	setRadius(radius);
	setOrigin(getRadius() / 2, getRadius() / 2);
	mSpeed = speed;
	setPosition(x, y);
}

Ball::~Ball()
{
}

