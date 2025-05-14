#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

//use the initial list to initialize text as its default construtctor is removed in new version
GameOverScreen::GameOverScreen(std::size_t score) : score_(score),text_(font_,"Your score: " + std::to_string(score) + "!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit")
{
	//use new version openFromFile instead of loadFromFile
	//and add a check to insure the file is correctly opened
	if(!font_.openFromFile("Fonts/game_over.ttf")){
		std::cerr<<"Failed to open font file Fonts/game_over.ttf"<<std::endl;
	}
	text_.setFillColor(sf::Color::Red);//change setColor into new version setFillColor

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin({textBounds.position.x + textBounds.size.x / 2,
		textBounds.position.y + textBounds.size.y / 2});
	text_.setPosition({Game::Width / 2, Game::Height / 2});
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		window.close();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
}