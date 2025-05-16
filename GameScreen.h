#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit();

	void showGrid(sf::RenderWindow& window);

	static void setGridVisible(bool visible);



private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	static bool gridVisible ;
};
}

#endif