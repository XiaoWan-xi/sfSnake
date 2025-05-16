#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

sf::Color Game::bgColor = sf::Color::Black;

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode({Game::Width, Game::Height}), "sfSnake")
{
	//add the check to ensure the file is correctly opened
	if(bgMusic_.openFromFile("Music/bg_music.wav")){
		bgMusic_.setLoopPoints({sf::milliseconds(0),sf::seconds(50)});//fix the bug:music should use setLoopPoints instead of setLoop
		bgMusic_.play();
	}
	else{
		std::cerr<<"Failed to open background music file:Music/bg_music.wav"<<std::endl;
	}
}

void Game::handleInput()
{
	//fix the wrong Close event handle
	while(const std::optional event = window_.pollEvent()){
		if(event->is<sf::Event::Closed>()){
			window_.close();
		}
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear(bgColor);
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}
