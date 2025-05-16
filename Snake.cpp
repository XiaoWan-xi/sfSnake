#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;


//use the initial list to initialize sound as its default construtctor is removed in new version
Snake::Snake() : direction_({0,-1}), hitSelf_(false),pickupSound_(pickupBuffer_),dieSound_(dieBuffer_)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	//change the input frow four keys into the mouse click
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f headPos = nodes_[0].getPosition();
		direction_ = {static_cast<float>(mousePos.x) - headPos.x, static_cast<float>(mousePos.y) - headPos.y};
		direction_=direction_.normalized();
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().findIntersection(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		switch(toRemove->getColor()){
			case Color::BROWN:break;
			case Color::RED:grow(3);break;
			case Color::BLUE:grow(2);break;
			case Color::GREEN:grow(1);break;
		}
		fruits.erase(toRemove);
	}
}

void Snake::grow(int length)
{
	//also change the grow function to fit more direction
	sf::Vector2f lastPos = nodes_[nodes_.size()-1].getPosition();
	sf::Vector2f secondLastPos = nodes_.size()>1?nodes_[nodes_.size()-2].getPosition():lastPos;

	sf::Vector2f tailDirection = {lastPos.x-secondLastPos.x,lastPos.y-secondLastPos.y};

	if(nodes_.size()<=1||(tailDirection.x==0&&tailDirection.y==0)){
		tailDirection.x=-direction_.x;
		tailDirection.y=-direction_.y;
	}
	//make the direction of grow more suitable
	tailDirection=tailDirection.normalized();
	for(int i=0;i<length;++i){
		nodes_.push_back(SnakeNode(sf::Vector2f(lastPos.x+SnakeNode::Width*tailDirection.x*(i+1),lastPos.y+SnakeNode::Height*tailDirection.y*(i+1))));
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().findIntersection(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}
	nodes_[0].move(SnakeNode::Width*direction_.x,SnakeNode::Height*direction_.y);
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& node : nodes_)
		node.render(window);
}
