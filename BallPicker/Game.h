#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Ball.h"

class Game
{
private:
	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	bool game_over;
	sf::Event window_event;

	Player player;

	int points;

	sf::Font font;
	sf::Text text;
	sf::Text game_over_text;

	std::vector<Ball> balls;
	float spawn_timer_max;
	float spawn_timer;
	int max_balls;

	void init_variables();
	void init_window();
	void init_font();
	void init_text();

public:
	// Konstruktor i destruktor
	Game();
	~Game();

	// Zwracacze
	const bool& is_game_over() const;
	// Modyfikatory

	// Funkcje cz³onkowskie
	const bool is_open() const;
	void poll_events();

	void spawn_balls();
	const int rand_ball_type() const;
	void update_player();
	void update_collision();
	void update_gui();
	void update();
	void render_gui(sf::RenderTarget* target);
	void render();
};

