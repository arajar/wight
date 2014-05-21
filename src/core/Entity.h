#pragma once

class Entity
{
public:
	Entity();
	virtual ~Entity() {};

public:
	void SetPosition(sf::Vector2f pos);
};