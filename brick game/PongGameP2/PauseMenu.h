#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__



#include "Menu.h"
class PauseMenu :
	public Menu
{
private:
	int mState = 1;
public:
	sf::Font titleFont;
	sf::Text title;
	sf::Text upperText, midleText, bottomText, text3;
	sf::RectangleShape upperBox, midleBox, bottomBox, box3;

	PauseMenu();
	virtual ~PauseMenu() = default;

	void setState(int);
	int getState();
	virtual void updateMenu();
	virtual void navigate(sf::Keyboard::Key key);
};


#endif // !__PAUSEMENU_H__