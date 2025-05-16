#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{

enum class NodeType{
	HEAD,
    BODY_CIRCLE,
    BODY_RECTANGLE
};

class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0),NodeType type = NodeType::BODY_CIRCLE);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setRotation(float angle);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const float Height;

private:

	NodeType type_;
    sf::Vector2f position_;
    
    sf::CircleShape circleShape_;
    sf::RectangleShape rectangleShape_;
    sf::Sprite headSprite_;
    
    static sf::Texture headTexture_;
	static bool textureLoaded_;
};
}

#endif