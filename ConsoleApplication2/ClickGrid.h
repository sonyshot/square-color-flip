#pragma once
#ifndef CLICKGRID_H
#define CLICKGRID_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include <algorithm>

class ClickGrid : public sf::Drawable {
	int m_numSquares, m_squareSize;

	sf::Clock m_timer;
	sf::Vector2f m_drawPos;
	sf::RectangleShape m_background;

	std::vector<sf::RectangleShape*> m_squares;
	std::vector<int> m_pixelArray;
	std::array<int, 2> m_lastSquare = { 0, 0 };

	bool m_waving = 0;
	bool m_GOL = 0;
	bool m_grayscale = 0;

	void flipSquare(std::array<int, 2> square);

	void dragGrid(int, int);

	void makeWaves();

	void flipRing(int num, int x, int y);

	bool livingSquare(int x, int y);

	int newColor(int x, int y);

public:
	ClickGrid(int squareSize, int numSquares, sf::Vector2f drawPos);

	ClickGrid(int numSquares, sf::Vector2f drawPos);

	ClickGrid(int squareSize, int numSquares, sf::Vector2f drawPos, int);

	~ClickGrid();

	bool chooseSquare(int, int);

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // !CLICKGRID_H