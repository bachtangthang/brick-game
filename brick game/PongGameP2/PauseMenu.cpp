#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	//Set title
	titleFont.loadFromFile("resource\\sansation.ttf");
	title.setFont(titleFont);
	title.setCharacterSize(80);
	title.setString("PAUSE");
	title.setPosition(180, 100);

	//Set upper box
	upperBox.setSize(sf::Vector2f(200, 50));
	upperBox.setFillColor(sf::Color::Transparent);
	upperBox.setOutlineThickness(2);
	upperBox.setOutlineColor(sf::Color::White);
	upperBox.setPosition(sf::Vector2f(210, 300));
	//Upper box text
	upperText.setFont(titleFont);
	upperText.setCharacterSize(25);
	upperText.setString("Continue");
	upperText.setFillColor(sf::Color::White);
	upperText.setPosition(sf::Vector2f(upperBox.getPosition().x + 50, upperBox.getPosition().y + 8));

	//Set midle box
	midleBox.setSize(sf::Vector2f(200, 50));
	midleBox.setFillColor(sf::Color::Transparent);
	midleBox.setOutlineThickness(2);
	midleBox.setOutlineColor(sf::Color::White);
	midleBox.setPosition(sf::Vector2f(210, 380));
	//Midle box text
	midleText = upperText;
	midleText.setString("Main menu");
	midleText.setPosition(sf::Vector2f(midleBox.getPosition().x + 35, midleBox.getPosition().y + 8));

	////
	box3.setSize(sf::Vector2f(200, 50));
	box3.setFillColor(sf::Color::Transparent);
	box3.setOutlineThickness(2);
	box3.setOutlineColor(sf::Color::White);
	box3.setPosition(sf::Vector2f(210, 460));
	//Bottom box text
	text3 = midleText;
	text3.setString("Save game");
	text3.setPosition(sf::Vector2f(box3.getPosition().x + 45, box3.getPosition().y + 8));
	//Set bottom box
	bottomBox.setSize(sf::Vector2f(200, 50));
	bottomBox.setFillColor(sf::Color::Transparent);
	bottomBox.setOutlineThickness(2);
	bottomBox.setOutlineColor(sf::Color::White);
	bottomBox.setPosition(sf::Vector2f(210, 540));
	//Bottom box text
	bottomText = midleText;
	bottomText.setString("Exit game");
	bottomText.setPosition(sf::Vector2f(bottomBox.getPosition().x + 45, bottomBox.getPosition().y + 8));
}

void PauseMenu::setState(int state)
{
	mState = state;
}

int PauseMenu::getState()
{
	return mState;
}

void PauseMenu::updateMenu()
{
	switch (mState)
	{
	case 1:
		upperBox.setFillColor(sf::Color::White);
		upperText.setFillColor(sf::Color::Black);
		midleBox.setFillColor(sf::Color::Transparent);
		midleText.setFillColor(sf::Color::White);
		box3.setFillColor(sf::Color::Transparent);
		text3.setFillColor(sf::Color::White);
		bottomBox.setFillColor(sf::Color::Transparent);
		bottomText.setFillColor(sf::Color::White);
		break;
	case 2:
		upperBox.setFillColor(sf::Color::Transparent);
		upperText.setFillColor(sf::Color::White);
		midleBox.setFillColor(sf::Color::White);
		midleText.setFillColor(sf::Color::Black);
		box3.setFillColor(sf::Color::Transparent);
		text3.setFillColor(sf::Color::White);
		bottomBox.setFillColor(sf::Color::Transparent);
		bottomText.setFillColor(sf::Color::White);
		break;
	case 3:
		upperBox.setFillColor(sf::Color::Transparent);
		upperText.setFillColor(sf::Color::White);
		midleBox.setFillColor(sf::Color::Transparent);
		midleText.setFillColor(sf::Color::White);
		box3.setFillColor(sf::Color::White);
		text3.setFillColor(sf::Color::Black);
		bottomBox.setFillColor(sf::Color::Transparent);
		bottomText.setFillColor(sf::Color::White);
		break;
	case 4:
		upperBox.setFillColor(sf::Color::Transparent);
		upperText.setFillColor(sf::Color::White);
		midleBox.setFillColor(sf::Color::Transparent);
		midleText.setFillColor(sf::Color::White);
		box3.setFillColor(sf::Color::Transparent);
		text3.setFillColor(sf::Color::White);
		bottomBox.setFillColor(sf::Color::White);
		bottomText.setFillColor(sf::Color::Black);
	default:
		break;
	}
}

void PauseMenu::navigate(sf::Keyboard::Key key)
{
	if (mState != 4)
	{
		if (key == sf::Keyboard::Down)
		{
			mState++;
		}
	}
	if (mState != 1)
	{
		if (key == sf::Keyboard::Up)
		{
			mState--;
		}
	}
}
