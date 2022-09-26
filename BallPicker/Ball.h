#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum ball_types { DEFAULT = 0, DAMAGING, HEALING, NUM_OF_TYPES };

class Ball
{
private:
	sf::CircleShape shape;
	int type;

	void init_shape(const sf::RenderWindow& window);

public:
	Ball(const sf::RenderWindow& window, int type);
	virtual ~Ball();

	// Zwracacze
	const sf::CircleShape get_shape() const;
	const int& get_type() const;

	// Funkcje
	void update();
	void render(sf::RenderTarget& target);
};

