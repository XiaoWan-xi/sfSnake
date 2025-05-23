#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	
class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window,std::vector<Fruit>& fruits);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;

	unsigned getSize() const;

	static void setAIMode(bool aiMode);

private:
	void move();
	void grow(int length);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	void updateNodeRotation();

	bool hitSelf_;

	sf::Vector2f position_;
	sf::Vector2f direction_;
	float previousAngle_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize;

	static bool AIMode;
};
}

#endif