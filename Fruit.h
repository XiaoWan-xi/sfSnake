#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
enum class Color{
	BROWN,RED,BLUE,GREEN
};

class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0),Color color=Color::BROWN);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	Color getColor() const;

	friend sf::Color convert(Color color);

private:
	sf::CircleShape shape_;

	static const float Radius;

	Color color_;
};

sf::Color convert(Color color);

}

#endif