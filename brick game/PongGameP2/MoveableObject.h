#ifndef __MOVEABLEOBJECT_H__
#define __MOVEABLEOBJECT_H__

#include<SFML\Graphics.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 144.f); //Thời gian của một frame
const unsigned int wWidth = 640; //Chiều rộng cửa sổ
const unsigned int wHeight = 960; //Chiều cao cửa sổ

class MoveableObject
{
protected:
	float mSpeed; //Tốc độ của vật
	sf::Vector2f mDirection; //Vector hướng
public:
	MoveableObject();
	virtual ~MoveableObject() = default;
	void setSpeed(float);
	void setDirection(float, float);
	void setDirection(const sf::Vector2f&);
	float getSpeed();
	sf::Vector2f getDirection();
	static sf::Vector2f normalizeVector(const sf::Vector2f&); //Đơn vị hoá vector
	static double vectorLength(const sf::Vector2f&); //Tính chiều dài vector
	static double dotProduct(const sf::Vector2f&, const sf::Vector2f&); //Tích vô hướng
	static double angleInDegree(const sf::Vector2f&); //Góc vector với trục hoành (chú ý: góc ngược xuống dưới)
	static sf::Vector2f rolateVector(const sf::Vector2f&, float); //Xoay vector một góc cho trước ngược chiều kim đồng hồ

};

#endif // !__MOVEABLEOBJECT_H__