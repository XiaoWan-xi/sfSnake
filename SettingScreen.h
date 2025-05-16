#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class SettingScreen : public Screen
{
public:
    SettingScreen();

    void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
    sf::Font font_;
    sf::Text text_;
};
}

#endif