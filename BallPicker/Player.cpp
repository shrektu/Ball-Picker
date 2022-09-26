#include "Player.h"

void Player::init_variables()
{
	this->movement_speed = 5.f;
	this->hp_max = 3;
	this->hp = hp_max;
	
}

void Player::init_shape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->init_variables();
	this->init_shape();
}

Player::~Player()
{
}

const sf::RectangleShape& Player::get_shape() const
{
	return this->shape;
}

const int& Player::get_hp() const
{
	return this->hp;
}

const int& Player::get_hp_max() const
{
	return this->hp_max;
}

void Player::take_damage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gain_health(const int health)
{
	if (this->hp < this->hp_max)
		this->hp += health;

	if (this->hp > this->hp_max)
		this->hp = this->hp_max;
}

void Player::update_input()
{
	// Wejœcie z klawiatury
	// Lewo
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->shape.move(-this->movement_speed, 0.f);

	// Prawo
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->shape.move(this->movement_speed, 0.f);

	// Góra
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->shape.move(0.f, -this->movement_speed);

	// Dó³
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->shape.move(0.f, this->movement_speed);

}

void Player::update_window_bounds_collision(const sf::RenderTarget* target)
{

	// Lewa krawêdŸ
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	
	// Prawa krawêdŸ
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	// Górna krawêdŸ
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);

	// Dolna krawêdŸ
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	// Wejœcie z klawiatury
	this->update_input();

	// Kolizja z krawêdziami okna
	this->update_window_bounds_collision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
