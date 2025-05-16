#include <SFML/Graphics.hpp>
#include <iostream>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

sf::Texture sfSnake::SnakeNode::headTexture_;
bool sfSnake::SnakeNode::textureLoaded_ = false;

SnakeNode::SnakeNode(sf::Vector2f position,NodeType type)
: position_(position),type_(type),headSprite_(headTexture_)
{
	if(!textureLoaded_){
		if(headTexture_.loadFromFile("Textures/snake_head.png")){
			textureLoaded_=true;
		}
		else{
			std::cerr<<"Failed to load the snake_head file"<<std::endl;
		}
	}

	switch (type_) {
        case NodeType::HEAD:
            headSprite_.setTexture(headTexture_);
            headSprite_.setOrigin({headTexture_.getSize().x / 2.0f, headTexture_.getSize().y / 2.0f});
            headSprite_.setScale({Width * 2 / headTexture_.getSize().x, 
                                Height * 2 / headTexture_.getSize().y});
            headSprite_.setPosition(position_);
            break;
            
        case NodeType::BODY_CIRCLE:
            circleShape_.setRadius(Width/2);
            circleShape_.setOrigin({Width/2, Width/2});
            circleShape_.setFillColor(sf::Color::Yellow);
            circleShape_.setOutlineColor(sf::Color::Black);
            circleShape_.setOutlineThickness(-1.f);
            circleShape_.setPosition(position_);
            break;
            
        case NodeType::BODY_RECTANGLE:
            rectangleShape_.setSize(sf::Vector2f(Width, Height));
            rectangleShape_.setOrigin({Width/2, Height/2});
            rectangleShape_.setFillColor(sf::Color::Black);
            rectangleShape_.setOutlineColor(sf::Color::Yellow);
            rectangleShape_.setOutlineThickness(-1.f);
            rectangleShape_.setPosition(position_);
            break;
    }
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	switch (type_) {
        case NodeType::HEAD:
            headSprite_.setPosition(position_);
            break;
        case NodeType::BODY_CIRCLE:
            circleShape_.setPosition(position_);
            break;
        case NodeType::BODY_RECTANGLE:
            rectangleShape_.setPosition(position_);
            break;
    }
}

void SnakeNode::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x,y));
}

void SnakeNode::move(float xOffset, float yOffset)
{
	setPosition(sf::Vector2f(position_.x+xOffset,position_.y+yOffset));
}

sf::FloatRect SnakeNode::getBounds() const
{
	switch (type_) {
        case NodeType::HEAD:
            return sf::FloatRect({position_.x-Width/2.0f,position_.y-Height/2.0f},{Width,Height});
        case NodeType::BODY_CIRCLE:
            return circleShape_.getGlobalBounds();
        case NodeType::BODY_RECTANGLE:
            return rectangleShape_.getGlobalBounds();
    }
    
    return sf::FloatRect(sf::Vector2f(position_.x,position_.y),sf::Vector2f(Width,Height));
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::setRotation(float angle){
	float degrees = angle * 180.0f/3.14159f;

	switch (type_) {
        case NodeType::HEAD:
            headSprite_.setRotation(sf::degrees(degrees+90)); // +90 to align properly
            break;
        case NodeType::BODY_RECTANGLE:
            rectangleShape_.setRotation(sf::degrees(degrees));
            break;
    }

}

void SnakeNode::render(sf::RenderWindow& window)
{
	switch (type_) {
        case NodeType::HEAD:
            window.draw(headSprite_);
            break;
        case NodeType::BODY_CIRCLE:
            window.draw(circleShape_);
            break;
        case NodeType::BODY_RECTANGLE:
            window.draw(rectangleShape_);
            break;
    }
}