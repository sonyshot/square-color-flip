#pragma once
#ifndef CLICKGRID_H
#define CLICKGRID_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include <algorithm>

class ClickGrid : public sf::Drawable {
	int m_size;
	sf::Vector2f m_drawPos;
	sf::RectangleShape m_background;
	std::vector<sf::RectangleShape*> m_squares;
	std::vector<int> m_pixelArray;
	std::array<int, 2> m_lastSquare = { 0, 0 };

	void flipSquare(std::array<int, 2> square);

	void dragGrid(int, int);

	void makeWaves();

	void blinkRing(int num, int x, int y);

public:
	ClickGrid(int size, sf::Vector2f drawPos);

	~ClickGrid();

	bool chooseSquare(int, int);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // !CLICKGRID_H