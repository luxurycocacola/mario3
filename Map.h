#pragma once
#include <vector>
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Object.h"

class Map
{
public:
	Map(float cellSize = 32.0f);

	sf::Vector2f CreateFromImage(const sf::Image& image, std::vector<Object*>& objects);

	void Draw(Renderer& renderer);

	std::vector<std::vector<sf::Texture*>> grid;
	float cellSize;
};

