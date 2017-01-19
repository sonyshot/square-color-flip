#pragma once
#ifndef CLICKGRID_H
#define CLICKGRID_H
#include <SFML\Graphics.hpp>
#include <iostream>

class ClickGrid : public sf::Drawable {
	int m_size;
	sf::Vector2f m_drawPos;
	sf::RectangleShape m_background;
	std::vector<sf::RectangleShape*> m_squares;
	std::vector<int> m_pixelArray;

public:
	ClickGrid(int size, sf::Vector2f drawPos);

	~ClickGrid();

	void flipSquare(std::array<int, 2> square);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // !CLICKGRID_H
