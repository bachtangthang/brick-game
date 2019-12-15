#ifndef __OVERMESSAGE_H__
#define __OVERMESSAGE_H__



#include "Menu.h"
class OverMessage :
	public Menu
{
public:
	sf::Font font;
	sf::Text P1Win;
	sf::Text P2Win;
	sf::Text guideMessage;

	OverMessage();
	virtual ~OverMessage() = default;

	virtual void updateMenu();
	virtual void navigate(sf::Keyboard::Key key);

};




#endif // !__OVERMESSAGE_H__