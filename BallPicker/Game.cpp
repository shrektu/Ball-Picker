#include "Game.h"


void Game::init_variables()
{
	this->game_over = false;
	this->spawn_timer_max = 10.f;
	this->spawn_timer = this->spawn_timer_max;
	this->max_balls = 10;
	this->points = 0;
}

void Game::init_window()
{
	this->video_mode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->video_mode, "Ball Picker", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::init_font()
{
	if (!this->font.loadFromFile("Fonts/nasalization-rg.otf"))
		std::cerr << "! ERROR::GAME::INIT_FONT()::Could not load nasalization-rg.otf\n";
}

void Game::init_text()
{
	// HP i Punkty
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(24);

	// Koniec gry
	this->game_over_text.setFont(this->font);
	this->game_over_text.setFillColor(sf::Color::Red);
	this->game_over_text.setCharacterSize(60);
	this->game_over_text.setPosition(sf::Vector2f(220.f, 200.f));
	this->game_over_text.setString("You died!\nGame Over!");
}


Game::Game()
{
	this->init_variables();
	this->init_window();
	this->init_font();
	this->init_text();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::is_game_over() const
{
	return this->game_over;
}

const bool Game::is_open() const
{
	return this->window->isOpen();
}

void Game::poll_events()
{
	while (this->window->pollEvent(this->window_event))
	{
		switch (this->window_event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->window_event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawn_balls()
{
	// Timer
	if (this->spawn_timer < this->spawn_timer_max)
		this->spawn_timer += 1.f;
	else
	{
		if (this->balls.size() < this->max_balls)
		{
			this->balls.push_back(Ball(*this->window, this->rand_ball_type()));
			this->spawn_timer = 0.f;
		}
		
	}
}

const int Game::rand_ball_type() const
{
	int type = ball_types::DEFAULT;
	int rand_value = rand() % 100 + 1;

	if (rand_value > 70 && rand_value <= 85)
		type = ball_types::DAMAGING;

	else if (rand_value > 85 && rand_value <= 100)
		type = ball_types::HEALING;

	return type;
}

void Game::update_player()
{
	this->player.update(this->window);

	if (this->player.get_hp() <= 0)
		this->game_over = true;
}

void Game::update_collision()
{
	// Sprawdzenie czy gracz dotyka kulki
	for (size_t i{}; i < this->balls.size(); ++i)
	{
		if (this->player.get_shape().getGlobalBounds().intersects(this->balls[i].get_shape().getGlobalBounds()))
		{
			switch (this->balls[i].get_type())
			{
			case ball_types::DEFAULT:
				this->points++;
				break;
			case ball_types::DAMAGING:
				this->player.take_damage(1);
				break;
			case ball_types::HEALING:
				this->player.gain_health(1);
				break;
			}
			

			this->balls.erase(this->balls.begin() + i);
			
		}
	}
	
}

void Game::update_gui()
{
	std::stringstream ss;
	ss << " Points: " << this->points << "\n"
		<< " Health: " << this->player.get_hp() << " / " << this->player.get_hp_max() << "\n";

	this->text.setString(ss.str());
}

void Game::update()
{
	this->poll_events();

	if (this->game_over == false)
	{
		this->spawn_balls();
		this->update_player();
		this->update_collision();
		this->update_gui();
	}
}

void Game::render_gui(sf::RenderTarget* target)
{
	target->draw(this->text);
}

void Game::render()
{
	this->window->clear();

	// Renderowanie
	this->player.render(this->window);

	for (auto ball : this->balls)
	{
		ball.render(*this->window);
	}

	this->render_gui(this->window);

	if (this->game_over)
		this->window->draw(this->game_over_text);

	this->window->display();
}

