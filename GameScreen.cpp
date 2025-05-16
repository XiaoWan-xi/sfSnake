#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace sfSnake;

bool GameScreen::gridVisible = false;
GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window,fruit_);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
	
	if(GameScreen::gridVisible) showGrid(window);
	
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine(time(NULL));
	//engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
	static std::uniform_int_distribution<int> color(0,3);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),static_cast<Color>(color(engine))));
}

void GameScreen::showGrid(sf::RenderWindow& window){
	for(float x=0;x<=(float)Game::Width;x+=2*SnakeNode::Width){
		sf::VertexArray line(sf::PrimitiveType::Lines,2);

		line[0].position=sf::Vector2f(x,0.0f);
		line[1].position=sf::Vector2f(x,(float)Game::Height);

		line[0].color=sf::Color(70,70,70);
		line[1].color=sf::Color(70,70,70);

		window.draw(line);
	}
	for(float y=0;y<=(float)Game::Height;y+=2*SnakeNode::Height){
		sf::VertexArray line(sf::PrimitiveType::Lines,2);

		line[0].position=sf::Vector2f(0,y);
		line[1].position=sf::Vector2f((float)Game::Width,y);

		line[0].color=sf::Color(70,70,70);
		line[1].color=sf::Color(70,70,70);

		window.draw(line);
	}
}

void GameScreen::setGridVisible(bool visible){
	gridVisible = visible;
}


