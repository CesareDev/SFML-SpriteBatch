#pragma once
#include <SFML/System/Vector2.hpp>

namespace sf
{
	float distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float mag(const sf::Vector2f& v);
	sf::Vector2f norm(const sf::Vector2f& v);
	sf::Vector2f floor(const sf::Vector2f& v);
	sf::Vector2f ceil(const sf::Vector2f& v);
	sf::Vector2f max(const sf::Vector2f& v1, const sf::Vector2f& v2);
	sf::Vector2f min(const sf::Vector2f& v1, const sf::Vector2f& v2);
}

