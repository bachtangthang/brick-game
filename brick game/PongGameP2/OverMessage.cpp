#include "OverMessage.h"

OverMessage::OverMessage()
{
	font.loadFromFile("resource\\sansation.ttf");
	P1Win.setFont(font);
	P1Win.setCharacterSize(80);
	P1Win.setString("P1 Win");
	P1Win.setPosition(270, 100);

	P2Win = P1Win;
	P2Win.setString("P2 Win");

	guideMessage = P1Win;
	guideMessage.setString("Press Enter to continue\nPress Escape to exit game");
	guideMessage.setCharacterSize(30);
	guideMessage.setPosition(250, 300);
}

void OverMessage::updateMenu()
{
}

void OverMessage::navigate(sf::Keyboard::Key key)
{
}
