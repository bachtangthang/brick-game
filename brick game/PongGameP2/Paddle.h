#ifndef __PADDLE_H__
#define __PADDLE_H__

#include<SFML\Graphics.hpp>
#include"MoveableObject.h"
#include<vector>

class Paddle : public sf::RectangleShape, public MoveableObject
{
protected:
	bool isLeft = false; //true: paddle move left
	bool isRight = false; //true: paddle move right
	int mScore = 0; //Player's score
public: 
	int point = 0;
	Paddle();
	virtual ~Paddle() = default;

	void setScore(const int&);
	int getScore();

	void defaultPaddle();
	void setLeftState(bool state);
	void setRightState(bool state);
	bool getLeftState();
	bool getRightState();
	Paddle(float x, float y);
};

#endif // !__PADDLE_H__