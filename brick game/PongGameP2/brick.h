#ifndef __BRICK_H__
#define __BRICK_H__
#include <SFML\Graphics.hpp>
#include "Paddle.h"
#include "MoveableObject.h"
//wweight = 640, wheight = 960, wallwidth = 20
class brick : public sf::RectangleShape,Paddle
{
protected:
	bool breakable;//1 la co the pha dc, 0 la ko the pha dc
public:
	std::vector <Paddle> vectorBrick;
	bool getBreakable();
	void setBreakable(bool state);
	void setLevelOne();
	const brick& operator=(const brick& x);
};
#endif
