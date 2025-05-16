#include <SFML/Graphics.hpp>

#include <iostream>

#include "SettingScreen.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "Game.h"

using namespace sfSnake;

SettingScreen::SettingScreen():text_(font_,
    "Press [P] or [B] to \nchange the \nbackground color"
    "\n\nPress [Y] or [N] to \nchoose whether \nto show the grid"
    "\n\nPress [Space] to back")
{
    if(!font_.openFromFile("Fonts/game_over.ttf")){
		std::cerr<<"Failed to open the file:Fonts/game_over.ttf"<<std::endl;
    }

    sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin({textBounds.position.x + textBounds.size.x/ 2,
		textBounds.position.y + textBounds.size.y/ 2});
	text_.setPosition({Game::Width / 2, Game::Height / 2});
}

void SettingScreen::handleInput(sf::RenderWindow& window){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)){
      Game::bgColor=sf::Color(255,192,203);
      window.clear(Game::bgColor);
      render(window);
      window.display();
    }
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)){
      Game::bgColor=sf::Color::Black;
      window.clear(sf::Color::Black);
      render(window);
      window.display();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)){
      GameScreen::setGridVisible(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)){
      GameScreen::setGridVisible(false);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
      Game::Screen = std::make_shared<MenuScreen>();
    }
}

void SettingScreen::update(sf::Time delta){
    
}

void SettingScreen::render(sf::RenderWindow& window){
    window.draw(text_);
}
