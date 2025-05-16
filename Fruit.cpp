#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position,Color color):color_(color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(convert(color));
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

Color Fruit::getColor() const{
	return color_;
}

//convert sfSnake::Color to sf::Color
sf::Color sfSnake::convert(Color color){
	switch(color){
		case Color::BROWN : return sf::Color(139,69,19);
		case Color::RED : return sf::Color::Red;
		case Color::BLUE : return sf::Color::Blue;
		case Color::GREEN : return sf::Color::Green;
	}
	return sf::Color(139,69,19);
}