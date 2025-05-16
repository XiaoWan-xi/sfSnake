#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"

using namespace sfSnake;


//use the initial list to initialize text as its default construtctor is removed in new version
MenuScreen::MenuScreen():text_(font_,
		"\n\n\n\n\n\nPress [S] to setting"
		"\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit"),snakeText_(font_,"Snake!")
{	
	//use new version openFromFile instead of loadFromFile
	//and add a check to insure the file is correctly opened
	if(!font_.openFromFile("Fonts/game_over.ttf")){
		std::cerr<<"Failed to open the file:Fonts/game_over.ttf"<<std::endl;
	}
	snakeText_.setFillColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin({textBounds.position.x + textBounds.size.x/ 2,
		textBounds.position.y + textBounds.size.y/ 2});
	text_.setPosition({Game::Width / 2, Game::Height / 2});

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin({snakeTextBounds.position.x + snakeTextBounds.size.x / 2,
		snakeTextBounds.position.y + snakeTextBounds.size.y / 2});
	snakeText_.setPosition({Game::Width / 2, Game::Height / 4});
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		Game::Screen = std::make_shared<SettingScreen>();

}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(sf::degrees(delta.asSeconds()));

		if (static_cast<int>(snakeText_.getRotation().asDegrees()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(sf::degrees(-delta.asSeconds()));

		if (static_cast<int>(snakeText_.getRotation().asDegrees()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);
}