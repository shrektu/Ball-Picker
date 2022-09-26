#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	sf::RectangleShape shape;

	float movement_speed;
	int hp;
	int hp_max;

	void init_variables();
	void init_shape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	// Zwracacze
	const sf::RectangleShape& get_shape() const;
	const int& get_hp() const;
	const int& get_hp_max() const;


	// Funkcje
	void take_damage(const int damage);
	void gain_health(const int health);
	void update_input();
	void update_window_bounds_collision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

