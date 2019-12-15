#ifndef __MENU_H__
#define __MENU_H__


#include<SFML\Graphics.hpp>

class Menu
{
public:
	Menu();
	virtual ~Menu() = default;

	virtual void updateMenu() = 0;
	virtual void navigate(sf::Keyboard::Key key) = 0;
};



#endif